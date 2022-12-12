/*******************************************************************************************
*
*   DatabaseFromScratch v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 Viachaslau Ilyuk. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#define RAYGUI_IMPLEMENTATION

#include <stdlib.h>
#include <stdio.h>

#include "..\..\thirdparty\raygui\include\raygui.h"

#include "..\laboratory_work\post_office.h"   // for MAX_STREET_NAME_SIZE 
#include "..\laboratory_work\post_package.h"  // for MAX_PACKAGE_NAME_SIZE 

#include "database_raygui_style.h"
#include "database_raylib_gui.h"

#include "..\database_package_row.h"
#include "..\database_statement.h"


//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------
static GuiQueryResult RegisterPackageButton(Table** table, int package_size_toggle, const char* street_name, const char* package_name);               // Button: register_package_button logic


int raylib_start(Table** table, GuiQueryResult* query_status_out_result)
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 936;
    int screenHeight = 504;

    InitWindow(screenWidth, screenHeight, "Database from scratch");
    GuiLoadStyleDatabaseRayguiStyle();  
    // Database from scratch: controls initialization
    //----------------------------------------------------------------------------------
    // Const text
    const char *package_size_boxText = "Package size";    // GROUPBOX: package_size_box
    const char *package_size_toggleText = "S;M;L";    // TOGGLEGROUP: package_size_toggle
    const char *register_package_buttonText = "Register package";    // BUTTON: register_package_button
    const char *office_status_window_boxText = "Office status";    // WINDOWBOX: office_status_window_box
    const char *street_name_group_boxText = "Street name";    // GROUPBOX: street_name_group_box
    const char *package_name_group_boxText = "Package name";    // GROUPBOX: package_name_group_box
    const char *add_office_toggleText = "Add office";    // TOGGLE: add_office_toggle
    const char *add_street_toggleText = "Add street";    // TOGGLE: add_street_toggle
    const char *office_status_toggleText = "Office status";    // TOGGLE: office_status_toggle
    const char *add_street_window_boxText = "Add street";    // WINDOWBOX: add_street_window_box
    const char *add_office_window_boxText = "Add office";    // WINDOWBOX: add_office_window_box
    
    // Define controls variables
    int package_size_toggleActive = 0;            // ToggleGroup: package_size_toggle

    bool street_name_text_boxEditMode = false;
    bool package_name_text_boxEditMode = false;
// MAX_STREET_NAME_SIZE MAX_PACKAGE_NAME_SIZE
    char street_name_text_boxText[MAX_STREET_NAME_SIZE + 1] = "";            // TextBox: street_name_text_box
    char package_name_text_boxText[MAX_PACKAGE_NAME_SIZE + 1] = "";
    
    bool add_office_toggleActive = false;            // Toggle: add_office_toggle
    bool add_street_toggleActive = false;            // Toggle: add_street_toggle
    bool office_status_toggleActive = false;            // Toggle: office_status_toggle

    bool add_office_window_boxActive = false;            // WindowBox: add_office_window_box
    bool add_street_window_boxActive = false;            // WindowBox: add_street_window_box
    bool office_status_window_boxActive = true;            // WindowBox: office_status_window_box
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

            GuiGroupBox((Rectangle){ 264, 216, 192, 72 }, package_size_boxText);
            GuiGroupBox((Rectangle){ 264, 24, 192, 72 }, street_name_group_boxText);
            GuiGroupBox((Rectangle){ 264, 120, 192, 72 }, package_name_group_boxText);

            if (GuiButton((Rectangle){ 24, 312, 432, 168 }, register_package_buttonText)) 
            {
                *query_status_out_result = RegisterPackageButton(table, package_size_toggleActive, street_name_text_boxText, package_name_text_boxText); 
            }
            if (GuiTextBox((Rectangle){ 288, 48, 144, 24 }, street_name_text_boxText, 128, street_name_text_boxEditMode)) 
            {
                street_name_text_boxEditMode = !street_name_text_boxEditMode;
            }
            if (GuiTextBox((Rectangle){ 288, 144, 144, 24 }, package_name_text_boxText, 128, package_name_text_boxEditMode)) 
            {
                package_name_text_boxEditMode = !package_name_text_boxEditMode;
            }
            
            add_office_toggleActive = GuiToggle((Rectangle){ 24, 24, 192, 72 }, add_office_toggleText, add_office_toggleActive);
            add_street_toggleActive = GuiToggle((Rectangle){ 24, 120, 192, 72 }, add_street_toggleText, add_street_toggleActive);
            office_status_toggleActive = GuiToggle((Rectangle){ 24, 216, 192, 72 }, office_status_toggleText, office_status_toggleActive);
            
            package_size_toggleActive = GuiToggleGroup((Rectangle){ 296, 240, 40, 24 }, package_size_toggleText, package_size_toggleActive);

            // Toggle windows
            if (add_office_toggleActive) { add_office_window_boxActive = GuiWindowBox((Rectangle){ 480, 24, 432, 456 }, add_office_window_boxText); }
            if (add_street_toggleActive) { add_street_window_boxActive = GuiWindowBox((Rectangle){ 480, 24, 432, 456 }, add_street_window_boxText); }
            if (office_status_toggleActive) { office_status_window_boxActive = GuiWindowBox((Rectangle){ 480, 24, 432, 456 }, office_status_window_boxText); }

        EndDrawing();
        //----------------------------------------------------------------------------------
        *query_status_out_result = GUI_QUERY_DID_NOT_QUERY_SUCCESS;
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    MinimizeWindow();
    //--------------------------------------------------------------------------------------
    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------
// Button: register_package_button logic
//------------------------------------------------------------------------------------
static GuiQueryResult RegisterPackageButton(Table** table, int package_size_toggle, const char* street_name, const char* package_name)
{
#if defined(DB_DEBUG)
    switch (package_size_toggle)
    {
        case 0:
        {
            fprintf(stdout, "Package size small: %d\n", package_size_toggle);
            break;
        }
        case 1:
        {
            fprintf(stdout, "Package size medium: %d\n", package_size_toggle);
            break;
        }
        case 2:
        {
            fprintf(stdout, "Package size large: %d\n", package_size_toggle);
            break;
        }
    }
#endif // defined(DB_DEBUG)
    
    Statement* database_gui_query = (Statement*)malloc(sizeof(Statement));
    if (database_gui_query == NULL)
    {
        fprintf(stdout, "Query error. Unable to allocate space for query.");
        return GUI_QUERY_ALLOC_FAILED;
    }

    database_gui_query->type = STATEMENT_INSERT;
    database_gui_query->row_to_insert.id = 0;
    strncpy(database_gui_query->row_to_insert.package_street, street_name, MAX_STREET_NAME_SIZE);
    strncpy(database_gui_query->row_to_insert.package_name, package_name, MAX_PACKAGE_NAME_SIZE);

    ExecuteResult execute_result = execute_statement(database_gui_query, table);
    execute_statement_result_message(execute_result);
    
#if defined(DB_DEBUG)
    fprintf(stdout, "Street name: %s\n", street_name);
    fprintf(stdout, "Street name len: %zu\n", strlen(street_name));
    fprintf(stdout, "Package name: %s\n", package_name);
    fprintf(stdout, "Package name len: %zu\n", strlen(package_name));
#endif // defined(DB_DEBUG)
    
    free(database_gui_query);
    database_gui_query = NULL;
    return GUI_QUERY_SUCCESS;
}
  
/*******************************************************************************************
*
*   DatabaseFromScratch v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 venci venice. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#define RAYGUI_IMPLEMENTATION

#include "..\..\thirdparty\raygui\include\raygui.h"

#include "database_raygui_style.h"
#include "database_raylib_gui.h"

#include "..\database_base_types.h"
#include "..\database_package_row.h"
#include "..\database_repl.h"


internal void database_gui_send_query(PackageRow row_to_send, InputBuffer* out_input_buffer);


//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------
static void AddStreet();
static void AddPostOffice();
static void OfficeState();

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int raylib_start()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Database from scratch");

    // database_from_scratch: controls initialization
    //----------------------------------------------------------------------------------
    const char *main_windowText = "I dont undertstand why do i need it";
    const char *buttons_group_boxText = "Database controls";
    const char *add_streetText = "Add street";
    const char *add_post_officeText = "Add post office";
    const char *office_stateText = "Office state";
    
    Vector2 anchor01 = { 0, 0 };
    Vector2 anchor03 = { 8, 24 };
    
    bool main_windowActive = true;
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            if (main_windowActive)
            {
                main_windowActive = !GuiWindowBox((Rectangle){ anchor01.x + 0, anchor01.y + 0, 800, 600 }, main_windowText);
            }
            GuiGroupBox((Rectangle){ anchor03.x + 0, anchor03.y + 10, 208, 204 }, buttons_group_boxText);
            if (GuiButton((Rectangle){ anchor03.x + 10, anchor03.y + 20, 188, 56 }, add_streetText)) AddStreet(); 
            if (GuiButton((Rectangle){ anchor03.x + 10, anchor03.y + 84, 188, 56 }, add_post_officeText)) AddPostOffice(); 
            if (GuiButton((Rectangle){ anchor03.x + 10, anchor03.y + 148, 188, 56 }, office_stateText)) OfficeState(); 
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
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
static void AddStreet()
{
}
static void AddPostOffice()
{
    // TODO: Implement control logic
}
static void OfficeState()
{
    // TODO: Implement control logic
}
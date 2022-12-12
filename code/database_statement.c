#include <stdio.h>
#include <stdlib.h>

#include "database_statement.h"
#include "database_repl.h"
#include "database_package_table.h"
#include "database_package_row.h"
#include "database_cursor.h"
#include "database_base_types.h"


//------------------------------------------------------------------------------------
// READ STATEMENT
//------------------------------------------------------------------------------------
internal PrepareStatementResult prepare_read(InputBuffer* input_buffer, Statement* statement)
{
    char* statement_token = strtok(input_buffer->buffer, " ");
    char* filename_string = strtok(NULL, " ");
    u8 file_extension_length = 4;
    
    if (statement_token == NULL || filename_string == NULL)
    {
        return PREPARE_SYNTAX_ERROR;
    }
    if (strlen(filename_string) > MAX_DATABASE_FILENAME_LENGTH)
    {
        return PREPARE_STRING_TOO_LONG;
    }
    if (strlen(filename_string) <= file_extension_length)
    {
        return PREPARE_STRING_TOO_SHORT;
    }

    // check for file extension
    char* file_extension_dot = strrchr(filename_string, '\0') - file_extension_length;
    if (file_extension_dot == NULL) 
    {
        return PREPARE_UNRECOGNIZED_DATABASE_FILE;
    }
    if (strncmp(file_extension_dot, ".idb", (size_t)file_extension_length))
    {
        return PREPARE_UNRECOGNIZED_DATABASE_FILE;
    }
    statement->type = STATEMENT_READ;

    // TEMPORARY SOLUTION MUST BE REWORKED
    statement->filename = (char*)malloc(strlen(filename_string));
    if (statement->filename == NULL)
    {
        fprintf(stderr, "Error. Malloc failed while allocating filename from READ statement.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(statement->filename, filename_string);
    // TEMPORARY SOLUTION MUST BE REWORKED

    return PREPARE_STATEMENT_SUCCESS;
}


internal ExecuteResult execute_read(Statement* statement, Table** table)
{
    if (*table != NULL)
    {
        db_close(*table);
    }
    *table = db_open(statement->filename);
    free(statement->filename);
    return EXECUTE_SUCCESS;
}

//------------------------------------------------------------------------------------
// INSERT STATEMENT
//------------------------------------------------------------------------------------
internal PrepareStatementResult prepare_insert(InputBuffer* input_buffer, Statement* statement)
{
    char* statement_token = strtok(input_buffer->buffer, " ");
    char* id_string = strtok(NULL, " ");
    char* package_name_string = strtok(NULL, " ");
    char* package_street_string  = strtok(NULL, " ");
    
    if (package_street_string == NULL ||
        package_name_string == NULL ||
        statement_token == NULL ||
        id_string == NULL)
    {
        return PREPARE_SYNTAX_ERROR;
    }
    if (strlen(package_name_string) > PACKAGE_NAME_SIZE)
    {
        return PREPARE_STRING_TOO_LONG;
    }
    if (strlen(package_street_string) > PACKAGE_STREET_SIZE)
    {
        return PREPARE_STRING_TOO_LONG;
    }

    // Assert thrown when id_string is NULL so place it after condition
    i32 int_id = atoi(id_string);
    if (int_id < 0)
    {
        return PREPARE_NEGATIVE_ID;
    }
    
    statement->row_to_insert.id = (u64)int_id;
    strcpy(statement->row_to_insert.package_name, package_name_string);
    strcpy(statement->row_to_insert.package_street, package_street_string);
    statement->type = STATEMENT_INSERT;
    return PREPARE_STATEMENT_SUCCESS;
}


internal ExecuteResult execute_insert(Statement* statement, Table* table)
{
    if (table == NULL)
    {
        return EXECUTE_DATABASE_FILE_NOT_LOADED;
    }

    DbCursor* cursor = table_end(table);

    PackageRow* row_to_insert = &(statement->row_to_insert);
    serialize_package_row(row_to_insert, cursor_value(cursor));
    table->num_rows += 1;

    debug_cursor_end(cursor);
    free(cursor);
    return EXECUTE_SUCCESS;
    
}

//------------------------------------------------------------------------------------
// SELECT STATEMENT
//------------------------------------------------------------------------------------
internal PrepareStatementResult prepare_select(InputBuffer* input_buffer, Statement* statement)
{
    statement->type = STATEMENT_SELECT;
    return PREPARE_STATEMENT_SUCCESS;
}


internal ExecuteResult execute_select(Statement* statement, Table* table)
{
    if (table == NULL)
    {
        return EXECUTE_DATABASE_FILE_NOT_LOADED;
    }

    DbCursor* cursor = table_start(table);

    PackageRow row;
    while (!(cursor->end_of_table))
    {
        deserialize_package_row(cursor_value(cursor), &row);
        print_package_row(&row);
        cursor_advance(cursor);
        debug_cursor_start(cursor);
    }
    
    free(cursor);
    return EXECUTE_SUCCESS;
}

//------------------------------------------------------------------------------------
// KIND OF STATEMENT'S "SQL COMPILER"
//------------------------------------------------------------------------------------
internal PrepareStatementResult prepare_statement(InputBuffer* input_buffer, Statement* statement)
{
    if (strncmp(input_buffer->buffer, "INSERT", 6) == 0)
    {
        return prepare_insert(input_buffer, statement);  
    }
    if (strncmp(input_buffer->buffer, "SELECT", 6) == 0)
    {
        return prepare_select(input_buffer, statement);
    }
    if (strncmp(input_buffer->buffer, "READ", 4) == 0)
    {
        return prepare_read(input_buffer, statement);
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}


ExecuteResult execute_statement(Statement* statement, Table** table)
{
    switch (statement->type)
    {
        case STATEMENT_SELECT:
        {
            return execute_select(statement, *table);
        }
        case STATEMENT_INSERT:
        {
            return execute_insert(statement, *table);
        }
        case STATEMENT_READ:
        {
            return execute_read(statement, table);
        }
    }
    return STATEMENT_UNRECOGNIZED; 
}


void execute_statement_result_message(ExecuteResult result)
{
    switch(result)
    {
        case EXECUTE_SUCCESS:
        {
            fprintf(stdout, "Executed successfully.\n");
            break;
        }
        case EXECUTE_TABLE_FULL:
        {
            fprintf(stdout, "Error: table full.\n");
            break;
        }
        case EXECUTE_DATABASE_FILE_NOT_LOADED:
        {
            fprintf(stderr, "Error. Database file is not loaded. Please run READ [<filename>.idb].\n");
            break;
        }
        default:
        {
            fprintf(stderr, "Error. Execute statement unrecognized return value.\n");
            exit(EXIT_FAILURE);
        }
    }
}
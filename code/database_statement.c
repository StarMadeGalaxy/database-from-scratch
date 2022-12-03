#include "database_statement.h"
#include "database_repl.h"
#include "database_cursor.h"


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
    DbCursor* cursor = table_end(table);

    PackageRow* row_to_insert = &(statement->row_to_insert);
    serialize_package_row(row_to_insert, cursor_value(cursor));
    table->num_rows += 1;

    free(cursor);
    return EXECUTE_SUCCESS;
    
}


internal PrepareStatementResult prepare_select(InputBuffer* input_buffer, Statement* statement)
{
    statement->type = STATEMENT_SELECT;
    return PREPARE_STATEMENT_SUCCESS;
}


internal ExecuteResult execute_select(Statement* statement, Table* table)
{
    DbCursor* cursor = table_start(table);

    PackageRow row;
    while (!(cursor->end_of_table))
    {
        deserialize_package_row(cursor_value(cursor), &row);
        print_package_row(&row);
        cursor_advance(cursor);
    }
    free(cursor);
    return EXECUTE_SUCCESS;
}

/* kind of compiler for SQL */
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
    return PREPARE_UNRECOGNIZED_STATEMENT;
}


internal ExecuteResult execute_statement(Statement* statement, Table* table)
{
    switch (statement->type)
    {
        case STATEMENT_SELECT:
        {
            return execute_select(statement, table);
        }
        case STATEMENT_INSERT:
        {
            return execute_insert(statement, table);
        }
    }
    return STATEMENT_UNRECOGNIZED; 
}
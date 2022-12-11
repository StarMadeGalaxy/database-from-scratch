#ifndef DATABASE_STATEMENT_H
#define DATABASE_STATEMENT_H

#include "database_base_types.h"
#include "database_package_row.h"


typedef enum PrepareStatementResult
{
    PREPARE_STATEMENT_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT,
    PREPARE_STRING_TOO_LONG,
    PREPARE_STRING_TOO_SHORT,
    PREPARE_UNRECOGNIZED_DATABASE_FILE,
    PREPARE_NEGATIVE_ID
} PrepareStatementResult;


typedef enum StatementType
{
    STATEMENT_INSERT,
    STATEMENT_SELECT,
    STATEMENT_READ,
    STATEMENT_UNRECOGNIZED
} StatementType;


typedef struct Statement
{
    StatementType type;
    PackageRow row_to_insert;
    char* filename; // mallocated
} Statement;


typedef enum ExecuteResult
{
    EXECUTE_TABLE_FULL, 
    EXECUTE_SUCCESS,
    EXECUTE_DATABASE_FILE_NOT_LOADED
} ExecuteResult;


internal PrepareStatementResult prepare_read(InputBuffer* input_buffer, Statement* statement);
internal ExecuteResult execute_read(Statement* statement, Table** table);

internal PrepareStatementResult prepare_insert(InputBuffer* input_buffer, Statement* statement);
internal ExecuteResult execute_insert(Statement* statement, Table* table);

internal PrepareStatementResult prepare_select(InputBuffer* input_buffer, Statement* statement);
internal ExecuteResult execute_select(Statement* statement, Table* table);

internal PrepareStatementResult prepare_statement(InputBuffer* input_buffer, Statement* statement);
internal ExecuteResult execute_statement(Statement* statement, Table** table);


#endif /* _DATABASE_STATEMENT_H */ 

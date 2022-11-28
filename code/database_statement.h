#ifndef _DATABASE_STATEMENT_H
#define _DATABASE_STATEMENT_H

#include "database_base_types.h"
#include "database_package_row.h"


typedef enum PrepareStatementResult
{
    PREPARE_STATEMENT_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT,
    PREPARE_STRING_TOO_LONG,
    PREPARE_NEGATIVE_ID
} PrepareStatementResult;


typedef enum StatementType
{
    STATEMENT_INSERT,
    STATEMENT_SELECT,
    STATEMENT_UNRECOGNIZED
} StatementType;


typedef struct Statement
{
    StatementType type;
    PackageRow row_to_insert;
} Statement;


typedef enum ExecuteResult
{
    EXECUTE_TABLE_FULL, EXECUTE_SUCCESS
} ExecuteResult;


internal PrepareStatementResult prepare_insert(InputBuffer* input_buffer, Statement* statement);
internal PrepareStatementResult prepare_statement(InputBuffer* input_buffer, Statement* statement);
internal ExecuteResult execute_insert(Statement* statement, Table* table);
internal ExecuteResult execute_select(Statement* statement, Table* table);
internal ExecuteResult execute_statement(Statement* statement, Table* table);


#endif /* _DATABASE_STATEMENT_H */ 

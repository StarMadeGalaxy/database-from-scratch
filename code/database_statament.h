#ifndef _DATABASE_STATEMENT_H
#define _DATABASE_STATEMENT_H


typedef enum
{
    PREPARE_STATEMENT_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareStatementResult;


typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;


typedef struct
{
    StatementType type;
} Statement;

/* kind of compiler for SQL */
PrepareStatementResult prepare_statement(InputBuffer* buffer, Statement* statement)
{
    return 0;
}


void execute_statement(Statement* statement)
{
    switch (statement->type)
    {
        case STATEMENT_SELECT:
        {
            puts("EXECUTE SELECT");
            break;
        }
        case STATEMENT_INSERT:
        {
            puts("EXECUTE INSERT");
            break;
        }
    }
}

#endif /* _DATABASE_STATEMENT_H */ 
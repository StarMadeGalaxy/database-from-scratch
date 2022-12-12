#if !defined(DATABASE_STATEMENT_H)
#define DATABASE_STATEMENT_H

#include "database_base_types.h"


// I have extremely enormous degree of doubts about forward decalration like that
// Should i include header instead or what?

typedef struct PackageRow PackageRow;
typedef struct InputBuffer InputBuffer;
typedef struct Table Table;

// So this is the first problem I encountered so far with forward decalaration
// I cannot figure why i have this kind of problem. I've heard that compiler must
// size of the PackageRow before compiling a that's the error appears, but so why
// do everything else not give me an error?
// Why is (typedef struct PackageRow PackageRow) not sufficient?
// (UPDATED): So problem dissappear when I disinclude it from database_raylib_gui.c
// and this is file is the first file being compiled. 
// I figure out that the compiler does not know the size of PackageRow at this point. 
// So in order to keep this file indepenent from includes (which is probably not the best idea)
// but unfortunately I have nobody to help me with this. Shouild go back to this problem after a little
// reasearch.


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
ExecuteResult execute_statement(Statement* statement, Table** table);

void execute_statement_result_message(ExecuteResult result);


#endif /* !defined(DATABASE_STATEMENT_H) */ 

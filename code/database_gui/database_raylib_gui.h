#if !defined(DATABASE_RAYLIB_GUI_H)
#define DATABASE_RAYLIB_GUI_H


typedef enum GuiQueryResult
{
    GUI_QUERY_ALLOC_FAILED,
    GUI_QUERY_SUCCESS,
    GUI_QUERY_DID_NOT_QUERY_SUCCESS
} GuiQueryResult;

typedef struct Table Table;


int raylib_start(Table** table, GuiQueryResult* query_status_out_result);


#endif // !defined(DATABASE_RAYLIB_GUI_H)
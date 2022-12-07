@ECHO OFF

CD ..

SET SRC=%cd%

:: Raylib pathways
SET RL_PATH=%SRC%\thirdparty\raylib
SET RL_BIN_PATH=%RL_PATH%\bin
SET RL_LIB_PATH=%RL_PATH%\lib
SET RL_INC_PATH=%RL_PATH%\include

:: Entry point
SET DB_ENTRY=%SRC%\code\database_entry_point.c

SET SNAKE_BUILD_OPTIONS=/DRELEASE_MODE /DGUI_DISABLED /DSNAKE_DOUBLY_LINKED_LIST
SET SNAKE_RENDERER=%SRC%\code\snake_game\code\snake_renderer_console.c

SET RL_DB_GUI=%SRC%\code\database_raylib_gui.c

SET CL_OPTS=/Zi /W3 /nologo /Od /wd5105 /std:c11
SET COMMON_LINK_FLAGS=/opt:ref user32.lib snake_renderer_console.lib %RL_LIB_PATH%\raylib.lib database_raylib_gui.obj
:: For snake game
SET CL_OPTS=/DRELEASE_MODE /DGUI_DISABLED /DSNAKE_DOUBLY_LINKED_LIST /D_CRT_SECURE_NO_WARNINGS %CL_OPTS%

IF NOT EXIST bulid MKDIR build
PUSHD build

:: The reason we renderer database raylib gui as a DLL is because I do not want to use cmake in this project,
:: and windows.h has a bunch of name conflicts with raylib.h so we isolate gui part
::cl %CL_OPTS% %RL_DB_GUI% /LD /Fedatabase_raylib_gui.dll /link %RL_LIB_PATH%\raylib.lib /opt:ref

cl /c %RL_DB_GUI% 

:: Compile snake renderer as a dll
cl %CL_OPTS% %SNAKE_RENDERER% /LD /Fesnake_renderer_console.dll /link user32.lib /opt:ref

:: Compile database and link the snake game and raylib
cl %CL_OPTS% %DB_ENTRY% /link %COMMON_LINK_FLAGS%

:: DEL *.ilk
DEL *.exp
DEL *.lib
DEL *.obj

:: Only in release mode
DEL *.pdb

POPD

CD code



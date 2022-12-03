@echo off

CD..

SET SRC=%cd%

SET SNAKE_BUILD_OPTIONS=/DRELEASE_MODE /DGUI_DISABLED /DSNAKE_DOUBLY_LINKED_LIST
SET DB_ENTRY=%SRC%\code\database_entry_point.c
SET SNAKE_RENDERER=%SRC%\code\snake_game\code\snake_renderer_console.c

SET CL_OPTS=/Zi /W3 /nologo /Od /wd5105 /std:c11
SET COMMON_LINK_FLAGS=/opt:ref user32.lib snake_renderer_console.lib
:: For snake game
SET BUILD_OPTIONS=/DRELEASE_MODE /DGUI_DISABLED /DSNAKE_DOUBLY_LINKED_LIST /D_CRT_SECURE_NO_WARNINGS /DDB_DEBU

IF NOT EXIST bulid MKDIR build
PUSHD build

:: Compile snake renderer as a dll
cl %CL_OPTS% /LD /Fesnake_renderer_console.dll %SNAKE_RENDERER% user32.lib

:: Compile and link the snake game
cl %BUILD_OPTIONS% %DB_ENTRY% %CL_OPTS% %ENTRY_FILE% /link %COMMON_LINK_FLAGS%

del *.ilk
del *.exp
del *.lib
:: del *.pdb
del *.obj

POPD

cd code



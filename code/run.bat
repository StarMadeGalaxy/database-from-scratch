@ECHO OFF

CD ..

SET SRC=%cd%
SET RL_PATH=%SRC%\thirdparty\raylib
SET RL_BIN_PATH=%RL_PATH%\bin

XCOPY /S %RL_BIN_PATH% build  

PUSHD build

START database_entry_point.exe

POPD

CD code
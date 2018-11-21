@ECHO OFF

CALL "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
CALL cl /EHsc /Fe:%0\..\console-assert.exe %0\..\main_win32.cpp
PAUSE

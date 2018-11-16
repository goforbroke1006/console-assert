@ECHO OFF

CALL "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
CALL cl /EHsc /Fe:%0\..\console-interaction-tester.exe C:\dev\projects\console-interaction-tester\main.cpp
PAUSE
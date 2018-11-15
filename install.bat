@ECHO OFF

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
call CL /EHsc /Fe:"%0\..\console-interaction-tester.exe" C:\dev\projects\console-interaction-tester\main.cpp
pause
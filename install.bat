@ECHO OFF

::call CL -I"C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Tools\MSVC\14.16.27023\include" main.cpp
::call CL -I"C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Tools\MSVC\14.16.27023\include" /MT /nologo /TP   /DWIN32 /D_WINDOWS /W3 /GR /EHsc /MDd /Zi /Ob0 /Od /RTC1 /showIncludes /FS -c C:\dev\projects\console-interaction-tester\main.cpp


::SET INCLUDE=";C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include;C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\atlmfc\include;C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include;C:\Program Files (x86)\Windows Kits\10\Include\10.0.17134.0\ucrt;"
::SET LIB=";C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\lib;C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\atlmfc\lib;C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib;C:\Program Files (x86)\Windows Kits\10\Lib\10.0.17134.0\ucrt\x64;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.16.27023\lib\x64;"

::call CL /EHsc -I"C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Tools\MSVC\14.16.27023\include" -I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.17134.0\ucrt" C:\dev\projects\console-interaction-tester\main.cpp
::call CL -I"%INCLUDE%" -L"%LIB%" /EHsc C:\dev\projects\console-interaction-tester\main.cpp
::call CL /EHsc C:\dev\projects\console-interaction-tester\main.cpp "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.16.27023\lib\x64\libcpmt.lib" "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.16.27023\lib\x64\libcmt.lib" "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.16.27023\lib\x64\oldnames.lib"
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
::call CL /EHsc /Fo%0\..\console-interaction-tester.exe C:\dev\projects\console-interaction-tester\main.cpp
call CL /EHsc /Fe:"%0\..\console-interaction-tester.exe" C:\dev\projects\console-interaction-tester\main.cpp
pause
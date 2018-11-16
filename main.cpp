#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <cstring>
#include <conio.h>

using namespace std;

#ifdef _WIN32

// From here https://stackoverflow.com/a/35658917/2048322

CStringA ExecCmd(const wchar_t* cmd) {
    CStringA strResult;
    HANDLE hPipeRead, hPipeWrite;

    SECURITY_ATTRIBUTES saAttr = { sizeof(SECURITY_ATTRIBUTES) };
    saAttr.bInheritHandle = TRUE;   //Pipe handles are inherited by child process.
    saAttr.lpSecurityDescriptor = NULL;

    // Create a pipe to get results from child's stdout.
    if ( !CreatePipe(&hPipeRead, &hPipeWrite, &saAttr, 0) )
        return strResult;

    STARTUPINFO si = { sizeof(STARTUPINFO) };
    si.dwFlags     = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.hStdOutput  = hPipeWrite;
    si.hStdError   = hPipeWrite;
    si.wShowWindow = SW_HIDE;       // Prevents cmd window from flashing. Requires STARTF_USESHOWWINDOW in dwFlags.

    PROCESS_INFORMATION pi  = { 0 };

    BOOL fSuccess = CreateProcessW( NULL, (LPWSTR)cmd, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
    if (! fSuccess)
    {
        CloseHandle( hPipeWrite );
        CloseHandle( hPipeRead );
        return strResult;
    }

    bool bProcessEnded = false;
    for (; !bProcessEnded ;)
    {
        // Give some timeslice (50ms), so we won't waste 100% cpu.
        bProcessEnded = WaitForSingleObject( pi.hProcess, 50) == WAIT_OBJECT_0;

        // Even if process exited - we continue reading, if there is some data available over pipe.
        for (;;)
        {
            char buf[1024];
            DWORD dwRead = 0;
            DWORD dwAvail = 0;

            if (!::PeekNamedPipe(hPipeRead, NULL, 0, NULL, &dwAvail, NULL))
                break;

            if (!dwAvail) // no data available, return
                break;

            if (!::ReadFile(hPipeRead, buf, min(sizeof(buf) - 1, dwAvail), &dwRead, NULL) || !dwRead)
                // error, the child process might ended
                break;

            buf[dwRead] = 0;
            strResult += buf;
        }
    } //for

    CloseHandle( hPipeWrite );
    CloseHandle( hPipeRead );
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
    return strResult;
}
#endif

int main(int argc, char **argv) {
    if (argc == 2 && (
            strcmp(argv[1], "?") == 0
            || strcmp(argv[1], "help") == 0
            || strcmp(argv[1], "-h") == 0
    )) {
        cout << "Usage: ./console-interaction-tester SOME_BIN_TEST_SUBJECT TEST_INPUT EXPECTED_OUTPUT";
        return 0;
    }

    string binFilename;
    string testInput;
    string expectedOutput;
    
    if (argc >= 4) {
        binFilename = argv[1];
        testInput = argv[2];
        expectedOutput = argv[3];
    } else {
        cout << "Enter subject binary path: ";
        getline(cin, binFilename);
        
        cout << "Enter test input: ";
        getline(cin, testInput);
        
        cout << "Enter expected output: ";
        getline(cin, expectedOutput);
    }

    FILE *fp;

    const char *pipeType = (testInput.length() > 0) ? "w" : "r";
    
#ifdef __linux__ 
    binFilename += " >/dev/null 2>&1";
    fp = popen(binFilename.c_str(), pipeType);
#elif _WIN32
    binFilename += " 2>&1";
    fp = _popen(binFilename.c_str(), pipeType);
#else
    cerr << "Only linux and win32 supported!";
    return -10;
#endif

    if (!fp) {
        std::cerr << "Couldn't start command." << std::endl;
        return -2;
    }

    //char outputBuff[2048];
    const size_t bufSize = 2048;
    std::array<char, bufSize> buffer;
    std::string result;
    
    if (testInput.length() > 0)
        fputs(testInput.c_str(), fp);
	
    //fscanf(fp, "%s", outputBuff);
    
    while (fgets(buffer.data(), bufSize, fp) != NULL) {
        std::cout << "Reading... " << buffer.data() << std::endl;
        result += buffer.data();
    }
	
	//string result;
	//const int max_buffer = 256;
	//char buffer[max_buffer];
	//while (!feof(fp))
	//	if (fgets(buffer, max_buffer, fp) != NULL) 
	//		result.append(buffer);
    
    fclose(fp);

    if (expectedOutput == result) {
    //if (strcmp(expectedOutput.c_str(), outputBuff) == 0) {
        cout << "OK" << endl;
        return 0;
    } else {
        cerr << "Assertion failed!" << endl;
        cerr << "Expected: " << expectedOutput
             << endl
             << "Actual:   " << result 
             << endl;
        return -100;
    }
    
    if (argc < 4) {
        getch();
    }
}

#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <cstring>

#include <sys/prctl.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <wait.h>

#ifdef _WIN32

#include <conio.h>

#endif

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

int main12345(int argc, char **argv) {
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


    pid_t pid1 = 0;
    pid_t pid2 = 0;
    int fd[3];
    char buf[2048];
//    char msg[256];
    int status;

    pipe(fd);

    pid1 = fork();
    if (pid1 == 0) {
        // Child
        dup2(fd[0], STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        dup2(fd[2], STDERR_FILENO);
        close(fd[0]);
        close(fd[1]);
        close(fd[2]);
        execlp(binFilename.c_str(), binFilename.c_str(), nullptr, (char *) NULL);
        exit(1);
    } else if (pid1 > 0) {
        printf("On parent\n");
    } else if (pid1 < 0) {
        printf("Fork has failed\n");
    }

    pid2 = fork();
    if (pid2 == 0) {
        // Child
        dup2(fd[0], STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        dup2(fd[2], STDERR_FILENO);
        close(fd[0]);
        close(fd[1]);
        close(fd[2]);
        execlp(binFilename.c_str(), binFilename.c_str(), nullptr, (char *) NULL);
        exit(1);
    } else if (pid2 > 0) {
        printf("On parent\n");
    } else if (pid2 < 0) {
        printf("Fork has failed\n");
    }

    /*else                                         //
    {                                            //
        pid2 = fork();                             //
        //
        if (pid2 == 0)                              //
        {                                        // I am going to be the ls process (i.e. producing output to the pipe)
//            close(fd[OUTPUT_END]);               // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[0] -> pipe_input] (of the ls process)
            dup2(fd[0], STDIN_FILENO);
            dup2(fd[1], STDOUT_FILENO);
            dup2(fd[2], STDERR_FILENO);
            execlp(binFilename.c_str(), binFilename.c_str(), nullptr, (char *) NULL);
        }                                        //
        //

        // At this point we can safely assume both process are completed
    }*/
    // The code below will be executed only by parent. You can write and read
    // from the child using pipefd descriptors, and you can send signals to
    // the process using its pid by kill() function. If the child process will
    // exit unexpectedly, the parent process will obtain SIGCHLD signal that
    // can be handled (e.g. you can respawn the child process).

    //close unused pipe ends
//    close(outpipefd[1]);
//    close(inpipefd[1]);

    // Now, you can write to outpipefd[1] and read from inpipefd[0] :
    /*while(1)
    {
        printf("Enter message to send\n");
        scanf("%s", msg);
        if(strcmp(msg, "exit") == 0) break;

        write(outpipefd[1], msg, strlen(msg));
        read(inpipefd[0], buf, 256);

        printf("Received answer: %s\n", buf);
    }*/

//    cout << "Start writing..." << endl;
//    cout << "<<< " << testInput << endl;
    write(fd[0], testInput.c_str(), strlen(testInput.c_str()));

//    cout << "Start reading..." << endl;
    while (read(fd[1], buf, 2048) > 0) {
        cout << ">>> " << buf << endl;
    }

    close(fd[1]);                   // [STDIN -> terminal_input, STDOUT -> terminal_output, fd[0] -> pipe_input] (of the parent process)
    close(fd[0]);                    // [STDIN -> terminal_input, STDOUT -> terminal_output]                      (of the parent process)
    waitpid(-1, NULL,
            0);                    // As the parent process - we wait for a process to die (-1) means I don't care which one - it could be either ls or wc
    waitpid(-1, NULL, 0);                    // As the parent process - we wait for the another process to die.

//    kill(pid, SIGKILL); //send SIGKILL signal to the child process
//    waitpid(pid, &status, 0);






//    if (expectedOutput == result) {
    if (strcmp(expectedOutput.c_str(), buf) == 0) {
        cout << "OK" << endl;
        return 0;
    } else {
        cerr << "Assertion failed!" << endl;
        cerr << "Expected: " << expectedOutput
             << endl
             << "Actual:   " << buf
             << endl;
        return -100;
    }

    if (argc < 4) {
#ifdef _WIN32

        getch();

#endif

    }
}


#define INPUT_END 1                              // INPUT_END means where the pipe takes input
#define OUTPUT_END 0

int main(int argc, char *argv[])                 //
{
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


    char buf[2048];
    ssize_t resLen = -1;

    pid_t pid1;
    pid_t pid2;
    int fd1[2];
    int fd2[2];

    string result;

    pipe(fd1);
    pid1 = fork();
    if (pid1 == 0) {
//        close(fd1[INPUT_END]);
//        dup2(fd1[OUTPUT_END], STDIN_FILENO);
//        close(fd1[OUTPUT_END]);
//
        close(fd1[OUTPUT_END]);
        dup2(fd1[INPUT_END], STDOUT_FILENO);
        close(fd1[INPUT_END]);

//        execlp("echo", "echo", "hello1", (char *) NULL);   //
        execlp("dec2bin", "dec2bin", (char *) NULL);   //
//        execlp(binFilename.c_str(), binFilename.c_str(), "?", (char *) NULL);

    } else {
        pipe(fd2);
        pid2 = fork();
        if (pid2 == 0) {
            close(fd2[OUTPUT_END]);
            dup2(fd2[INPUT_END], STDOUT_FILENO);
            close(fd2[INPUT_END]);
//            execlp("echo", "echo", "hello2", (char *) NULL);
            execlp("dec2bin", "dec2bin", (char *) NULL);
        }

        if (resLen == -1) {
            write(fd2[INPUT_END], testInput.c_str(), strlen(testInput.c_str()));
            resLen = read(fd2[OUTPUT_END], buf, 2048);
        }

//        close(fd2[OUTPUT_END]);
//        close(fd2[INPUT_END]);
//        waitpid(-1, NULL, 0);
//        waitpid(-1, NULL, 0);
    }

    if (resLen == -1) {
        write(fd1[INPUT_END], testInput.c_str(), strlen(testInput.c_str()));
        resLen = read(fd1[OUTPUT_END], buf, 2048);
    }

//    cout << testInput.c_str();
//    cin >> buf;

//    kill(pid1, SIGKILL);
//    kill(pid2, SIGKILL);
//    int status = 0;
//    waitpid(pid1, &status, 0);
//    cout << "finish with response: " << status << endl;

    if (resLen <= 0) {
        cerr << "Empty response";
        return -1;
    }

    result = buf;
    result = result.substr(0, resLen);

    if (expectedOutput == result) {
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
}
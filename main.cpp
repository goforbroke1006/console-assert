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

    } /*else {
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
    }*/

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

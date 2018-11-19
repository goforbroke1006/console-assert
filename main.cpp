#include <iostream>
#include <zconf.h>
#include <sys/wait.h>
#include <cstring>

#define PIPE_READ 0
#define PIPE_WRITE 1

using namespace std;

int main() {

    int inputFd[2];
    int outputFd[2];
    char nChar;

    if (pipe(inputFd) < 0) {
        perror("input pipe");
        exit(EXIT_FAILURE);
    }

    if (pipe(outputFd) < 0) {
        close(inputFd[PIPE_READ]);
        close(inputFd[PIPE_WRITE]);
        perror("output pipe");
        exit(EXIT_FAILURE);
    }

    pid_t childPid = fork();
    if (childPid < 0) {
        close(inputFd[PIPE_READ]);
        close(inputFd[PIPE_WRITE]);
        close(outputFd[PIPE_READ]);
        close(outputFd[PIPE_WRITE]);
        perror("fork() error");
        exit(-1);
    }

    string result;

    if (childPid == 0) {
        printf("I'm child %d, parent is %d\n", getpid(), getppid());

        if (dup2(inputFd[PIPE_READ], STDIN_FILENO) == -1) { // redirect stdin
            exit(errno);
        }
        if (dup2(outputFd[PIPE_WRITE], STDOUT_FILENO) == -1) { // redirect stdout
            exit(errno);
        }
        if (dup2(outputFd[PIPE_WRITE], STDERR_FILENO) == -1) { // redirect stderr
            exit(errno);
        }
        close(inputFd[PIPE_READ]);
        close(inputFd[PIPE_WRITE]);
        close(outputFd[PIPE_READ]);
        close(outputFd[PIPE_WRITE]);

        const char *szCommand = "/home/goforbroke/CLionProjects/console-interaction-tester/cmake-build-debug/dec2bin";
        char *const aArguments[] = {"dec2bin", NULL};
        char *const aEnvironment[] = {NULL};
        int nResult = execve(szCommand, aArguments, aEnvironment);
        exit(nResult);
    } else {
        printf("I'm paretn %d, child is %d\n", getpid(), childPid);

        close(inputFd[PIPE_READ]);
        close(outputFd[PIPE_WRITE]);

        printf("Child ready for input\n");
        const char *input = "32\n";
        write(inputFd[PIPE_WRITE], input, strlen(input));
        while (read(outputFd[PIPE_READ], &nChar, 1) == 1) {
            result += nChar;
        }
    }

    int status = 0;
    waitpid(childPid, &status, WUNTRACED);
    printf("Child finish with status %d\n", status);
    printf("Child out data: %s\n", result.c_str());

    return 0;
}

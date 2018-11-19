#include <iostream>
#include <zconf.h>
#include <sys/wait.h>
#include <cstring>

static const int BUF_SIZE = 2048;

int main() {

    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t childPid = fork();
    if (childPid < 0) {
        perror("fork() error");
        exit(-1);
    }

    char buf[BUF_SIZE];

    if (childPid > 0) {
        printf("I'm paretn %d, child is %d\n", getpid(), childPid);

        const char *input = "Hello, World!";
        write(fd[1], input, strlen(input));

        wait(NULL);

        ssize_t resLen = read(fd[0], &buf, BUF_SIZE);
        if (resLen > 0) {
            printf("Child say: %s", buf);
        }

        close(fd[1]);
        close(fd[0]);
        exit(EXIT_SUCCESS);
    } else {
        printf("I'm child %d, parent is %d\n", getpid(), getppid());
        execl("/bin/echo", "echo", "Hello, World!", NULL);
    }

    wait(NULL);

    return 0;
}

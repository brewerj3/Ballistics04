#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include "man.h"

int main() {
    pid_t pid;

    // @TODO make the pipes for the manager and host here



    pid = fork();

    if(pid == -1) {
        printf("Error: the fork() failed\n");
        return 0;
    } else if(pid == 0) { // The child process
        host_main();    // @TODO Implement the host routine
        return 0;
    }

    // Parent process executes manager routine
    man_main();

    // If user quits manager routine, kill all child processes
    kill(0, SIGKILL);   // @TODO Implement the manager routine
    return 0;
}

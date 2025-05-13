#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        printf("I'm child process!\n");    
    } else {
        printf("I'm parent process!\n");
        wait(NULL);
    }
    
    return 0;
}

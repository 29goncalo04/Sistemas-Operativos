#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    
    pid_t pid_filho = fork(), status;

    if(pid_filho == 0){
        //processo-filho
        printf("[filho] PID: %d PID pai: %d\n", getpid(), getppid());
        _exit(0);
    } else{
        //processo-pai
        printf("[pai] PID: %d PID pai: %d, PID filho: %d\n", getpid(), getppid(), pid_filho);
        wait(&status);
        if(WIFEXITED(status)) printf("[pai]: processo filho terminou normalmente com %d.\n", WEXITSTATUS(status));
        else printf("[pai]: processo filho não terminou normalmente.\n");
    }

    return 0;
}
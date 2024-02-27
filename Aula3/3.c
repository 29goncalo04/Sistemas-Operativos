#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    
    for(int i = 1; i<=10; i++){
        pid_t pid_filho = fork();
        int status;
        if(pid_filho == 0){  //é filho
            printf("[filho%d] PID: %d PID pai: %d\n", i, getpid(), getppid());
            _exit(i);
        }
        else{
            wait(&status);
            if(WIFEXITED(status)) printf("[pai] processo filho terminou normalmente com %d\n", WEXITSTATUS(status));
            else printf("[pai] processo filho não terminou normalmente\n");
        } 
    }

    return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int status;
    pid_t pid_filho = fork();
    if(pid_filho == 0){  //processo-filho
        printf("[Filho] Meu PID %d e PID do meu pai %d\n", getpid(), getppid());
        _exit(0);
    }
    int aux = wait(&status);
    if(WIFEXITED(status)) printf("[Pai] Meu PID %d, PID do meu pai %d e PID do meu filho %d\n", getpid(), getppid(), aux);
    return 0;
}

// int main(int argc, char* argv[]){
//     pid_t pid_filho = fork(), status;
//     if(pid_filho == 0){
//         //processo-filho
//         printf("[filho] PID: %d PID pai: %d\n", getpid(), getppid());
//         _exit(0);
//     } else{
//         //processo-pai
//         printf("[pai] PID: %d PID pai: %d, PID filho: %d\n", getpid(), getppid(), pid_filho);
//         wait(&status);
//         if(WIFEXITED(status)) printf("[pai]: processo filho terminou normalmente com %d.\n", WEXITSTATUS(status));
//         else printf("[pai]: processo filho não terminou normalmente.\n");
//     }
//     return 0;
// }
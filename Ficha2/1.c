#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int agrc, char* argv[]){
    int status;
    pid_t pid = fork();
    if(pid == 0){
        printf("Sou o filho com PID %d\n", getpid());
        printf("Pai com PID %d\n", getppid());
        _exit(0);
    }
    wait(&status);
    return 0;
}

// int main(int argc, char* argv[]){
//     printf("PID: %d PID pai: %d\n", getpid(), getppid());
//     return 0;
// }
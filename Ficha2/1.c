#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    
    printf("PID: %d PID pai: %d\n", getpid(), getppid());

    return 0;
}
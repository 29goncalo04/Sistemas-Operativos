#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int pid, status;
    pid = fork();
    switch(pid){
        case -1:
            perror("fork");
            break;
        case 0:
            if (execlp("ls", "/bin/ls", "-l", NULL) == -1) perror("execl");
            _exit(-1);

        default:
            wait(&status);
            if(WIFEXITED(status)){
                printf("Filho terminou com %d\n", WEXITSTATUS(status));
            }
    }

    return 0;
}
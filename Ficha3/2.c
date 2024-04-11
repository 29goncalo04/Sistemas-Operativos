#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int status;
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        return -1;
    }
    if(pid == 0){ //processo-filho
        if(execlp("ls", "ls", "-l", NULL) == -1){   // ou ->  if(execl("/bin/ls", "ls", "-l", NULL) == -1)
            perror("execlp");
            _exit(-1);
        }
        _exit(0);
    }
    wait(&status);
    if(WIFEXITED(status)) printf("Filho de PID terminou com %d\n", WEXITSTATUS(status));
    return 0;
}

// int main(int argc, char* argv[]){
//     int pid, status;
//     pid = fork();
//     switch(pid){
//         case -1:
//             perror("fork");
//             break;
//         case 0:
//             if (execlp("ls", "/bin/ls", "-l", NULL) == -1) perror("execl");
//             _exit(-1);
//         default:
//             wait(&status);
//             if(WIFEXITED(status)){
//                 printf("Filho terminou com %d\n", WEXITSTATUS(status));
//             }
//     }
//     return 0;
// }
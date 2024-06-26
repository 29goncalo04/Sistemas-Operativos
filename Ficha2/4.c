#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int agrc, char* argv[]){
    int status, codigos[10];
    for(int i = 0; i<10; i++){
        pid_t pid_filho = fork();
        if(pid_filho == 0){
            printf("[Filho%d]\n]",i+1);
            _exit(i+1);
        }
    }
    for(int i = 0; i<10; i++){
        wait(&status);
        if(WIFEXITED(status)) codigos[i] = WEXITSTATUS(status);
    }
    printf("\n[Pai] ");
    for(int i = 0; i<10; i++){
        printf("%d ", codigos[i]);
    }
    printf("\n");
    return 0;
}

// int main(int argc, char* argv[]){
//     int status, terminacao[10];
//     for(int i = 1; i<=10; i++){
//         pid_t pid_filho = fork();  //cria um processo-filho
//         if(pid_filho == 0){
//             //processo-filho faz a sua tarefa
//             printf("Processo-filho %d com PID %d criado\n", i, getpid());
//             _exit(i);
//         }
//     }
//     //printf("Todos criados\n");
//     for(int i = 1; i<=10; i++){
//         wait(&status);
//         terminacao[i-1] = WEXITSTATUS(status);
//     }
//     printf("\n");
//     for(int i = 1; i<=10; i++){
//         if(WIFEXITED(status)) printf("Processo filho %d terminou com o código de terminação %d\n", i, terminacao[i-1]);
//     }
//     printf("\nProcesso-pai terminado\n");
//     return 0;
// }
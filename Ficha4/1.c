#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int file[2], num = 10;
    if(pipe(file) == -1){
        perror("pipe");
        return -1;
    }
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        return -1;
    }
    if(pid == 0){  //processo-filho
        close(file[1]);
        int num_read;
        read(file[0], &num_read, sizeof(int));
        close(file[0]);
        printf("[FILHO] -> Li %d do pipe\n", num_read);
        _exit(0);
    }
    close(file[0]);
    sleep(3);
    write(file[1], &num, sizeof(int));
    close(file[1]);
    printf("[PAI] -> Escrevi %d para o pipe\n", num);
    wait(NULL);
    return 0;
}

// int main(int agrc, char* argv[]){
//     int pd[2], num = 10;
//     if(pipe(pd) == -1){
//         perror("pipe");
//         return -1;
//     }
//     int fork_ret = fork();
//     if(fork_ret == -1){
//         perror("fork");
//     } else if(fork_ret == 0){
//         //filho
//         close(pd[1]);
//         int num_read;
//         read(pd[0], &num_read, sizeof(int));
//         printf("[FILHO]: li %d do pipe\n", num_read);
//         close(pd[0]);
//         _exit(0);
//     }
//     else{
//         //pai
//         close(pd[0]);
//         sleep(5);
//         write(pd[1], &num, sizeof(int));
//         printf("[PAI]: escrevi %d para o pipe\n", num);
//         close(pd[1]);
//         wait(NULL);
//     }
//     return 0;
// }
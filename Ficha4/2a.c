#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int file[2];
    if(pipe(file) == -1){
        perror("pipe");
        return -1;
    }
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        return -1;
    }
    if(pid == 0){
        close(file[0]);
        for(int i = 0; i<10; i++){
            write(file[1], &i, sizeof(int));
            printf("[FILHO] -> Escrevi %d para o pipe\n", i);
        }
        close(file[1]);
        _exit(0);
    }
    int num_read;
    close(file[1]);
    sleep(3);
    for(int i = 0; i<10; i++){
        read(file[0], &num_read, sizeof(int));
        printf("[PAI] -> Li %d do pipe\n", num_read);
    }
    close(file[0]);
    wait(NULL);
    return 0;
}

// int main (int argc, char* argv[]) {
//     int pd[2];
//     int num = 10;
//     if (pipe(pd) == -1) {
//         perror ("pipe");
//         return -1;
//     }
//     int fork_ret = fork();
//     if (fork_ret == -1) {
//         perror ("fork");
//         return -1;
//     }
//     else if (fork_ret == 0){
//         // filho
//         close (pd[0]);
//         write (pd[1], &num, sizeof(int));
//         printf ("[FILHO]: escrevi %d para o pipe\n", num);
//         close (pd[1]);
//         _exit (0);
//     }
//     else{
//         // pai
//         close (pd[1]);
//         // sleep (4);  // b)
//         int num_read;
//         read (pd[0], &num_read, sizeof(int));
//         printf ("[PAI]: li %d do pipe\n", num_read);
//         close (pd[0]); 
//         wait(NULL);
//     }
//     return 0;
// }
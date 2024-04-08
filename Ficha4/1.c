#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int agrc, char* argv[]){
    int pd[2], num = 10;
    if(pipe(pd) == -1){
        perror("pipe");
        return -1;
    }
    int fork_ret = fork();
    if(fork_ret == -1){
        perror("fork");
    } else if(fork_ret == 0){
        //filho
        close(pd[1]);
        int num_read;
        read(pd[0], &num_read, sizeof(int));
        printf("[FILHO]: li %d do pipe\n", num_read);
        close(pd[0]);
        _exit(0);
    }
    else{
        //pai
        close(pd[0]);
        sleep(5);
        write(pd[1], &num, sizeof(int));
        printf("[PAI]: escrevi %d para o pipe\n", num);
        close(pd[1]);
        wait(NULL);
    }
    return 0;
}
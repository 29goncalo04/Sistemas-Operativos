

//NÃO ESTÁ TUDO PASSADO


#include <stdio.h>
#include "mysystem.h"

void controller(int N, char** commands){
    int fork_ret, status;
    int pids[N];
    for(int i = 0; i<N; i++){
        fork_ret = fork();
        if(fork_ret == 0){
            int counter = 0;
            int res = -1;
            while(res!=0){
                res = mysystem(commands[i]);
                counter++;
            }
            _exit(counter);
        }
        else{
            pids[i] = fork_ret;
        }
    }

    for(int i = 0; i<N; i++){
        waitpid(pids[i], &status, 0);
    }
}
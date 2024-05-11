#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main (int argc, char* argv[]){
    int p[2];
    pid_t pid;
    if(pipe(p) == -1) perror("pipe");
    if((pid = fork()) == -1){
        perror("fork");
    }
    else{
        if(pid == 0){
            close(p[0]);
            dup2(p[1], 1);
            close(p[1]);
            int exec_ret = execlp("ls", "ls", "/etc/", NULL);
            if(exec_ret == -1){
                perror("exec");
                _exit(-1);
            }
        }
        else{
            close(p[1]);
            if((pid = fork()) == -1){
                perror("fork");
            }
            else{
                if(pid == 0){
                    dup2(p[0], 0);
                    close(p[0]);
                    int exec_ret = execlp("wc", "wc", "-l", NULL);
                    if(exec_ret == -1){
                        perror("exec");
                        _exit(-1);
                    }
                }
                else{
                    close(p[0]);
                    for(int i = 0; i<2; i++){
                        wait(NULL);
                    }
                }
            }
        }
    }
    return 0;
}
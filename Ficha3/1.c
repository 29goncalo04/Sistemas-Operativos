#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    if(execlp("ls", "ls", "-l", NULL) == -1){
        perror("execlp");
        return -1;
    }
    return 0;
}
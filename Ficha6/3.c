#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int args, char* argv[]) {
    int fdin = open("/etc/passwd", O_RDONLY);
    int fdout = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0640);
    int fderr = open("erros.txt", O_WRONLY | O_CREAT | O_TRUNC, 0640);
    
    int out = dup(1);

    dup2(fdin, 0);
    close(fdin);

    dup2(fdout, 1);
    close(fdout);

    dup2(fderr, 2);
    close(fderr);


    execlp("wc", "wc", NULL);
    dup2(out, 1);
    printf("terminei");
    return 0;
}
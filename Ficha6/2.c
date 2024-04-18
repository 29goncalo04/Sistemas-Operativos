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


    int fork_ret = fork();
    if (fork_ret == -1) {
        perror ("fork");
    }
    else if (fork_ret == 0) {
        int bytes_read;
        char buf[1024];
        while ((bytes_read = read(0, buf, sizeof(buf))) > 0) {
            write(1, buf, bytes_read);
        }
    }
    else {
        dup2(out,1);
        printf("terminei\n");
    }
    return 0;
}
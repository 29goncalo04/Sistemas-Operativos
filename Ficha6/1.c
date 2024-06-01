#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    int input = open("/etc/passwd", O_RDONLY);
    int output = open("saida.txt", O_CREAT | O_WRONLY | O_TRUNC, 0600);
    int error = open("erros.txt", O_CREAT | O_WRONLY | O_TRUNC, 0600);
    int out = dup(1);
    dup2(input, 0);
    close(input);
    dup2(output, 1);
    close(output);
    dup2(error, 2);
    close(error);
    dup2(out, 1);
    printf("terminei\n");
    close(out);
    return 0;
}
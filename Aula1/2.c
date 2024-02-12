#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    
    char buffer[10];
    int bytes_read;

    int fd_origin = open(argv[1], O_RDONLY);
    int fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0640);

    while((bytes_read = read(fd_origin, buffer, 10)) > 0){
        write(fd_dest, buffer, bytes_read);
    }

    return 0;
}
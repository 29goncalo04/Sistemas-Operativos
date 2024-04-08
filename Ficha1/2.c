#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    char buffer[100];
    int file1 = open(argv[1], O_CREAT | O_RDONLY,0600);
    int file2 = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0600);
    int bytes_read;
    while((bytes_read = read(file1, buffer, 100) > 0)){
        write(file2, buffer, bytes_read);
    }
    close(file1);
    close(file2);
    return 0;
}

//  0600: O arquivo tem permissão de leitura e gravação apenas para o proprietário 
    // e nenhum acesso para o grupo ou outros usuários.
//  0640: O arquivo tem permissão de leitura e gravação para o proprietário
    // permissão de leitura para o grupo e nenhum acesso para outros usuários.


// int main(int argc, char* argv[]){
//     char buffer[10];
//     int bytes_read;
//     int fd_origin = open(argv[1], O_RDONLY);
//     int fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0640);
//     while((bytes_read = read(fd_origin, buffer, 10)) > 0){
//         write(fd_dest, buffer, bytes_read);
//     }
//     return 0;
// }
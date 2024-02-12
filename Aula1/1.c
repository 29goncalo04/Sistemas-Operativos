#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

// int main(int argc, char* argv[]){
//     char buffer[10];
//     read(0, buffer, 10);
//     buffer[9] = '\0';
//     printf("%s", buffer);
//     return 0;
// }

int main(int argc, char* argv[]){
    
    char buffer[10];
    int bytes_read;

    while((bytes_read = read(0, buffer, 10)) > 0){
        write(1, buffer, bytes_read);
    }

    return 0;
}
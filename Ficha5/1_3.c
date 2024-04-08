#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#define BSIZE 20

int main() {
    char buf [BSIZE];
    int bytes_read, fd;
    fd = open("fifo", O_RDONLY);
    printf ("opened fifo for reading\n");
    while ((bytes_read = read (fd, buf, BSIZE)) > 0) {
        write (1, buf, bytes_read);
    }
    close (fd);
    return 0;
}
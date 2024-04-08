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
    fd = open("fifo", O_WRONLY);
    printf ("opened fifo for writing\n");
    while ((bytes_read = read (0, buf, BSIZE)) > 0) {
        int w = write (fd, buf, bytes_read);
    }
    close (fd);
    return 0;
}
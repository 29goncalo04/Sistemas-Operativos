#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <sys/wait.h>

int main (int argc, char* argv[]) {
    
    int pd[2];
    int num = 10;

    if (pipe(pd) == -1) {
        perror ("pipe");
        return -1;
    }

    int fork_ret = fork();
    if (fork_ret == -1) {
        perror ("fork");
        return -1;
    }
    else if (fork_ret == 0) {
        // filho
        close (pd[0]);
        for (int i=0; i<10; i++) {
            write (pd[1], &i, sizeof(int));
            printf ("[FILHO]: escrevi %d para o pipe\n", i);
        }
        close (pd[1]);
        _exit (0);
    }
    else {
        // pai
        close (pd[1]);
        sleep (4);  // b)
        int num_read, bytes_read;
        while ((bytes_read = read (pd[0], &num_read, sizeof(int))) > 0) {
            printf ("[PAI]: li %d do pipe\n", num_read);
        }
        close (pd[0]); 
        wait(NULL);
    }

    return 0;
}
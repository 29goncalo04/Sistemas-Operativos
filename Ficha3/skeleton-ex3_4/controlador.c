#include <stdio.h>
#include "mysystem.h"

void controller(int N, char** commands) {
	int pids[N], status;
	for(int i = 0; i<N; i++){
		pid_t pid = fork();
		if(pid == -1){
			perror("fork");
			return;
		}
		if(pid == 0){
			int resultado = -1;
			int contador = 0;
			while(resultado!=0){
				resultado = mysystem(commands[i]);
				contador++;
			}
			exit(contador);    //a função "_exit" só consegue receber um número até 255 por isso neste caso não iria funcionar
		}
		pids[i] = pid;
	}
	for(int i = 0; i<N; i++){
		waitpid(pids[i], &status, 0);
		if(WIFEXITED(status)) printf("%s -> %d\n", commands[i], WEXITSTATUS(status));
	}
}

int main(int argc, char* argv[]) {

    char *commands[argc-1];
    int N = 0;
	for(int i=1; i < argc; i++){
		commands[N] = strdup(argv[i]);
		printf("command[%d] = %s\n", N, commands[N]);
        N++;
	}

    controller(N, commands);

	return 0;
}
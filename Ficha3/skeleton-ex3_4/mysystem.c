#include "mysystem.h"

// recebe um comando por argumento
// retorna -1 se o fork falhar
// caso contrario retorna o valor do comando executado

int mysystem(const char *command){
	char* cmd = strdup(command);
	char* string = NULL;
	int i = 0, status;
	char* args[20];
	while((string = strsep(&cmd, " ")) != NULL){
		args[i] = string;
		i++;
	}
	args[i] = NULL;
	pid_t pid = fork();
	if(pid == -1){
		perror("fork");
		return -1;
	}
	if(pid == 0){
		execvp(args[0], args);
		perror("execvp");
		_exit(127);    //apenas caso o execvp dê errado
	}
	wait(&status);
	if(WIFEXITED(status)) return WEXITSTATUS(status);
	return -1;
} 

// int mysystem (const char* command) {
// 	int res = -1, fork_ret, exec_ret, status;
// 	char* exec_args[20];
// 	char* string = NULL;
// 	int i = 0;
// 	char* cmd = strdup(command);
// 	while((string = strsep(&cmd, " ")) != NULL){
// 		exec_args[i] = string;
// 		i++;
// 	}
// 	exec_args[i] = NULL;
// 	fork_ret = fork();
// 	if(fork_ret == 0){
// 		execvp(exec_args[0], exec_args);
// 		_exit(127);
// 	}
// 	else{
// 		wait(&status);
// 		if(WIFEXITED(status)){
// 			return exec_ret = WEXITSTATUS(status);
// 		}
// 		else{
// 			res = -1;
// 		}
// 		if(fork_ret == -1){
// 			res = -1;
// 		}
// 	}
// 	return res;
// }
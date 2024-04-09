#include "matrix.h"

int **createMatrix() {
    // seed random numbers
    srand(time(NULL));
    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **) malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");
    return matrix;
}

void printMatrix(int **matrix) {
    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// ex.5
int valueExists(int **matrix, int value) {
    int status;
    int codigos[COLUMNS];
    for(int i = 0; i<COLUMNS; i++){
        pid_t pid_filho = fork();
        if(pid_filho == 0){
            for(int j = 0; j<ROWS; j++){
                if(value == matrix[j][i]) _exit(j);
            }
            _exit(-1);    //vai retornar o valor 255         
        }
    }
    for(int i = 0; i<COLUMNS; i++){
        wait(&status);
        if(WIFEXITED(status)) codigos[i] = WEXITSTATUS(status);
        else codigos[i] = 255;  //erro
    }
    int res = codigos[0];
    for(int i = 0; i<COLUMNS; i++){
        if(codigos[i]<res) res = codigos[i];
    }
    if(res == 255) return -1;
    return res;
}

// int valueExists(int **matrix, int value) {  
//     for (int i=0;i<ROWS; i++) {
//         pid_t pid_f = fork();
//         if (pid_f == -1) {
//             perror ("fork");
//             return -1;
//         }
//         else if (pid_f == 0) {
//             // processo filho
//             for (int j=0; j<COLUMNS; j++) {
//                 if (matrix[i][j] == value) {
//                     _exit (i);
//                 }
//             }
//             _exit (-1);
//         }
//     }
//     for (int i=0; i<ROWS; i++) {
//         int status;
//         // processo pai
//         pid_t pid_f = wait(&status);
//         if (pid_f == -1) {
//             perror ("wait");
//             return -1;
//         }
//         if (WIFEXITED(status)) {
//             if (WEXITSTATUS(status) < 255) {
//                 return WEXITSTATUS(status);
//             }
//         }
//     }
//     return -1;
// }

// ex.6
void linesWithValue(int **matrix, int value) {
    int status, codigos[COLUMNS];
    for(int i = 0; i<COLUMNS; i++){
        pid_t pid_filho = fork();
        if(pid_filho == 0){
            for(int j = 0; j<ROWS; j++){
                if(matrix[j][i] == value) _exit(j);
            }
            _exit(-1);  //sai com valor 255
        }
    }
    for(int i = 0; i<COLUMNS; i++){
        wait(&status);
        if(WIFEXITED(status)) codigos[i] = WEXITSTATUS(status);
    }
    int min = 255;
    for(int i = 0; i<COLUMNS; i++){
        for(int j = i; j<COLUMNS; j++){
            if(codigos[j]<min){
                min = codigos[j];
                codigos[j] = codigos[i];
                codigos[i] = min;
            }
        }
        min = 255;
    }
    if(codigos[0] == 255){
        printf("Não existem ocorrências desse número\n");
        return;
    }
    printf("Este número está presenta nas linhas: ");
    for(int i = 0; i<COLUMNS && codigos[i]!=255; i++) printf("%d ", codigos[i]);
    printf("\n");
}
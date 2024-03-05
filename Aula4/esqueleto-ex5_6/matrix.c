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

    int ret = -1;
    for(int i = 0; i<ROWS; i++){
        pid_t pid_filho = fork();

        if(pid_filho == -1){
            perror("fork");
            return -1;
        }
        if(pid_filho == 0){   //processo-filho
            for(int j = 0; j<COLUMNS; j++){
                if(matrix[i][j] == value){
                    _exit(i+1);
                }
            }
            _exit(0);
        }
    }
    for(int i = 0; i<ROWS; i++){
        int status;
        //processo-pai
        pid_t pid_filho = wait(&status);
        if(pid_filho == -1){
            perror("wait");
            return -1;
        }
        if(WIFEXITED(status)){
            if(WEXITSTATUS(status) != 0) ret = 1;
        }
    }

    return ret;
}


// ex.6
void linesWithValue(int **matrix, int value) {

    
}
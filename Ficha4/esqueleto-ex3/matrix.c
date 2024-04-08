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

void lookupNumber(int** matrix, int value, int* vector){
    int p[2], pid;
    pipe(p);
    for(int r = 0; r<ROWS; r++){
        if((pid = fork()) == 0){
            Minfo m;
            m.line_nr = r;
            m.ocur_nr = 0;
            for(int j = 0; j<COLUMNS; j++){
                if(matrix[r][j] == value) m.ocur_nr++;
            }
            write(p[1], &m, sizeof(Minfo));
            close(p[1]);
            _exit(0);
        }
    }
    close(p[1]);
    Minfo resp;
    while(read(p[0], &resp, sizeof(Minfo)) > 0){
        vector[resp.line_nr] = resp.ocur_nr;
    }
}
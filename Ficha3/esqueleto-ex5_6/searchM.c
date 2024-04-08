#include "matrix.h"


int main(int argc, char *argv[]) {

    // generate random matrix
    int **matrix = createMatrix();

    // print matrix
    printMatrix(matrix);

    // TO DO
    if(valueExists(matrix, atoi(argv[1])) == 1) printf("O valor existe na matriz\n");
    else printf("O valor não existe na matriz\n");

    // free matrix
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
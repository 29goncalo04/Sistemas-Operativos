#include "matrix.h"

int main(int argc, char *argv[]) {
    // generate random matrix
    int **matrix = createMatrix();
    // print matrix
    printMatrix(matrix);
    int found = valueExists (matrix, atoi(argv[1]));
    if (found == -1) printf ("Valor não encontrado\n");
    else printf ("O elemento aparece pela primeira vez na linha %d\n", found);
    linesWithValue(matrix, atoi(argv[1]));
    // free matrix
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
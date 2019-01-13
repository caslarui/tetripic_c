// Copyright [2019] <Ligia Dolinta 311CD>
#include "../includes/tetripic.h"

int allocMatrix(int*** matrix, int row, int col) {
    int i = 0;

    (*matrix)  = (int**)calloc(row, sizeof(int*));
    for (i = 0; i < row; i++) {
        (*matrix)[i] =  (int *)calloc(col, sizeof(int));
    }
    if (matrix)
        return 1;
    else
        return 0;
}

void freeMatrix_i(int** matrix, int row) {
    int i;
    for (i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix);
    matrix = NULL;
}

void freeMatrix_c(char** matrix, int row) {
    int i;
    for (i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix);
    matrix = NULL;
}

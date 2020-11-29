#include "qwirkle.h"

void matrix_print(int **matrix, int matrix_rows, int matrix_cols, int *matrix_origin, char *pecaTab) {


    printf("      ");
    for(int j = 0; j <= 6*(matrix_cols); j++) {
        printf("-");
    }
    printf("\n");

    for(int i = 0; i<=matrix_rows; i++) {
        for(int j = 0; j<=matrix_cols; j++) {

            if(i == 0 && j == 0){
                printf("      ");

            } else if(i == 0 && j != 0){
                index_print(j-matrix_origin[1]);

            } else if(j == 0 && i != 0){
                index_print(i-matrix_origin[0]);

            } else {
                printf("|  %s  " , printTab(matrix[i-1][j-1], pecaTab));
            }
        }
        printf("|\n");

        for(int j = 0; j <= 6*(matrix_cols+1); j++) {
            printf("-");
        }
        printf("\n");
    }
}


void index_print(int index) {

    if(index <= -10) {
        printf("| %d ", index);

    } else if(index < 0) {
        printf("|  %d ", index);

    } else if(index < 10) {
        printf("|   %d ", index);

    } else {
        printf("|  %d ", index);
    }
}

void ReallocMatrix(int ***mat, int *matrix_rows, int *matrix_cols, int *matrix_origin, int add_row, int add_col) {

    *matrix_rows += abs(add_row);
    *matrix_cols += abs(add_col);

    *mat = (int**)realloc(*mat, (*matrix_rows)*sizeof(int*));
    for(int i = 0; i < (*matrix_rows) ; i++) {
        (*mat)[i] = (int*)realloc((*mat)[i], (*matrix_cols)*sizeof(int));
    }

    for(int i = 0; i < abs(add_col)*(*matrix_rows); i++) {
        (*mat)[i][(*matrix_cols)-1] = 0;
    }
    for(int j = 0; j < abs(add_row)*(*matrix_cols); j++) {
        (*mat)[(*matrix_rows)-1][j] = 0;
    }

    matrix_origin[0] = matrix_origin[0] + (abs(add_row) - add_row)/2;
    matrix_origin[1] = matrix_origin[1] + (abs(add_col) - add_col)/2;


    if(add_row < 0 || add_col < 0) {
        ShiftMatrix(*mat, matrix_rows, matrix_cols, add_row, add_col);
    }
}


void ShiftMatrix(int **mat, int* matrix_rows, int* matrix_cols, int add_row, int add_col) {

    for(int i = 0; i < ((abs(add_row) - add_row)/2)*((*matrix_rows)-1); i++) {
        //printf("1\n");
        for(int j = 0; j < (*matrix_cols); j++) {
            //printf("[%d][%d]\n", (*matrix_rows)-i-1, (*matrix_cols)-j-1);
            mat[(*matrix_rows)-i-1][(*matrix_cols)-j-1] = mat[(*matrix_rows)-i-2][(*matrix_cols)-j-1];
        }
    }
    for(int j = 0; j < ((abs(add_col) - add_col)/2)*((*matrix_cols)-1); j++) {
        //printf("2\n");
        for(int i = 0; i < (*matrix_rows); i++) {
            //printf("[%d][%d]\n", (*matrix_rows)-i-1, (*matrix_cols)-j-1);
            mat[(*matrix_rows)-i-1][(*matrix_cols)-j-1] = mat[(*matrix_rows)-i-1][(*matrix_cols)-j-2];
        }
    }

    for(int i = 0; i < (*matrix_rows); i++) {
        mat[(*matrix_rows)-i-1][0] = 0;
    }
    for(int j = 0; j < (*matrix_cols); j++) {
        mat[0][(*matrix_cols)-j-1] = 0;
    }

}

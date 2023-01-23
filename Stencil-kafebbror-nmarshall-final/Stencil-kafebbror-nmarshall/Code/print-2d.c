#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "utilities.h"

int main(int argc, char* argv[]){
    //Check for correct usage
    if(argc != 2){
        printf("usage: ./print-2d <input data file>\n");
        exit(1);
    }

    //Declare and init variables
    FILE *fp = NULL;
    char *file = argv[1];
    int row,col,j,i;

    //Open file
    fp = fopen(file, "r");

    if (fp == NULL){
        printf("Error: File did not open correctly\n");
        exit(1);
    }

    //Read number of columns and rows from file
    fread(&row, sizeof(int),1,fp);
    fread(&col, sizeof(int),1,fp);

    //Create memory space for array
    double **x = (double **)malloc2D(row,col);

    printf("Reading in file: %s\n", file);

    //Read the matrix in from input data file
    fread(x[0], sizeof(double), row*col, fp);

    //print out the matrix
    for(j = 0; j < row; j++){
        for(i = 0; i<col; i++){
            printf("%.2f  ", x[j][i]);
        }
        printf("\n");
    }

    //Free memory and exit
    free(x);
    exit(0);
}

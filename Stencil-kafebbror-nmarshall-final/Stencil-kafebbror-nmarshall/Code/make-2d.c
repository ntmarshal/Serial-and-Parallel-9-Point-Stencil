#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    //Check for correct usage
    if(argc != 4){
        printf("usage: ./make-2d <rows> <cols> <output_file>\n");
        exit(1);
    }

    //Declare and init variables
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    char *file = argv[3];


    //j rows, i columns
    int i,j;
    double **x = (double **)malloc2D(rows,cols);

    //In the first and last row, set values to 1, otherwise set values to 0
    for(j = 0; j<rows; j++){
        for(i = 0; i<cols; i++){
            if(i == 0 || i == cols-1){
                x[j][i] = 1;
        } else {
                x[j][i] = 0;
        }
    }

    }
    //Write matrix to file, free memory
    write_file(x, rows,cols,file);
    free(x);
    exit(0);

}

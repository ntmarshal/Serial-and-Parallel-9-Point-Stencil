#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

//Create contiguous 2D array
double **malloc2D(int row, int col)
 {
    double **x = (double **)malloc(row*sizeof(double *) + row*col*sizeof(double));
    x[0] = (double *)x + row;
    for (int j = 1; j < row; j++) {
        x[j] = x[j-1] + col;
    }
    return(x);
}

//Write file with row and col included in the beginning of the file
void write_file(double** matrix, int row, int col, char* filename){
    FILE *fp = NULL;

    fp = fopen(filename,"w");


    fwrite(&row,sizeof(int),1,fp);
    fwrite(&col,sizeof(int),1,fp);

    fwrite(matrix[0],sizeof(double),row*col,fp);

    fclose(fp);
}

//Input two matrix pointers and run 9-point stencil on them serially
void serial_stencil(double** x, double** xNew, int row, int col){
     for(int j = 1; j < row - 1; j++){
            for(int i = 1; i < col - 1; i++){
                xNew[j][i] = (x[j-1][i-1] + x[j-1][i] + x[j-1][i+1] + x[j][i+1] + x[j+1][i+1] + x[j+1][i] + x[j+1][i-1] + x[j][i-1] + x[j][i])/9.0;
            }
        }

}

//Utilize OpenMP to parallize the 9-point stencil
void parallel_stencil(double** x, double** xNew, int row, int col,int numThreads){
    omp_set_num_threads(numThreads);
    #pragma omp parallel shared(x,xNew,row,col)
        {
        #pragma omp for
        for(int j = 1; j < row - 1; j++){
            for(int i = 1; i < col - 1; i++){
                xNew[j][i] = (x[j-1][i-1] + x[j-1][i] + x[j-1][i+1] + x[j][i+1] + x[j+1][i+1] + x[j+1][i] + x[j+1][i-1] + x[j][i-1] + x[j][i])/9.0;
            }
        }
        }
}

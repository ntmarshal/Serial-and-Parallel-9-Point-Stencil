#include "utilities.h"
#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>


#define SWAP_PTR(xNew,x,temp) (temp=xNew, xNew=x, x=temp)

int main(int argc, char*argv[]){
    //Check for correct usage
    if(argc != 5){
        printf("usage: ./omp-stencil-2d <num interations> <input file> <output file> <num threads>\n");
        exit(1);
    }
    //Declare variables and init
    FILE *fp = NULL;
    char *file = argv[2];
    int maxIterations = atoi(argv[1]);
    char *outputFile = argv[3];
    int numThreads = atoi(argv[4]);
    int row,col;
    double **temp;
    double elapsedTime,start,end;

    //Open File

    fp = fopen(file, "r");
    if (fp == NULL){
        printf("Error: Input File could not be opened\n");
        exit(1);
    }

    //Read integer values
    fread(&row, sizeof(int),1,fp);
    fread(&col, sizeof(int),1,fp);

    //Create space for matrix
    double **x = (double **)malloc2D(row,col);

    //Create new matrix
    double **xNew = (double **)malloc2D(row,col);

    //Read matrix from file
    fread(x[0], sizeof(double), row*col, fp);


    //Copy Memory for xNew
    memcpy(xNew[0],x[0],sizeof(double)*(row*col));

    //Start Timer
    GET_TIME(start);
    //Loop through iterations passed by user
    for(int k = 0; k < maxIterations; k++){

        //Use 9 point stencil to calculate averages of each spot in matrix
        parallel_stencil(x,xNew,row,col,numThreads);


        //Change the pointers
        SWAP_PTR(xNew,x,temp);
    }

    //End Timer
    GET_TIME(end);
    write_file(x,row,col,outputFile);
    //Calculate Elapsed Time
    elapsedTime = end - start;

    //Print information to console
    printf("Elapsed Time: %f Number of Interations: %d Row: %d Column: %d Number of Threads:%d\n",elapsedTime,maxIterations,row,col,numThreads);

    //Free Memory
    free(x);
    free(xNew);
    fclose(fp);
}

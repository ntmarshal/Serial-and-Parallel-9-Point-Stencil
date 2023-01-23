#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include "timer.h"
#include <string.h>

#define SWAP_PTR(xNew,x,temp) (temp=xNew, xNew=x, x=temp)

int main(int argc, char*argv[]){
    //Check for correct usage
    if(argc != 4){
        printf("usage: ./stencil-2d-stack <num interations> <input file> <all-iterations>\n");
        exit(1);
    }
    //Declare variables and init
    FILE *fp = NULL;
    FILE *fp1 = NULL;
    char *file = argv[2];
    int maxIterations = atoi(argv[1]);
    char *allFile = argv[3];
    int row,col;
    double **temp;
    double start,end,elapsedTime;
    //Open File

    fp = fopen(file, "r");
    if (fp == NULL){
        printf("Error: Input File could not be opened\n");
        exit(1);
    }

    //Open all file
    fp1 = fopen(allFile,"w");


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
         //Write initial state to all file
        fwrite(x[0],sizeof(double),row*col,fp1);
        //Use 9 point stencil to calculate averages of each spot in matrix
        serial_stencil(x,xNew,row,col);

        //Write final interation file
        if(k == maxIterations - 1){
            fwrite(xNew[0],sizeof(double),row*col,fp1);
        }

        //Change the pointers
        SWAP_PTR(xNew,x,temp);
    }
    //End Timer
    GET_TIME(end);

    //Calculate Elapsed Time
    elapsedTime = end - start;

    //Print informaition to screen
    printf("Elapsed Time: %f Number of Interations: %d Row: %d Column: %d\n",elapsedTime,maxIterations,row,col);

    //Free Memory
    free(x);
    free (xNew);
    fclose(fp);
    fclose(fp1);
}

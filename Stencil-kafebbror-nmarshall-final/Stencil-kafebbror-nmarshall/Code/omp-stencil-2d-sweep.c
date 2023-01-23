#include "utilities.h"
#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>


#define SWAP_PTR(xNew,x,temp) (temp=xNew, xNew=x, x=temp)

int main(int argc, char*argv[]){
    //Check for correct usage
    if(argc != 7){
        printf("usage: ./omp-stencil-2d <num interations> <input file> <serial-output file> <parrallel-output-file> <data-output-file> <num threads>\n");
        exit(1);
    }
    //Declare variables and init
    FILE *fp = NULL;
    FILE *fp1 = NULL;
    char *file = argv[2];
    char *outputFile = argv[5];
    int maxIterations = atoi(argv[1]);
    char *serialoutputFile = argv[3];
    char *parallelOutputFile = argv[4];
    int numThreads = atoi(argv[6]);
    int row,col;
    double **temp;
    double elapsedTime,start,end,serialTime,speedup,efficiency;
    char writeValue[500];



    if(numThreads < 2){
        printf("Error: Not enough threads entered\n");
        exit(1);
    }
    //Open File

    fp = fopen(file, "r");
    if (fp == NULL){
        printf("Error: Input File could not be opened\n");
        exit(1);
    }

    fp1 = fopen(outputFile,"w");

     //Read intergers
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

    GET_TIME(start);
    for(int k = 0; k < maxIterations; k++){
        //Use 9 point stencil to calculate averages of each spot in matrix
        serial_stencil(x,xNew,row,col);

        //Change the pointers
        SWAP_PTR(xNew,x,temp);

    }
    GET_TIME(end);
    //write file
    write_file(x,row,col,serialoutputFile);

    //Get serial elapsedTime
    serialTime = end - start;

    //print serial time
    printf("Serial Time: %f\n",serialTime);
    snprintf(writeValue, sizeof(writeValue),"%d %f %f %f\n",1,serialTime,1.0,1.0);
	fputs(writeValue,fp1);

    //rewind file
    rewind(fp);

    for(int m = 2; m <= numThreads; m++){
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
            parallel_stencil(x,xNew,row,col,m);

            //Change the pointers
            SWAP_PTR(xNew,x,temp);
        }

        //End Timer
        GET_TIME(end);

         //write parallel output file
        write_file(x,row,col,parallelOutputFile);

        //Calculate Elapsed Time
        elapsedTime = end - start;

        //Speedup Calculation
        speedup = serialTime/elapsedTime;

        //Efficiency Calculation
        efficiency = speedup/m;

        //Print information to console
        printf("Elapsed Time: %f Threads:%d Speedup:%f Efficiency: %f\n",elapsedTime,m,speedup,efficiency);

         snprintf(writeValue, sizeof(writeValue),"%d %f %f %f\n",m,elapsedTime,speedup,efficiency);
        fputs(writeValue,fp1);

        //Free Memory
        free(x);
        free(xNew);
        rewind(fp);
    }
    fclose(fp);
    fclose(fp1);
}

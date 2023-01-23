#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include "MyMPI.h"

#define SWAP_PTR(xNew,x,temp) (temp=xNew, xNew=x, x=temp)
#define dtype double

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    if (argc != 4) {
        printf("Usage: mpirun -np <p> ./mpi-stencil-2d-stack <num iterations> <input file> <all-raw file>\n");
        MPI_Finalize();
        exit(1);
    }

    char *file = argv[2];
    int maxIterations = atoi(argv[1]);
    char *outputFile = argv[3];
    double **temp;
    int id, p;
    double elapsedTime,start,end;
    FILE *fp1 = NULL;
    dtype** x, *xdata; int rows, cols;

    dtype** xNew, *xNewdata;

    //Open all file
    fp1 = fopen(outputFile,"w");

    MPI_Comm_rank (MPI_COMM_WORLD, &id);
    MPI_Comm_size (MPI_COMM_WORLD, &p);

    read_row_striped_matrix_halo(file, (void***)&x, (void**)&xdata, MPI_DOUBLE, &rows, &cols, MPI_COMM_WORLD);

    read_row_striped_matrix_halo(file, (void***)&xNew, (void**)&xNewdata, MPI_DOUBLE, &rows, &cols, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    if(id == 0) {
        start = MPI_Wtime();
    }

    for(int k = 0; k < maxIterations; k++){
        exchange_row_striped_matrix_halo((void***)&x, (void**)&xdata, MPI_DOUBLE, rows, cols, MPI_COMM_WORLD);

        write_row_striped_matrix_halo_stack((void**)x, MPI_DOUBLE, rows, cols, MPI_COMM_WORLD, fp1);
        if(p > 1){
        serial_stencil((double**)x,(double**)xNew,BLOCK_SIZE_HALO(id,p,rows),cols);
        } else {
        serial_stencil((double**)x,(double**)xNew,rows,cols);

        }
        if(k == maxIterations -1){
            write_row_striped_matrix_halo_stack((void**)xNew, MPI_DOUBLE, rows, cols, MPI_COMM_WORLD, fp1);
        }

        SWAP_PTR(xNew,x,temp);

    }

    MPI_Barrier(MPI_COMM_WORLD);
    if(id == 0) {
        end = MPI_Wtime();
        elapsedTime = end - start;
        printf("Elapsed Time: %.3f\n",elapsedTime);
    }


    fclose(fp1);
    MPI_Finalize();
    return 0;
}


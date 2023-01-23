#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

double **malloc2D(int row, int col);

void write_file(double** matrix, int row, int col, char* filename);

void serial_stencil(double** x, double** xNew, int row, int col);

void parallel_stencil(double** x, double** xNew, int row, int col,int numThreads);

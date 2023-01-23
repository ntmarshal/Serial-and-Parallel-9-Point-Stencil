CC=gcc
MCC=mpicc
CFLAGS=-g -Wall -std=gnu99 -fopenmp
LFLAGS=-fopenmp
all:	print-2d make-2d stencil-2d stencil-2d-stack omp-stencil-2d omp-stencil-2d-stack omp-stencil-2d-sweep mpi-stencil-2d mpi-stencil-2d-stack mpi-openmp-stencil-2d
driver:	utilities.o driver.o
	$(CC) $(LFLAGS) -o driver utilities.o driver.o
print-2d:	utilities.o print-2d.o
	$(CC) $(LFLAGS) -o print-2d utilities.o print-2d.o
make-2d:	utilities.o make-2d.o
	$(CC) $(LFLAGS) -o make-2d utilities.o make-2d.o
stencil-2d:	utilities.o stencil-2d.o
	$(CC) $(LFLAGS) -o stencil-2d utilities.o stencil-2d.o
stencil-2d-stack:	utilities.o stencil-2d-stack.o
	$(CC) $(LFLAGS) -o stencil-2d-stack utilities.o stencil-2d-stack.o
omp-stencil-2d:	utilities.o omp-stencil-2d.o
	$(CC) $(LFLAGS) -o omp-stencil-2d utilities.o omp-stencil-2d.o
omp-stencil-2d-stack:	utilities.o omp-stencil-2d-stack.o
	$(CC) $(LFLAGS) -o omp-stencil-2d-stack utilities.o omp-stencil-2d-stack.o
omp-stencil-2d-sweep:	utilities.o omp-stencil-2d-sweep.o
	$(CC) $(LFLAGS) -o omp-stencil-2d-sweep utilities.o omp-stencil-2d-sweep.o
mpi-stencil-2d: mpi-stencil-2d.o utilities.o MyMPI.o
	$(MCC) $(LFLAGS) -o mpi-stencil-2d mpi-stencil-2d.o utilities.o MyMPI.o
mpi-stencil-2d-stack: mpi-stencil-2d-stack.o utilities.o MyMPI.o
	$(MCC) $(LFLAGS) -o mpi-stencil-2d-stack mpi-stencil-2d-stack.o utilities.o MyMPI.o
mpi-openmp-stencil-2d: mpi-openmp-stencil-2d.o utilities.o MyMPI.o
	$(MCC) $(LFLAGS) -o mpi-openmp-stencil-2d mpi-openmp-stencil-2d.o utilities.o MyMPI.o

utilities.o: utilities.c utilities.h
	$(CC) $(CFLAGS) $(LFLAGS) -c utilities.c
print-2d.o: print-2d.c utilities.h
	$(CC) $(CFLAGS) -c print-2d.c
make-2d.o: make-2d.c utilities.h
	$(CC) $(CFLAGS) -c make-2d.c
stencil-2d.o: stencil-2d.c utilities.h
	$(CC) $(CFLAGS) -c stencil-2d.c
stencil-2d-stack.o: stencil-2d-stack.c utilities.h
	$(CC) $(CFLAGS) -c stencil-2d-stack.c
omp-stencil-2d.o: omp-stencil-2d.c utilities.h
	$(CC) $(CFLAGS) -c omp-stencil-2d.c
omp-stencil-2d-stack.o: omp-stencil-2d-stack.c utilities.h
	$(CC) $(CFLAGS) -c omp-stencil-2d-stack.c
omp-stencil-2d-sweep.o: omp-stencil-2d-sweep.c utilities.h
	$(CC) $(CFLAGS) -c omp-stencil-2d-sweep.c
MyMPI.o: MyMPI.c MyMPI.h
	$(MCC) $(CFLAGS) -c MyMPI.c
mpi-stencil-2d.o: mpi-stencil-2d.c utilities.h MyMPI.h
	$(MCC) $(CFLAGS) -c mpi-stencil-2d.c
mpi-stencil-2d-stack.o: mpi-stencil-2d-stack.c utilities.h MyMPI.h
	$(MCC) $(CFLAGS) -c mpi-stencil-2d-stack.c

mpi-openmp-stencil-2d.o: mpi-openmp-stencil-2d.c utilities.h MyMPI.h
	$(MCC) $(CFLAGS) -c mpi-openmp-stencil-2d.c




clean:
	rm -f *.o core* print-2d make-2d stencil-2d stencil-2d-stack omp-stencil-2d omp-stencil-2d-stack omp-stencil-2d-sweep mpi-stencil-2d mpi-stencil-2d-stack mpi-openmp-stencil-2d


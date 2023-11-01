#include "mpi.h"
#include <stdlib.h>
#include "stdio.h"

#define Q 1
#define SIZE 6300017

int main(int argc, char* argv[])
{
	float* a = new float[SIZE];
	float* b = new float[SIZE];
	float* c = new float[SIZE];
	int ProcRank, ProcNum, i;

	double st_time, end_time;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

	int count;
	if (ProcRank == ProcNum - 1) {
		count = SIZE / ProcNum + SIZE % ProcNum;
	}
	else {
		count = SIZE / ProcNum;
	}
	if (ProcRank == 0) {
		for (int i = 0; i < SIZE; ++i) {
			a[i] = 1.0;
			b[i] = 2.0;
		}
	}
	float* a_ = new float[SIZE];
	float* c_ = new float[SIZE];
	float* b_ = new float[SIZE];
	double time = 0;
	int* sendcounts = new int[ProcNum];
	for (int i = 0; i < ProcNum - 1; ++i) {
		sendcounts[i] = SIZE / ProcNum;
	}
	sendcounts[ProcNum - 1] = SIZE / ProcNum + SIZE % ProcNum;
	int* biases = new int[ProcNum];
	biases[0] = 0;
	for (i = 1; i < ProcNum; i++) {
			biases[i] = biases[i - 1] + sendcounts[i - 1];
	}
	st_time = MPI_Wtime();
	MPI_Scatterv(a, sendcounts, biases, MPI_FLOAT, a_, count, MPI_FLOAT, 0, MPI_COMM_WORLD);
	MPI_Scatterv(b, sendcounts, biases, MPI_FLOAT, b_, count, MPI_FLOAT, 0, MPI_COMM_WORLD);
	for (int i = 0; i < count; ++i) {
		for (int j = 0; j < Q; j++) {
			c_[i] = a_[i] + b_[i];
		}
	}
	MPI_Gatherv(c_, count, MPI_FLOAT, c, sendcounts, biases, MPI_FLOAT, 0, MPI_COMM_WORLD);
	end_time = MPI_Wtime();
	time = end_time - st_time;

	if (ProcRank == 0)
	{
		printf("\nTIME OF SCATTERV and GATHERV WORK IS %f \n", time);
		printf("\nProcesses: %d", ProcNum);
		printf("\nQ = %d", Q);

	}
	MPI_Finalize();
	return 0;
}

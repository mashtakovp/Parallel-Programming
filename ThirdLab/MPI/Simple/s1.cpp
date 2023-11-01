#include "mpi.h"
#include <stdlib.h>
#include "stdio.h"

#define Q 1
#define SIZE 6300000

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

	int count = SIZE / ProcNum;
	if (ProcRank == 0) {
		for (int i = 0; i < SIZE; ++i) {
			a[i] = 1.0;
			b[i] = 2.0;
		}
	}

	float* a_ = new float[SIZE];
	float* b_ = new float[SIZE];
	float* c_ = new float[SIZE];

	double time = 0;

	st_time = MPI_Wtime();

	MPI_Scatter(a, count, MPI_FLOAT, a_, count, MPI_FLOAT, 0, MPI_COMM_WORLD);
	MPI_Scatter(b, count, MPI_FLOAT, b_, count, MPI_FLOAT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < count; ++i) {
		for (int j = 0; j < Q; j++) {
			c_[i] = a_[i] + b_[i];
		}
	}
	MPI_Gather(c_, count, MPI_FLOAT, c, count, MPI_FLOAT, 0, MPI_COMM_WORLD);
	end_time = MPI_Wtime();
	time = end_time - st_time;

	if (ProcRank == 0)
	{
		printf("\nTIME OF SCATTER and GATHER WORK IS %f \n", time);
		printf("\nProcesses: %d", ProcNum);
		printf("\nQ = %d", Q);
	}
	MPI_Finalize();
	return 0;
}
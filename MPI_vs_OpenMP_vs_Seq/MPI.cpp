#include "mpi.h"
#include "stdio.h"

int main(int argc, char* argv[])
{
	int rank, ranksize, i;
	MPI_Init(&argc, &argv);
	double start;
	start = MPI_Wtime();
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &ranksize);
	printf("Hello world from process %d from total number of %d\n", rank, ranksize);
	printf("MPI Time: %f\n", MPI_Wtime() - start);
	MPI_Finalize();
	return 0;
}

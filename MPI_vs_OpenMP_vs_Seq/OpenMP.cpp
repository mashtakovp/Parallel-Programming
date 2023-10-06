#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <cmath>


int main(int argc, char* argv[])
{
	double Time = 0;
	for (int i = 0; i < 12; ++i) {
		omp_set_num_threads(8);
		int nThreads, threadNum;
		double start = omp_get_wtime();
#pragma omp parallel private(nThreads, threadNum)
		{
			nThreads = omp_get_num_threads();
			threadNum = omp_get_thread_num();
			printf("Hello world thread %d from %d threads \n", threadNum, nThreads);
		}
		double end = omp_get_wtime();
		Time += end - start;
	}
	printf("OpenMP Time (mcs) : %f ", Time * (pow(10, 6) / 12));
	return 0;
}

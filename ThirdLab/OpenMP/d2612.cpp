#include <omp.h>
#include <ctime>
#include "stdio.h"
#include "iostream"

#define THREADS 12
#define Q 26
#define CHUNK 100
#define SIZE 6300000

float* omp_dynamic(float* vec1, float* vec2, int n) {
	float* sum = new float[n];
	for (int i = 0; i < 12; ++i) {
#pragma omp parallel for shared(vec1, vec2, sum) schedule(dynamic, CHUNK)
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < Q; ++j) {
				sum[i] = vec1[i] + vec2[i];
			}
		}
	}
	return sum;
}

int main(int argc, char* argv[]) {

	omp_set_num_threads(THREADS);
	double st_time, total_time;

	float* a = new float[SIZE];
	float* b = new float[SIZE];
	float* vec_sum;

	for (int i = 0; i < SIZE; ++i) {
		a[i] = 1.0;
		b[i] = 2.0;
	}

	st_time = omp_get_wtime();
	vec_sum = omp_dynamic(a, b, SIZE);
	total_time = omp_get_wtime() - st_time;
	printf("\nTIME OF DYNAMIC WORK DYNAMIC IS: %f ", total_time / 12);
	printf("\nTHREADS: %d", THREADS);
	printf("\nQ: %d", Q);
	delete[] vec_sum;
	delete[] a;
	delete[] b;

	return 0;
}
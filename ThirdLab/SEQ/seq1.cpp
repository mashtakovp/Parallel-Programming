#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 6300000
#define Q 1

int main(int argc, char* argv[]) {
	int count;
	double total_time = 0;
	float* a = new float[SIZE];
	float* b = new float[SIZE];
	float* sum = new float[SIZE];

	for (int i = 0; i < SIZE; i++) {
		a[i] = 1.0;
		b[i] = 2.0;
	}

	double start_time, end_time;

	for (count = 0; count < 12; count++) {
		start_time = clock();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < Q; j++) {
				sum[i] = a[i] + b[i];
			}
		}
		end_time = clock();
		total_time += end_time - start_time;
	}

	printf("\nQ: %d", Q);
	printf("\nTIME OF SEQUENTIAL WORK IS %f ", (total_time / 12) / CLOCKS_PER_SEC);

	return 0;
}
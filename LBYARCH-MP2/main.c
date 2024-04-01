#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

extern void stencilComputation(double* X, double* Y, int sizeOfArray);
void stencilComputationC(double* X, double* Y, int sizeOfY);
void prompt(int* sizeOfArray);
void printY(double* Y, int size);

int main() {
	int sizeOfArray;
	
	prompt(&sizeOfArray);
	
	int sizeOfY = sizeOfArray - 6;
	double* X = malloc(sizeOfArray * sizeof(double));
	double* Y = malloc(sizeOfY * sizeof(double));
	double* X_C = malloc(sizeOfArray * sizeof(double));
	double* Y_C = malloc(sizeOfY * sizeof(double));

	if (X == NULL || Y == NULL) {
		printf("Memory not allocated.\n");
		free(X);
		free(Y);
		exit(0);
	}
	else {
		 //Memory has been successfully allocated
		printf("Memory successfully allocated using malloc.\n");
	}

	//populate
	for (int i = 0; i < sizeOfArray; i++) {
		X[i] = i;
	}
	
	for (int j = 0; j < sizeOfArray; j++) {
		X_C[j] = X[j];
	}

	stencilComputation(X, Y, sizeOfArray);
	stencilComputationC(X_C, Y_C, sizeOfY);
	
	printf("asm:\n");
	printY(Y, sizeOfY);

	printf("C:\n");
	printY(Y_C, sizeOfY);

	return 0;
}

void prompt(int* sizeOfArray) {
	int normal;
	do {
		printf("Enter the size (n) of vector X: ");
		scanf_s("%d", &normal);
		if (normal < 7) {
			printf("Input size is too small.\n");
		}
	} while (normal < 7);
	*sizeOfArray = normal;
}

void stencilComputationC(double* X, double* Y, int iteration) {
	int stencilSum;
	int offset = 0;
	for (int i = 0; i < iteration; i++) {
		stencilSum = 0;
		for (int j = 0; j < 7; j++) {
			stencilSum += X[j + offset];
		}
		Y[i] = stencilSum;
		offset++;
	}
}

void printY(double* Y, int size) {
	for (int i = 0; i < size; i++) {
		printf("%lf\n", Y[i]);
	}
}
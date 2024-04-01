#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

extern void stencilComputation(double* X, double* Y, int sizeOfArray);
void stencilComputationC(double* X, double* Y, int sizeOfY);
void prompt(int* sizeOfArray);
int sanityCheckPass(double* Y_Asm, double* Y_C, int size);

int main() {
	int sizeOfArray;
	prompt(&sizeOfArray);
	int sizeOfY = sizeOfArray - 6;
	double* X = malloc(sizeOfArray * sizeof(double));
	double* Y = malloc(sizeOfY * sizeof(double));
	double* X_C = malloc(sizeOfArray * sizeof(double));
	double* Y_C = malloc(sizeOfY * sizeof(double));
	int sanityCheck;
	int yPrintLimit = 10;
	int test = 30;
	double cTime[30];
	double asmTime[30];

	


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

	//run asm and C functions once
	printf("Running C and Asm functions once...\nPrinting the first 10 elements of vector Y...\n");
	stencilComputation(X, Y, sizeOfArray);
	stencilComputationC(X_C, Y_C, sizeOfY);
	
	sanityCheck = sanityCheckPass(Y, Y_C, sizeOfY);

	if (!sanityCheck) {
		printf("Return values from Assembly and C functions don't match.");
		free(X);
		free(Y);
		exit(0);
	}
	else {
		printf("Sanity Checked passed!\nProceeding to testing.");
	}

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

int sanityCheckPass(double* Y_Asm, double* Y_C, int size) {
	for (int i = 0; i < size; i++) {
		if (Y_Asm[i] != Y_C[i]) {
			return 0;
		}
		//print first 10 values
		if (i < 10) {
			printf("Y_Asm[%d] = %lf\n", i, Y_Asm[i]);
			printf("Y_C[%d] = %lf\n", i, Y_C[i]);
		}
	}
	return 1;
}
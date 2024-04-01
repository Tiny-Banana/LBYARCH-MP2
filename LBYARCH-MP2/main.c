#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

extern void stencilComputation(double* X, double* Y, int sizeOfY);
void stencilComputationC(double* X, double* Y, int sizeOfY);
void prompt(int* sizeOfArray);
int sanityCheckPass(double* Y_Asm, double* Y_C, int size);
void generateCsv(const double asmTime[], const double cTime[], int testRun, int size);
double getAverage(double* times, int size);

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
	int testRun = 30;
	double asmTime[30];
	double cTime[30];
	clock_t start;
	clock_t end;

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

	//populate the array
	for (int i = 0; i < sizeOfArray; i++) {
		X[i] = i;
	}

	for (int j = 0; j < sizeOfArray; j++) {
		X_C[j] = X[j];
	}

	//run asm and C functions once
	printf("Running C and Asm functions once...\nPrinting the first 10 elements of vector Y for correctness check...\n\n");
	stencilComputation(X, Y, sizeOfY);
	stencilComputationC(X_C, Y_C, sizeOfY);

	sanityCheck = sanityCheckPass(Y, Y_C, sizeOfY);

	if (!sanityCheck) {
		printf("Return values from Assembly and C functions don't match.");
		free(X);
		free(Y);
		exit(0);
	}
	else {
		printf("Sanity check passed!\n\nProceeding to testing.\n");
	}

	printf("Running Asm function 30 times...\n");
	for (int i = 0; i < testRun; i++) {
		start = clock();
		stencilComputation(X, Y, sizeOfY);
		end = clock();
		asmTime[i] = (double)(end - start) / CLOCKS_PER_SEC;
	}

	printf("Running C function 30 times...\n");
	for (int i = 0; i < testRun; i++) {
		start = clock();
		stencilComputationC(X_C, Y_C, sizeOfY);
		end = clock();
		cTime[i] = (double)(end - start) / CLOCKS_PER_SEC;
	}

	printf("Saving results to a CSV file...\n");
	generateCsv(asmTime, cTime, testRun, sizeOfArray);

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
			printf("Y[%d] in x86-64 implementation: %lf\n", i, Y_Asm[i]);
			printf("Y[%d] in C implementation:      %lf\n", i, Y_C[i]);
		}
	}
	return 1;
}

double getAverage(double* times, int size) {
	double sum = 0.0;
	for (int i = 0; i < size; i++) {
		sum += times[i];
	}
	return sum / size;

}

void generateCsv(const double asmTime[], const double cTime[], int testRun, int size) {
	FILE* file = fopen("result.csv", "w");
	if (file == NULL) {
		perror("Error opening file");
		return;
	}

	fprintf(file, "Vector Size,Iteration,Assembly Time (s), C Time (s)\n");

	for (int i = 0; i < testRun; ++i) {
		if (i == 0) {
			fprintf(file, "%d,", size);
		}
		else {
			fprintf(file, ",");
		}
		fprintf(file, "%d,%f,%f\n", i + 1, asmTime[i], cTime[i]);
	}

	double asmAverage = getAverage(asmTime, testRun);
	double cAverage = getAverage(cTime, testRun);
	fprintf(file, "\n, , Average Time (s): %f, Average Time (s): %f\n", asmAverage, cAverage);

	fclose(file);
}
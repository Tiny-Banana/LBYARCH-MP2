#include <stdio.h>

extern void stencilComputation(double* X, double* Y, int sizeOfArray);

int main() {
	const int sizeOfArray = 10;
	double X[10] = { 1,2,3,4,5,6,7,8, 9, 10};
	double Y[10];
	stencilComputation(X, Y, sizeOfArray);

	for (int i = 0; i < 4; i++) {
		printf("value %lf\n", Y[i]);
	}

	return 0;
}
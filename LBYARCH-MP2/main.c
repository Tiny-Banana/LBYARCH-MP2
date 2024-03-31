#include <stdio.h>

extern void stencilComputation(double* X, double* Y, int sizeOfArray);

int main() {
	const int sizeOfArray = 9;
	double X[9] = { 1,2,3,4,5,6,7,8, 9 };
	double Y[9];
	stencilComputation(X, Y, sizeOfArray);

	for (int i = 0; i < 3; i++) {
		printf("value %lf\n", Y[i]);
	}


	return 0;
}
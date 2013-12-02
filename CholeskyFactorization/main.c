#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print2DArray(double **A, int rowsNum,int colsNum)
{
    printf("\n");
    int m,n;
    for (m=0;m<rowsNum;m++)
    {
        for (n=0;n<colsNum;n++)
        {
            printf("[%d,%d]= %.5f ",m,n,A[m][n]);
        }
        printf("\n");
    }
}

void print1DArray(double *A, int size)
{
    printf("\n");
    int m;

	for (m=0 ;m < size; m++)
	{
		printf("[%d]= %.5f ",m, A[m]);
	}

    printf("\n");

}

double *allocade1DArray(int size) {
    double *array = calloc(size, sizeof(double));
    return array;
}



/*funkcja alokująca dwuwymiarową tablicę*/
double **allocate2DArray(int numRows, int numCols) {
	double **newArray;
	int i=0;

	newArray = calloc(numRows, sizeof(double*));
	if(newArray == NULL)
	{
		printf("Program nie może zaalokować pamięci\n");
		return NULL;
	}
	for(i = 0; i < numRows; i++)
		{
		newArray[i] = calloc(numCols, sizeof(double));
		if(newArray[i] == NULL)
		{
			printf("Program nie może zaalokować pamięci\n");
			return NULL;
		}
	}

	return newArray;
}

void deallocate2D(double** array, int numRows) {
	/*  deallocate each row  */
	int i;
	for(i = 0; i < numRows; i++) {
		free(array[i]);
	}

	/*  deallocate array of pointers  */
	free(array);
}

double **cholesky(int size, double** inputMatrix) {
	double **matrixL = allocate2DArray(size, size);
	double tempSum, partOfResult;
	int k, i, j;

	for(i = 0; i < size; i++) {
		for(j = 0; j <= i; j++) {
			/*Część wspólna obliczeń: zarówno dla elementów na przekątnej jaki i poza*/
			tempSum = 0;
			for(k = 0; k < j; k++) {
				tempSum += matrixL[i][k] * matrixL[j][k];
			}

			partOfResult = inputMatrix[i][j] - tempSum;

			if(i == j) {/*na przekatnej*/
				matrixL[i][j] = sqrt(partOfResult);
			}
			else {/*(i != j) poza przekątną*/
				matrixL[i][j] = partOfResult / matrixL[j][j];
			}
		}
	}

	return matrixL;
}

double *forwardSolutionPhase(int size, double** factorizedMatrix, double* b) {
	int i, j;
	double tempSum, *result = allocade1DArray(size);

	for(i = 0; i < size; i++) {

		tempSum = 0;
		for(j = 0; j < i; j++) {

			tempSum += factorizedMatrix[i][j] * result[j];

		}

		result[i] = (b[i] - tempSum)/factorizedMatrix[i][i];
	}
	return result;
}

double *backwardSolutionPhase(int size, double** factorizedMatrix, double* y) {
	int i, j;
	double tempSum, *result = allocade1DArray(size);

	for(i = size - 1; i >= 0; i--) {

		tempSum = 0;
		for(j = size - 1; j > i; j--) {
			tempSum += factorizedMatrix[i][j] * result[j];
		}

		result[i] = (y[i] - tempSum)/factorizedMatrix[i][i];

	}
	return result;

}

double **matrixTransposition(int size, double** inputMatrix) {
	double **transposed = allocate2DArray(size, size);
	int i,j;

	for(i = 0; i < size; i++) {
		for(j = 0; j < size; j++) {
			transposed[i][j] = inputMatrix[j][i];
		}
	}

	return transposed;
}

void checkSolution(double** matrixA, double* matrixX, double* matrixB, int size) {
	int i, j;
	double temSum = 0;

	printf("\n Powinno być równe: \n");
	for(i = 0; i < size; i++) {
		temSum = 0;
		for(j = 0; j < size; j++) {
			temSum += matrixA[i][j] * matrixX[j];
		}
		printf("%f == %f \n",temSum,matrixB[i]);
	}
}

int main()
{
    int rowNum = 4;
    double **m1 = allocate2DArray(rowNum, rowNum);

    m1[0][0] = 18;
    m1[0][1] = 22;
    m1[0][2] = 54;
    m1[0][3] = 42;

    m1[1][0] = 22;
    m1[1][1] = 70;
    m1[1][2] = 86;
    m1[1][3] = 62;

    m1[2][0] = 54;
    m1[2][1] = 86;
    m1[2][2] = 174;
    m1[2][3] = 134;

    m1[3][0] = 42;
    m1[3][1] = 62;
    m1[3][2] = 134;
    m1[3][3] = 106;

    double *b = allocade1DArray(rowNum);

    b[0] = 1;
    b[1] = 0;
    b[2] = 4;
    b[3] = 0;
    /*
    18  22   54   42           4.24264    0.00000    0.00000    0.00000
    22  70   86   62   -->     5.18545    6.56591    0.00000    0.00000
    54  86  174  134          12.72792    3.04604    1.64974    0.00000
    42  62  134  106           9.89949    1.62455    1.84971    1.39262
	*/

    double **factorizedMT = cholesky(rowNum, m1);
    double **factorizedM = matrixTransposition(rowNum, factorizedMT);

    printf("Sfaktoryzowana transponowana macierz Choleskiego (U): \n");
    print2DArray(factorizedMT, rowNum, rowNum);

    double *y = forwardSolutionPhase(rowNum, factorizedMT, b);
    printf("\nWynik po forwardSolutionPhase: \n");

    print1DArray(y, rowNum);

    double *x = backwardSolutionPhase(rowNum, factorizedM, y);

    printf("\nWynik po backwardSolutionPhase: \n");
    print1DArray(x, rowNum);

    printf("\nSprawdzenie rozwiązania: \n");
    checkSolution(m1, x, b, rowNum);

    /*Zwolnij pamięć*/
    deallocate2D(m1, rowNum);
    free(b);
    deallocate2D(factorizedMT,rowNum);
    deallocate2D(factorizedM,rowNum);
    free(y);
    free(x);
    return 0;
}


/*
 * Dane testowe

    m1[0][0] = 2;
    m1[0][1] = -1;
    m1[0][2] = 0;

    m1[1][0] = -1;
    m1[1][1] = 2;
    m1[1][2] = -1;

    m1[2][0] = 0;
    m1[2][1] = -1;
    m1[2][2] = 1;
 */

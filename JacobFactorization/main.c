#include <stdio.h>
#define sizeOfMatrix 4

int main(void)
{
	int i, j;
	double A[sizeOfMatrix][sizeOfMatrix] = {{4,-1,-0.2,2},{-1,5,0,2},{0.2,1,10,-1},{0,-2,-1,4}};
    double L[sizeOfMatrix][sizeOfMatrix];
    double D[sizeOfMatrix][sizeOfMatrix];
    double U[sizeOfMatrix][sizeOfMatrix];

	printf("Jacob Factorization\n");

    for(i=0;i<sizeOfMatrix;i++)
    	for(j=0;j<sizeOfMatrix;j++)
    	{
    		L[i][j] = 0;
    		D[i][j] = 0;
    		U[i][j] = 0;
    	}

    for(i=0;i<sizeOfMatrix;i++)
       	for(j=0;j<sizeOfMatrix-i-1;j++)
       		L[i][j] = A[i][j];


    for(i=0;i<sizeOfMatrix;i++)
        D[i][i] = A[i][i];

    for(i=1;i<sizeOfMatrix;i++)
     	for(j=sizeOfMatrix-1;j>=sizeOfMatrix-i;j--)
      		U[i][j] = A[i][j];

	printf("Test:\n\n");
	printf("Matrix A\n");
	for(i=0;i<sizeOfMatrix;i++)
	{
	 	for(j=0;j<sizeOfMatrix;j++)
	  		printf("%f\t",A[i][j]);
	 	printf("\n");
	}

	printf("Matrix L\n");
		for(i=0;i<sizeOfMatrix;i++)
		{
		 	for(j=0;j<sizeOfMatrix;j++)
		  		printf("%f\t",L[i][j]);
		 	printf("\n");
		}

	printf("Matrix D\n");
	for(i=0;i<sizeOfMatrix;i++)
	{
	 	for(j=0;j<sizeOfMatrix;j++)
	  		printf("%f\t",D[i][j]);
	 	printf("\n");
	}
	printf("Matrix U\n");
	for(i=0;i<sizeOfMatrix;i++)
	{
		for(j=0;j<sizeOfMatrix;j++)
	  		printf("%f\t",U[i][j]);
	 	printf("\n");
	}


	return 0;
}

#include <stdio.h>
#define sizeOfMatrix 4

int main(void)
{
	int i, j, k, iter;
	double A[sizeOfMatrix][sizeOfMatrix] = {{4,-1,-0.2,2},{-1,5,0,-2},{0.2,1,10,-1},{0,-2,-1,4}};
    double L[sizeOfMatrix][sizeOfMatrix];
    double D[sizeOfMatrix][sizeOfMatrix];
    double U[sizeOfMatrix][sizeOfMatrix];
    double b[sizeOfMatrix] = {30,0,-10,5};
    double x[sizeOfMatrix];
    double x_old[sizeOfMatrix];
    double Mx[sizeOfMatrix];
    double Nb[sizeOfMatrix];
    double N[sizeOfMatrix][sizeOfMatrix];
    double M[sizeOfMatrix][sizeOfMatrix];
    double sumLU[sizeOfMatrix][sizeOfMatrix];
	printf("Jacob Factorization\n");

    for(i=0;i<sizeOfMatrix;i++)
    {
    	for(j=0;j<sizeOfMatrix;j++)
    	{
    		L[i][j] = 0;
    		D[i][j] = 0;
    		U[i][j] = 0;
    		N[i][j] = 0;
    		M[i][j] = 0;
    		sumLU[i][j] = 0;
        }
		x[i]=0;
		x_old[i]=0;
		Nb[i]=0;
		Mx[i]=0;
    }
    iter=0;
    for(i=0;i<sizeOfMatrix;i++)
       	for(j=0;j<sizeOfMatrix-i-1;j++)
       		L[i][j] = A[i][j];

    for(i=0;i<sizeOfMatrix;i++)
        D[i][i] = A[i][i];

    for(i=1;i<sizeOfMatrix;i++)
     	for(j=sizeOfMatrix-1;j>=sizeOfMatrix-i;j--)
      		U[i][j] = A[i][j];

    for(i=0;i<sizeOfMatrix;i++)
    	N[i][i] = 1/D[i][i];

    for(i=0;i<sizeOfMatrix;i++)
         for(j=0;j<sizeOfMatrix;j++)
         	if(i!=j)
         		sumLU[i][j] =A[i][j];

    for(i=0;i<sizeOfMatrix;i++)
    	for(j=0;j<sizeOfMatrix;j++)
    		for(k=0; k<sizeOfMatrix;k++)
    		{
    			M[i][j]+=-N[i][k]*sumLU[k][j];
    		}

    	for(i=0;i<sizeOfMatrix;i++)
        	for(j=0;j<sizeOfMatrix;j++)
        	{
        		Nb[i]+=N[i][j]*b[j];
        		//printf("%d\t%d\tNb: %f\n", i,j,Nb[i]);
        	}

    	while(iter<7)
    	{
    		for(i=0;i<sizeOfMatrix;i++)
    		{
    			for(j=0;j<sizeOfMatrix;j++)
    			{
    				Mx[i]+=M[i][j]*x_old[j];
    			}
    			x[i]=Nb[i]+Mx[i];
    		}

    		for(i=0;i<sizeOfMatrix;i++)
    		{
    			x_old[i]=x[i];
    			printf("x_old: %f\n", x_old[i]);
    		}
    		iter++;
    		printf("\n");
    	}
   ////////////////////////////////////////////////////////////////////////////


	printf("Test:\n\n");
	/*
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

	printf("Matrix N\n");
	for(i=0;i<sizeOfMatrix;i++)
	{
		for(j=0;j<sizeOfMatrix;j++)
	  		printf("%f\t",N[i][j]);
	 	printf("\n");
	}
	printf("Matrix sumLU\n");
		for(i=0;i<sizeOfMatrix;i++)
		{
			for(j=0;j<sizeOfMatrix;j++)
		  		printf("%f\t",sumLU[i][j]);
		 	printf("\n");
		}
		printf("Matrix M\n");
		for(i=0;i<sizeOfMatrix;i++)
		{
			for(j=0;j<sizeOfMatrix;j++)
				printf("%f\t",M[i][j]);
		 	printf("\n");
		}
		printf("Vector b\n");
		for(i=0;i<sizeOfMatrix;i++)
			printf("%f\t",b[i]);
		printf("\n");

		printf("Vector x_old\n");
		for(i=0;i<sizeOfMatrix;i++)
			printf("%f\t",x_old[i]);
		printf("\n");
	*/
	return 0;
}

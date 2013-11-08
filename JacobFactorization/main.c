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
    double N[sizeOfMatrix];
    double M[sizeOfMatrix][sizeOfMatrix];
    double sumLU[sizeOfMatrix][sizeOfMatrix];

    float x2[100];
	printf("Jacob Factorization\n");

    for(i=0;i<sizeOfMatrix;i++)
    {
    	for(j=0;j<sizeOfMatrix;j++)
    	{
    		L[i][j] = 0;
    		D[i][j] = 0;
    		U[i][j] = 0;

    		M[i][j] = 0;
    		sumLU[i][j] = 0;
        }
		x[i]=0;
		x_old[i]=0;
		Nb[i]=0;
		Mx[i]=0;
		N[i] = 0;
		x_old[i]=0;
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
    	N[i] = 1/D[i][i];

    for(i=0;i<sizeOfMatrix;i++)
         for(j=0;j<sizeOfMatrix;j++)
         	if(i!=j)
         		sumLU[i][j] =A[i][j];

    for(i=0;i<sizeOfMatrix;i++)
    	for(j=0;j<sizeOfMatrix;j++)
    	{
    		M[i][j]=-(sumLU[i][j]*N[i]);
    	}


    iter=200000000;

    while(iter>0)
    {
       for (i=0; i<sizeOfMatrix; i++)
       {
          x[i]= N[i]*b[i];
          for (j=0; j<sizeOfMatrix; j++)
          {
        	 Mx[i] = M[i][j]*x_old[j];
             x[i] +=Mx[i];
          }
       }
       for (i=0; i<sizeOfMatrix; i++)
          x_old[i] = x[i];
       iter--;
    }

    printf("Wynik\n");
    for (i=0; i<sizeOfMatrix; i++)
       printf("x[%d] = %f\n", (i+1), x_old[i]);
	return 0;
}


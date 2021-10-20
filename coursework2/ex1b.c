#include<stdio.h>
#include<stdlib.h>
#include "functions.h"


void main(){

	int Lx, Ly, N, f;
 
	printf("Please type the number of rows of the grid: ");
	scanf("%d", &Ly);
	printf("Please type the number of columns of the grid: ");
	scanf("%d", &Lx);
	printf("Please type the number of particles: ");
	scanf("%d", &N);
	printf("Please type the percentage of super-conductors:  ");
	scanf("%d", &f);
	
  if ( Lx * Ly < N){
		printf("Too many particles\n");
		printf("Enter a number of particles between 0 and %d \n", Lx * Ly);
		scanf("%d", &N);
	}
	

	srandom(6);

	int a,i,j;
	printf("Lx = %d, Ly = %d, N = %d, f = %d% \n", Lx, Ly, N, f);
	particle **g = makeGrid(Lx, Ly);
	fillGrid(g, Lx,Ly, N, f);

	for( i = 0; i < Ly; i++){
		for( j = 0; j < Lx; j++){
			printf("%c ", g[i][j].type);
		}
		printf("\n");
	}
	printf("\n");
}


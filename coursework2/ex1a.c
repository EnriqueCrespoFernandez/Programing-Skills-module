#include<stdio.h>
#include<stdlib.h>
#include "functions.h"

void main(){
	int Lx, Ly, N, f = 0;

	printf("Please type the number of rows of the grid: ");
	scanf("%d", &Ly);
	printf("Please type the number of columns of the grid: ");
	scanf("%d", &Lx);
	printf("Please type the number of particles:  ");
	scanf("%d", &N);
	
	srandom(6);

     	//get the grid
	particle **g = makeGrid(Lx, Ly);
	
	int a,i,j;
	for( a =0 ; a <3; a++){
   		fillGrid(g, Lx, Ly, N, f);
		//print the grid
		for( i = 0; i < Ly; i++){
			for( j = 0; j < Lx; j++){
				printf("%c ", g[i][j].type);
			}
			printf("\n");
		}
		printf("\n");
		freeGrid(g, Lx, Ly);
	}
}

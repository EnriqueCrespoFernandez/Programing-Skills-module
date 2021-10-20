#include<stdio.h>
#include<stdlib.h>
#include "functions.h"

void main(){
	int Lx = 10, Ly = 10, N = 30, f = 10, s=9;

	srandom(s);

	particle **g = makeGrid(Lx, Ly);
	int a,i,j;
	for (a = 0; a<3;a++){

		//build random grid
		fillGrid(g, Lx, Ly, N, f);
			
		for (i = 0 ; i<Ly; i++){
			for (j = 0 ; j < Lx; j++){
					g[i][j].cluster = 0;
			}
		}	
   
		//coordinates initial point
		int x,y;
		x = random_i(Lx);
		y = random_i(Ly);
		particle *p;
		p = &g[y][x];
   
		//set the value of cluster to one on the initial particle
		p->cluster = 1;
		
		//Array of pointers to the particles in the cluster
		particle *cluster[N];
		
		cluster[0] = p;
		//count the number of particles in the cluster
		int c = 1;

		//fill the array
		for( int k = 0; k < c; k++){
			//get a particle in the cluster
			particle *a = cluster[k];
			
			//get the array of pointers to the neigbouring particles
			particle **vi = vicinity(a,g,Lx,Ly);
			//number of neigbouring particles
			int n = a->ng;
			
			for( int h = 0; h < n; h++){
				//check if the particle is a conductor and isnt already counted
				if( vi[h]->type != '.' && vi[h]->cluster == 0){
					cluster[c] = vi[h];
					vi[h]->cluster = 2;
					c++;
				}
			}
			//free the memory allocation because is not loger useful
			free(vi);
		}


		//Print the grid showing the cluster
		for( i = 0; i < Ly; i++){
			for( j = 0; j < Lx; j++){
				printf("%d ", g[i][j].cluster);
			}
			printf("\n");
		}
		printf("\n");

		//Free the memory allocation for the grid
		freeGrid(g, Lx, Ly);
	}
}





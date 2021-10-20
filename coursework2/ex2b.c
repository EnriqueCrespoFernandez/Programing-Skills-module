#include<stdio.h>
#include<stdlib.h>
#include "functions.h"

void main(){
	int Lx = 6, Ly = 4, N = 10, f = 10, s=9;

	srandom(s);

	//count number of paths found
	int npath = 0;
	
	//build an empty grid
	particle **g = makeGrid(Lx, Ly);
	
	int a,i,j;
	
	for (a = 0; a<100;a++){
 	//	printf("a\n");
		//fill the empty grid with randomly
   		fillGrid(g, Lx, Ly, N, f);

		//print the grid
/*		printf("Lx = %d, Ly = %d, N = %d, f = %d%c \n", Lx, Ly, N, f, '%');
		for( i = 0; i < Ly; i++){
			for( j = 0; j < Lx; j++){
				printf("%c ", g[i][j].type);
			}
			printf("\n");
		}
		printf("\n");
*/		
		//coordinates initial point
		int x,y;
		x = random_i(Lx);
		y = random_i(Ly);
		particle *p;
		p = &g[y][x];
   
		//set the value of cluster to one on the initial particle
		p->cluster = 1;
		
		//Array of pointers to the particles in the cluster
		particle *cluster[Lx*Ly];
		
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


		//if there is a particle that belongs to the cluster on y=0 and y=Ly-1 then there must be a path between the two
		int w = 0, q = 0;
		for( j = 0; j < Lx; j++){
			if( g[0][j].cluster == 2){
				 w = 1;
				break;	 
			}
		}
		for( j = 0; j < Lx; j++){
			if( g[Ly-1][j].cluster == 2){
				 q = 1;
				break;	 
			}
		}
		if ( w == 1 && q == 1){
			npath++;
		}

		//Free the memory allocation for the grid
		freeGrid(g, Lx, Ly);
	}

	printf("Paths have been found on a %d %c of the grids\n", npath*100/a, '%'); 
}





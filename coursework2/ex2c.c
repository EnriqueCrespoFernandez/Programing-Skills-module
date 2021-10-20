#include<stdio.h>
#include<stdlib.h>
#include "functions.h"

void main(){
	int Lx = 100, Ly = 100, N = 6000, f = 10, s=9;

	srandom(s);

	//count number of paths found
	
	//open a file to store the data
	FILE *fp;
	fp = fopen("data.csv", "w");
	fprintf(fp, "f , N = 40%, N = 50%, N = 60%, N = 70%, N = 80%, N = 90% \n");
	int ar[] = {40,50,60,70,80,90};
	//build an empty grid
	particle **g = makeGrid(Lx, Ly);
	int a,i,j,t;
	for(f = 0; f < 101; f = f + 5){	
		fprintf(fp, "%d",f);
		for(t = 0; t < 6; t++){
			N = Lx*Ly*ar[t]/100;
			int npath = 0;
			for (a = 0; a<100;a++){
				//fill the empty grid with randomly
				fillGrid(g, Lx, Ly, N, f);

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
			fprintf(fp, ",%d",npath*100/a);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}





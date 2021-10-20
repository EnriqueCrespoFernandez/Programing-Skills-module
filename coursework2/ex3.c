#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "functions3d.h"

void findCluster(particle ***g, particle *p, int N, int Lx, int Ly, int Lz);
bool checkForPath(particle ***g, int Lx, int Ly, int Lz);

void main(){
	int Lx, Ly, Lz, N, f, s=5;

	srandom(s);

	FILE *fp;
 fp = fopen("dataex3hola.csv", "w");
  fprintf(fp, "N\f");
 for(f = 0; f <101; f = f + 10){
 fprintf(fp, ",%d", f);
 }
  fprintf(fp, "\n");
	//build an empty grid
	
		for( int L = 5; L < 51;L++){
			Lx = L;
			Ly = L;
			Lz = L;
       fprintf(fp, "%d", L);
			particle ***g = makeGrid(Lx, Ly, Lz);
      for(f = 0; f <101; f++){
			for(int r = 30; r <= 81; r++){
				int n = Lx*Ly*Lz;
				N = n*r/100;
				//count number of paths found
				int a, npath = 0;
				for (a = 0; a<100;a++){
					//fill the empty grid with randomly
					fillGrid(g, Lx, Ly, Lz, N, f);
					//Get a random initial particle that is at the top or the botton of the grid
					int x,y,z;
					x = random_i(Lx);
					y = random_i(Ly);
					int temp = random_i(2);
					if (temp == 0){
						z = 0;
					}
					else{
						z = Lz-1;
					}
					particle *p;
					p = &g[z][y][x];
	
					findCluster(g, p, N, Lx, Ly, Lz);
					
					bool path = checkForPath(g, Lx, Ly, Lz);
					if (path == true){
						npath++;
					}
					freeGrid(g, Lx, Ly,Lz);
				}
			
				if (npath*100/a > 45){
	         fprintf(fp,",%d", N);
					break;
				}
			}
       
      }
      fprintf(fp, "\n");
			for(int k= L ; k < L; k++){
				for( int i= 0; i<L;i++){
					free(g[k][i]);
				}
				free(g[k]);
			}
			free(g);
	}
 fclose(fp);
}

void findCluster(particle ***g, particle *p, int N, int Lx,int Ly,int Lz){
	

	//set the value of cluster to one on the initial particle
	p->cluster = 1;
	//Array of pointers to the particles in the cluster
	particle *cluster[N];	
	cluster[0] = p;
	//count the number of particles in the cluster
	int c = 1;
 particle* vi[26];
	//fill the array
	for( int k = 0; k < c; k++){
		//get a particle in the cluster
		particle *a = cluster[k];
		
		//get the array of pointers to the neigbouring particles

		vicinity(a,g,Lx,Ly,Lz, vi);
		//number of neigbouring particles
		int n = a->ng;
		for( int h = 0; h < n; h++){
			//check if the particle is a conductor and isnt already counted 
     // printf("%c, %d\n",vi[h]->type,h);
			if( vi[h]->type != '.' && vi[h]->cluster == 0){
				cluster[c] = vi[h];
				vi[h]->cluster = 2;
				c++;
			}
		}
	}
}

bool checkForPath(particle ***g, int Lx, int Ly, int Lz){
	
	bool path = false;
	//if there is a particle that belongs to the cluster on y=0 and y=Ly-1 then there must be a path between the two
	int w = 0, q = 0, i, j;
	for( i = 0; i < Ly; i++){
		for( j = 0; j < Lx; j++){
			if( g[0][i][j].cluster == 2 || g[0][i][j].cluster == 1){
				 w = 1;
				break;	 
			}
		}
	}

	for(i = 0; i < Ly; i++){
		for( j = 0; j < Lx; j++){
			if( g[Lz-1][i][j].cluster == 2 || g[Lz-1][i][j].cluster == 1){
				 q = 1;
				break;	 
			}
		} 
	}
	if ( w == 1 && q == 1){
		path = true;
	}
	return path;
}

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct particle{
	//type of particle +, x or .
	char type;
	// coordinates of the particle
	int coor[2];
	// 0 if is not part of the cluster , 2 if it is and 1 if is the initial particle
	int cluster;
	// number of accesible plarticles in the surrundings
	int ng;
}particle;

int random_i(int max);
particle **makeGrid(int Lx,int  Ly);
void fillGrid(particle **g, int Lx, int Ly, int N, int f);
void freeGrid(particle **g, int Lx, int Ly);
particle **vicinity(particle *p, particle **grid, int Lx, int Ly);

#endif

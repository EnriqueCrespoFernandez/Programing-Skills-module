
#include<stdio.h>
#include<stdlib.h>
#include "functions.h"



int random_i(int max){
	return( random() % max);
}

particle **makeGrid(int Lx,int  Ly){
	//Build the grid as an 2D pointer
	particle **g = (particle **)malloc(Ly *sizeof(particle *));
	//fill it with dots
	int i,j;
	for( i = 0; i< Ly; i++){
		g[i] = (particle *)malloc(Lx * sizeof(particle));
		for ( j = 0; j<Lx; j++){
			g[i][j].type = '.';
			g[i][j].coor[1] = i;
			g[i][j].coor[0] = j;
		}
	}
	return g;

}
void fillGrid(particle **g, int Lx, int Ly, int N, int f){
	//Put the + and the x
 
	//Number of supercontuctor
	int s = N*f/100;
	//Number of conductors
	int c = N - s;
	// count the total number of conductors/superconductors
	int n = N;
  
	while ( n > 0){
		// get random coordinates
		int x = random_i( Lx);
		int y = random_i( Ly);
		//check if the slot is 'free'
		if ( g[y][x].type == '.'){
			//check if there are any contuctors left to put
			if(c>0){
				g[y][x].type = '+';
				c--;	
			}
			//if not put a superconductor
			else{
				g[y][x].type = 'x';
				s--;		
			}
			n--;
		}
		else{
			continue;
		}
	}
}

void freeGrid(particle **g, int Lx, int Ly){
	
	int i,j;
	for( i = 0; i< Ly; i++){
		for ( j = 0; j<Lx; j++){
			g[i][j].type = '.';
			g[i][j].cluster = 0;
			g[i][j].ng = 0;
		}
	}
}


particle **vicinity(particle *p, particle **grid, int Lx, int Ly){

	//get the coordinates of the initial particle
	int x = p->coor[0];
	int y = p->coor[1];
	
	//Create a pointer to the array of pointers of the neigbouring particles	
	particle **arr = (particle **)malloc( sizeof(particle*));
	
	if ( p->type == '+'){
    *arr = (particle*)malloc(4*sizeof(particle));
		//fill the array depending on the possition of the particle relative to the edges of the grid
		if (x == 0){
			arr[0] = &grid[y][x+1];
			if ( y == 0){
				//Set the number of neigbouring particles dependin on its possition
				p->ng = 2;	
				arr[1] = &grid[y+1][x];  	
			}
			else if( y == Ly-1 ){
				p->ng = 2;	
				arr[1] = &grid[y-1][x];
			}
			else{
				p->ng = 3;	
				arr[1] = &grid[y+1][x]; 
				arr[2] = &grid[y-1][x];	
				
			}
		}
		else if(x == Lx-1){
			arr[0] = &grid[y][x-1];
			if ( y == 0){
				p->ng = 2;	
				arr[1] = &grid[y+1][x];  	
			}
			else if( y == Ly-1 ){
				p->ng = 2;	
				arr[1] = &grid[y-1][x];
			}
			else{
				p->ng = 3;	
				arr[1] = &grid[y+1][x]; 
				arr[2] = &grid[y-1][x];	
			}
		}
		else{
			arr[0] = &grid[y][x+1];
			arr[1] = &grid[y][x-1];
			if ( y == 0){
				p->ng = 3;	
				arr[2] = &grid[y+1][x];  	
			}
			else if( y == Ly-1 ){
				p->ng = 3;	
				arr[2] = &grid[y-1][x];
			}
			else{
				p->ng = 4;	
				arr[2] = &grid[y+1][x]; 
				arr[3] = &grid[y-1][x];	
				
			} 	
		}
		return arr;
	
	}
	else if (p->type == 'x'){

		*arr = (particle*)malloc(8*sizeof(particle));
		if (x == 0){
			arr[0] = &grid[y][x+1];
			if ( y == 0){
				p->ng = 3;	
				arr[1] = &grid[y+1][x];  	
				arr[2] = &grid[y+1][x+1];  	
			}
			else if( y == Ly-1 ){
				p->ng = 3;	
				arr[1] = &grid[y-1][x];
				arr[2] = &grid[y-1][x+1];  	
			}
			else{
				p->ng = 5;	
				arr[1] = &grid[y+1][x]; 
				arr[2] = &grid[y+1][x+1];	
				arr[3] = &grid[y-1][x+1];  	
				arr[4] = &grid[y-1][x];  	
				
			}
		}
		else if(x == Lx-1){
			arr[0] = &grid[y][x-1];
			if ( y == 0){
				p->ng = 3;	
				arr[1] = &grid[y+1][x];  	
				arr[2] = &grid[y+1][x-1];  	
			}
			else if( y == Ly-1 ){
				p->ng = 3;	
				arr[1] = &grid[y-1][x];
				arr[2] = &grid[y-1][x-1];  	
			}
			else{
				p->ng = 5;	
				arr[1] = &grid[y+1][x]; 
				arr[2] = &grid[y+1][x-1];	
				arr[3] = &grid[y-1][x-1];  	
				arr[4] = &grid[y-1][x];  				
			}
		}
		else{
			arr[0] = &grid[y][x+1];
			arr[1] = &grid[y][x-1];
			if ( y == 0){
				p->ng = 5;	
				arr[2] = &grid[y+1][x];  	
				arr[3] = &grid[y+1][x+1];  	
				arr[4] = &grid[y+1][x-1];  	
			}
			else if( y == Ly-1 ){
				p->ng = 5;	
				arr[2] = &grid[y-1][x];
				arr[3] = &grid[y-1][x+1];  	
				arr[4] = &grid[y-1][x+1];  	
			}
			else{
				p->ng = 8;	
					
				arr[2] = &grid[y+1][x];  	
				arr[3] = &grid[y+1][x+1];  	
				arr[4] = &grid[y+1][x-1];  	
				arr[5] = &grid[y-1][x];
				arr[6] = &grid[y-1][x+1];  	
				arr[7] = &grid[y-1][x+1];
			}
		}			
		return arr;
	}
	//if the particle is an insulator return an empty array
	else{
		*arr = (particle*)malloc(sizeof(particle));
		p->ng = 0;
		return arr;
	}
	
}




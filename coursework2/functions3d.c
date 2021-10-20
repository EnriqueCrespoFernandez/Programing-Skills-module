
#include<stdio.h>
#include<stdlib.h>
#include "functions3d.h"



int random_i(int max){
	return( random() % max);
}

particle ***makeGrid(int Lx,int  Ly, int Lz){
	particle ***g = (particle ***)malloc(Lz * sizeof(particle **));
	for(int k = 0; k < Lz; k++){
		//Build the grid as an 2D pointer
		g[k] = (particle **)malloc(Ly *sizeof(particle *));
		//fill it with dots
		int i,j;
		for( i = 0; i< Ly; i++){
			g[k][i] = (particle *)malloc(Lx * sizeof(particle));
			for ( j = 0; j<Lx; j++){
				g[k][i][j].type = '.';
				g[k][i][j].coor[1] = i;
				g[k][i][j].coor[0] = j;
        g[k][i][j].coor[2] = k;
			}
		}
	}
	return g;

}
void fillGrid(particle ***g, int Lx, int Ly,int Lz, int N, int f){
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
		int z = random_i( Lz);
		//check if the slot is 'free'
		if ( g[z][y][x].type == '.'){
			//check if there are any contuctors left to put
			if(c>0){
				g[z][y][x].type = '+';
				c--;	
			}
			//if not put a superconductor
			else{
				g[z][y][x].type = 'x';
				s--;		
			}
			n--;
		}
		else{
			continue;
		}
	}
}

void freeGrid(particle ***g, int Lx, int Ly, int Lz){
	
	int i,j,k;
	for( k = 0; k<Lz;k++){
		for( i = 0; i< Ly; i++){
			for ( j = 0; j<Lx; j++){
				g[k][i][j].type = '.';
				g[k][i][j].cluster = 0;
				g[k][i][j].ng = 0;
			}
		}
	}
}


void vicinity(particle *p, particle ***grid, int Lx, int Ly, int Lz, particle** arr){

	//get the coordinates of the initial particle
	int x = p->coor[0];
	int y = p->coor[1];
	int z = p->coor[2];

	//Create a pointer to the array of pointers of the neigbouring particles	
	if ( p->type == '+'){
		//fill the array depending on the possition of the particle relative to the edges of the grid
		if (z == 0){
			if (x == 0){
				arr[0] = &grid[z][y][x+1];
				arr[1] = &grid[z+1][y][x];
				if ( y == 0){
					//Set the number of neigbouring particles dependin on its possition
					p->ng = 3;	
					arr[2] = &grid[z][y+1][x];
				}
				else if( y == Ly-1 ){
					p->ng = 3;	
					arr[2] = &grid[z][y-1][x];
				}
				else{
          
					p->ng = 4;	
					arr[2] = &grid[z][y+1][x]; 
					arr[3] = &grid[z][y-1][x];	
				
				}
			}
			else if(x == Lx-1){
				arr[0] = &grid[z][y][x-1];
				arr[1] = &grid[z+1][y][x];
				if ( y == 0){
					p->ng = 3;	
					arr[2] = &grid[z][y+1][x];  	
				}
				else if( y == Ly-1 ){
					p->ng = 3;	
					arr[2] = &grid[z][y-1][x];
				}
				else{
					p->ng = 4;	
					arr[2] = &grid[z][y+1][x]; 
					arr[3] = &grid[z][y-1][x];	
				}
			}
			else{
				arr[0] = &grid[z][y][x+1];
				arr[1] = &grid[z][y][x-1];
				arr[2] = &grid[z+1][y][x];
				if ( y == 0){
					p->ng = 4;	
					arr[3] = &grid[z][y+1][x];  	
				}
				else if( y == Ly-1 ){
					p->ng = 4;	
					arr[3] = &grid[z][y-1][x];
				}
				else{
   
					p->ng = 5; 
					arr[3] = &grid[z][y+1][x];         	
					arr[4] = &grid[z][y-1][x];	

				} 	
			}
		}
		else if (z == Lz - 1){
			if (x == 0){
				arr[0] = &grid[z][y][x+1];
				arr[1] = &grid[z-1][y][x];
				if ( y == 0){
					//Set the number of neigbouring particles dependin on its possition
					p->ng = 3;	
					arr[2] = &grid[z][y+1][x];  	
				}
				else if( y == Ly-1 ){
					p->ng = 3;	
					arr[2] = &grid[z][y-1][x];
				}
				else{
					p->ng = 4;	
					arr[2] = &grid[z][y+1][x]; 
					arr[3] = &grid[z][y-1][x];	
				
				}
			}
			else if(x == Lx-1){
				arr[0] = &grid[z][y][x-1];
				arr[1] = &grid[z-1][y][x];
				if ( y == 0){
					p->ng = 3;	
					arr[2] = &grid[z][y+1][x];  	
				}
				else if( y == Ly-1 ){
					p->ng = 3;	
					arr[2] = &grid[z][y-1][x];
				}
				else{
					p->ng = 4;	
					arr[2] = &grid[z][y+1][x]; 
					arr[3] = &grid[z][y-1][x];	
				}
			}
			else{
				arr[0] = &grid[z][y][x+1];
				arr[1] = &grid[z][y][x-1];
				arr[2] = &grid[z-1][y][x];
				if ( y == 0){
					p->ng = 4;	
					arr[3] = &grid[z][y+1][x];  	
				}
				else if( y == Ly-1 ){
					p->ng = 4;	
					arr[3] = &grid[z][y-1][x];
				}
				else{
					p->ng = 5;	
					arr[3] = &grid[z][y+1][x]; 
					arr[4] = &grid[z][y-1][x];	
				
				} 	
			}
		}
		else{
			if (x == 0){
				arr[0] = &grid[z][y][x+1];
				arr[1] = &grid[z+1][y][x];
				arr[2] = &grid[z-1][y][x];
				
				if ( y == 0){
					//Set the number of neigbouring particles dependin on its possition
					p->ng = 4;	
					arr[3] = &grid[z][y+1][x];  	
				}
				else if( y == Ly-1 ){
					p->ng = 4;	
					arr[3] = &grid[z][y-1][x];
				}
				else{
					p->ng = 5;	
					arr[3] = &grid[z][y+1][x]; 
					arr[4] = &grid[z][y-1][x];	
				
				}
			}
			else if(x == Lx-1){
				arr[0] = &grid[z][y][x-1];
				arr[1] = &grid[z+1][y][x];
				arr[2] = &grid[z-1][y][x];
				if ( y == 0){
					p->ng = 4;	
					arr[3] = &grid[z][y+1][x];  	
				}
				else if( y == Ly-1 ){
					p->ng = 4;	
					arr[3] = &grid[z][y-1][x];
				}
				else{
					p->ng = 5;	
					arr[3] = &grid[z][y+1][x]; 
					arr[4] = &grid[z][y-1][x];	
				}
			}
			else{
				arr[0] = &grid[z][y][x+1];
				arr[1] = &grid[z][y][x-1];
				arr[2] = &grid[z+1][y][x];
				arr[3] = &grid[z-1][y][x];
				if ( y == 0){
					p->ng = 5;	
					arr[4] = &grid[z][y+1][x];  	
				}
				else if( y == Ly-1 ){
					p->ng = 5;	
					arr[4] = &grid[z][y-1][x];
				}
				else{
					p->ng = 6;	
					arr[4] = &grid[z][y+1][x]; 
					arr[5] = &grid[z][y-1][x];	
				
				} 	
			}
		}
	}
	else if (p->type == 'x'){
		if (z == 0){
			arr[0] = &grid[z+1][y][x];
			if (x == Lx-1){
				arr[1] = &grid[z][y][x-1];
				if ( y == 0){
					p->ng = 7;	
					arr[2] = &grid[z][y+1][x];  	
					arr[3] = &grid[z][y+1][x-1];
					arr[4] = &grid[z+1][y+1][x];
					arr[5] = &grid[z+1][y][x-1];
					arr[6] = &grid[z+1][y+1][x-1];


				}
				else if( y == Ly-1 ){
					p->ng = 7;	
					arr[2] = &grid[z][y-1][x];  	
					arr[3] = &grid[z][y-1][x-1];
					arr[4] = &grid[z+1][y-1][x];
					arr[5] = &grid[z+1][y][x-1];
					arr[6] = &grid[z+1][y-1][x-1]; 	
				}
				else{
					p->ng = 11;	
					arr[2] = &grid[z][y+1][x];  	
					arr[3] = &grid[z][y+1][x-1];
					arr[4] = &grid[z+1][y+1][x];
					arr[5] = &grid[z+1][y][x-1];
					arr[6] = &grid[z+1][y+1][x-1];
					arr[7] = &grid[z][y-1][x];  	
					arr[8] = &grid[z][y-1][x-1];
					arr[9] = &grid[z+1][y-1][x];
					arr[10] = &grid[z+1][y-1][x-1];  	
					
				}
			}
			else if(x == 0){
				arr[1] = &grid[z][y][x+1];
				if ( y == 0){
					p->ng = 7;	
					arr[2] = &grid[z][y+1][x];  	
					arr[3] = &grid[z][y+1][x+1];
					arr[4] = &grid[z+1][y+1][x];
					arr[5] = &grid[z+1][y][x+1];
					arr[6] = &grid[z+1][y+1][x+1];


				}
				else if( y == Ly-1 ){
					p->ng = 7;	
					arr[2] = &grid[z][y-1][x];  	
					arr[3] = &grid[z][y-1][x+1];
					arr[4] = &grid[z+1][y-1][x];
					arr[5] = &grid[z+1][y][x+1];
					arr[6] = &grid[z+1][y-1][x+1]; 	
				}
				else{
					p->ng = 11;	
					arr[2] = &grid[z][y+1][x];  	
					arr[3] = &grid[z][y+1][x+1];
					arr[4] = &grid[z+1][y+1][x];
					arr[5] = &grid[z+1][y][x+1];
					arr[6] = &grid[z+1][y+1][x+1];
					arr[7] = &grid[z][y-1][x];  	
					arr[8] = &grid[z][y-1][x+1];
					arr[9] = &grid[z+1][y-1][x];
					arr[10] = &grid[z+1][y-1][x+1];  	
					
				}
			}				
			else{
				arr[1] = &grid[z][y][x+1];
				arr[2] = &grid[z][y][x-1];
				if ( y == 0){
					p->ng = 11;	
					arr[3] = &grid[z][y+1][x];  	
					arr[4] = &grid[z][y+1][x+1];
					arr[5] = &grid[z][y+1][x-1];
					arr[6] = &grid[z+1][y+1][x];
					arr[7] = &grid[z+1][y][x+1];
					arr[8] = &grid[z+1][y+1][x+1];	
					arr[9] = &grid[z+1][y][x-1];
					arr[10] = &grid[z+1][y+1][x-1];



				}
				else if( y == Ly-1 ){
					p->ng = 11;	
					arr[3] = &grid[z][y-1][x];  	
					arr[4] = &grid[z][y-1][x+1];
					arr[5] = &grid[z][y-1][x-1];
					arr[6] = &grid[z+1][y-1][x];
					arr[7] = &grid[z+1][y][x+1];
					arr[8] = &grid[z+1][y-1][x+1];	
					arr[9] = &grid[z+1][y][x-1];
					arr[10] = &grid[z+1][y-1][x-1];
				}
				else{
					p->ng = 17;	
					arr[3] = &grid[z][y+1][x+1];
					arr[4] = &grid[z+1][y+1][x];
					arr[5] = &grid[z+1][y][x+1];
					arr[6] = &grid[z+1][y+1][x+1];
					arr[7] = &grid[z][y-1][x];  	
					arr[8] = &grid[z][y-1][x+1];
					arr[9] = &grid[z+1][y-1][x];
					arr[10] = &grid[z+1][y-1][x+1]; 
					arr[11] = &grid[z][y+1][x-1];
					arr[12] = &grid[z+1][y][x-1];
					arr[13] = &grid[z+1][y+1][x-1];
					arr[14] = &grid[z][y-1][x-1];
					arr[15] = &grid[z+1][y-1][x-1]; 
					arr[16] = &grid[z][y+1][x];  	
                  
					
				}
			}
		}
		else if (z == Lz -1){
			arr[0] = &grid[z-1][y][x];
			if (x == Lx-1){
				arr[1] = &grid[z][y][x-1];
				if ( y == 0){
					p->ng = 7;	
					arr[2] = &grid[z][y+1][x];  	
					arr[3] = &grid[z][y+1][x-1];
					arr[4] = &grid[z-1][y+1][x];
					arr[5] = &grid[z-1][y][x-1];
					arr[6] = &grid[z-1][y+1][x-1];


				}
				else if( y == Ly-1 ){
					p->ng = 7;	
					arr[2] = &grid[z][y-1][x];  	
					arr[3] = &grid[z][y-1][x-1];
					arr[4] = &grid[z-1][y-1][x];
					arr[5] = &grid[z-1][y][x-1];
					arr[6] = &grid[z-1][y-1][x-1]; 	
				}
				else{
					p->ng = 11;	
					arr[2] = &grid[z][y+1][x];  	
					arr[3] = &grid[z][y+1][x-1];
					arr[4] = &grid[z-1][y+1][x];
					arr[5] = &grid[z-1][y][x-1];
					arr[6] = &grid[z-1][y+1][x-1];
					arr[7] = &grid[z][y-1][x];  	
					arr[8] = &grid[z][y-1][x-1];
					arr[9] = &grid[z-1][y-1][x];
					arr[10] = &grid[z-1][y-1][x-1];  	
					
				}
			}
			else if(x == 0){
				arr[1] = &grid[z][y][x+1];
				if ( y == 0){
					p->ng = 7;	
					arr[2] = &grid[z][y+1][x];  	
					arr[3] = &grid[z][y+1][x+1];
					arr[4] = &grid[z-1][y+1][x];
					arr[5] = &grid[z-1][y][x+1];
					arr[6] = &grid[z-1][y+1][x+1];


				}
				else if( y == Ly-1 ){
					p->ng = 7;	
					arr[2] = &grid[z][y-1][x];  	
					arr[3] = &grid[z][y-1][x+1];
					arr[4] = &grid[z-1][y-1][x];
					arr[5] = &grid[z-1][y][x+1];
					arr[6] = &grid[z-1][y-1][x+1]; 	
				}
				else{
					p->ng = 11;	
					arr[2] = &grid[z][y+1][x];  	
					arr[3] = &grid[z][y+1][x+1];
					arr[4] = &grid[z-1][y+1][x];
					arr[5] = &grid[z-1][y][x+1];
					arr[6] = &grid[z-1][y+1][x+1];
					arr[7] = &grid[z][y-1][x];  	
					arr[8] = &grid[z][y-1][x+1];
					arr[9] = &grid[z-1][y-1][x];
					arr[10] = &grid[z-1][y-1][x+1];  	
					
				}
			}				
			else{
				arr[1] = &grid[z][y][x+1];
				arr[2] = &grid[z][y][x-1];
				if ( y == 0){
					p->ng = 11;	
					arr[3] = &grid[z][y+1][x];  	
					arr[4] = &grid[z][y+1][x+1];
					arr[5] = &grid[z][y+1][x-1];
					arr[6] = &grid[z-1][y+1][x];
					arr[7] = &grid[z-1][y][x+1];
					arr[8] = &grid[z-1][y+1][x+1];	
					arr[9] = &grid[z-1][y][x-1];
					arr[10] = &grid[z-1][y+1][x-1];



				}
				else if( y == Ly-1 ){
					p->ng = 11;	
					arr[3] = &grid[z][y-1][x];  	
					arr[4] = &grid[z][y-1][x+1];
					arr[5] = &grid[z][y-1][x-1];
					arr[6] = &grid[z-1][y-1][x];
					arr[7] = &grid[z-1][y][x+1];
					arr[8] = &grid[z-1][y-1][x+1];	
					arr[9] = &grid[z-1][y][x-1];
					arr[10] = &grid[z-1][y-1][x-1];
				}
				else{
					p->ng = 17;	
					arr[3] = &grid[z][y+1][x+1];
					arr[4] = &grid[z-1][y+1][x];
					arr[5] = &grid[z-1][y][x+1];
					arr[6] = &grid[z-1][y+1][x+1];
					arr[7] = &grid[z][y-1][x];  	
					arr[8] = &grid[z][y-1][x+1];
					arr[9] = &grid[z-1][y-1][x];
					arr[10] = &grid[z-1][y-1][x+1]; 
					arr[11] = &grid[z][y+1][x-1];
					arr[12] = &grid[z-1][y][x-1];
					arr[13] = &grid[z-1][y+1][x-1];
					arr[14] = &grid[z][y-1][x-1];
					arr[15] = &grid[z-1][y-1][x-1]; 
					arr[16] = &grid[z][y+1][x];  	
					
				}
			}
		}
		else{
			arr[0] = &grid[z+1][y][x];
			arr[1] = &grid[z-1][y][x];
			if (x == Lx-1){
				arr[2] = &grid[z][y][x-1];
				if ( y == 0){
					p->ng = 11;	
					arr[10] = &grid[z][y+1][x];  	
					arr[3] = &grid[z][y+1][x-1];
					arr[4] = &grid[z+1][y+1][x];
					arr[5] = &grid[z+1][y][x-1];
					arr[6] = &grid[z+1][y+1][x-1];
					arr[7] = &grid[z-1][y+1][x];
					arr[8] = &grid[z-1][y][x-1];
					arr[9] = &grid[z-1][y+1][x-1];


				}
				else if( y == Ly-1 ){
					p->ng = 11;	
					arr[10] = &grid[z][y-1][x];  	
					arr[3] = &grid[z][y-1][x-1];
					arr[4] = &grid[z+1][y-1][x];
					arr[5] = &grid[z+1][y][x-1];
					arr[6] = &grid[z+1][y-1][x-1];
					arr[7] = &grid[z-1][y-1][x];
					arr[8] = &grid[z-1][y][x-1];
					arr[9] = &grid[z-1][y-1][x-1];
	
				}
				else{
					p->ng = 17;	
					arr[15] = &grid[z][y+1][x];  	
					arr[3] = &grid[z][y+1][x-1];
					arr[4] = &grid[z+1][y+1][x];
					arr[5] = &grid[z+1][y][x-1];
					arr[6] = &grid[z+1][y+1][x-1];
					arr[7] = &grid[z][y-1][x];  	
					arr[8] = &grid[z][y-1][x-1];
					arr[9] = &grid[z+1][y-1][x];
					arr[10] = &grid[z+1][y-1][x-1];  
					arr[11] = &grid[z-1][y+1][x];
					arr[12] = &grid[z-1][y][x-1];
					arr[13] = &grid[z-1][y+1][x-1];	
					arr[14] = &grid[z-1][y-1][x];
					arr[16] = &grid[z-1][y-1][x-1]; 
					
				}
			}
			else if(x == 0){
				arr[2] = &grid[z][y][x+1];
				if ( y == 0){
					p->ng = 11;	
					arr[10] = &grid[z][y+1][x];  	
					arr[3] = &grid[z][y+1][x+1];
					arr[4] = &grid[z+1][y+1][x];
					arr[5] = &grid[z+1][y][x+1];
					arr[6] = &grid[z+1][y+1][x+1];
					arr[7] = &grid[z-1][y+1][x];
					arr[8] = &grid[z-1][y][x+1];
					arr[9] = &grid[z-1][y+1][x+1];
					arr[10] = &grid[z][y+1][x];
				}
				else if( y == Ly-1 ){
					p->ng = 11;	  	
					arr[3] = &grid[z][y-1][x+1];
					arr[4] = &grid[z+1][y-1][x];
					arr[5] = &grid[z+1][y][x+1];
					arr[6] = &grid[z+1][y-1][x+1];
					arr[7] = &grid[z-1][y-1][x];
					arr[8] = &grid[z-1][y][x+1];
					arr[9] = &grid[z-1][y-1][x+1];
          arr[10] = &grid[z][y-1][x];
				}
				else{
					p->ng = 17;	

					arr[3] = &grid[z][y+1][x+1];
					arr[4] = &grid[z+1][y+1][x];
					arr[5] = &grid[z+1][y][x+1];
					arr[6] = &grid[z+1][y+1][x+1];
					arr[7] = &grid[z][y-1][x];  	
					arr[8] = &grid[z][y-1][x+1];
					arr[9] = &grid[z+1][y-1][x];
					arr[10] = &grid[z+1][y-1][x+1];  
					arr[11] = &grid[z-1][y+1][x];
					arr[12] = &grid[z-1][y][x+1];
					arr[13] = &grid[z-1][y+1][x+1];	
					arr[14] = &grid[z-1][y-1][x];
					arr[16] = &grid[z-1][y-1][x+1]; 
     			arr[15] = &grid[z][y+1][x];  	

				}
			}					
			else{
				arr[2] = &grid[z][y][x+1];
				arr[3] = &grid[z][y][x-1];
				if ( y == 0){
					p->ng = 17;	
					arr[4] = &grid[z][y+1][x];  	
					arr[5] = &grid[z][y+1][x+1];
					arr[6] = &grid[z][y+1][x-1];
					arr[7] = &grid[z+1][y+1][x];
					arr[8] = &grid[z+1][y][x+1];
					arr[9] = &grid[z+1][y+1][x+1];	
					arr[10] = &grid[z+1][y][x-1];
					arr[11] = &grid[z+1][y+1][x-1];
					arr[12] = &grid[z-1][y+1][x];
					arr[13] = &grid[z-1][y][x+1];
					arr[14] = &grid[z-1][y+1][x+1];	
					arr[15] = &grid[z-1][y][x-1];
					arr[16] = &grid[z-1][y+1][x-1];



				}
				else if( y == Ly-1 ){
					p->ng = 17;	
					arr[4] = &grid[z][y-1][x];  	
					arr[5] = &grid[z][y-1][x+1];
					arr[6] = &grid[z][y-1][x-1];
					arr[7] = &grid[z+1][y-1][x];
					arr[8] = &grid[z+1][y][x+1];
					arr[9] = &grid[z+1][y-1][x+1];	
					arr[10] = &grid[z+1][y][x-1];
					arr[11] = &grid[z+1][y-1][x-1];
					arr[12] = &grid[z-1][y-1][x];
					arr[13] = &grid[z-1][y][x+1];
					arr[14] = &grid[z-1][y-1][x+1];	
					arr[15] = &grid[z-1][y][x-1];
					arr[16] = &grid[z-1][y-1][x-1];
				}
				else{
					p->ng = 26;	
					arr[4] = &grid[z][y+1][x+1];
					arr[5] = &grid[z+1][y+1][x];
					arr[6] = &grid[z+1][y][x+1];
					arr[7] = &grid[z+1][y+1][x+1];
					arr[8] = &grid[z][y-1][x];  	
					arr[9] = &grid[z][y-1][x+1];
					arr[10] = &grid[z+1][y-1][x];
					arr[11] = &grid[z+1][y-1][x+1]; 
					arr[12] = &grid[z][y+1][x-1];
					arr[13] = &grid[z+1][y][x-1];
					arr[14] = &grid[z+1][y+1][x-1];
					arr[15] = &grid[z][y-1][x-1];
					arr[16] = &grid[z+1][y-1][x-1]; 
					arr[17] = &grid[z][y+1][x];  
					arr[18] = &grid[z-1][y+1][x];
					arr[19] = &grid[z-1][y][x+1];
					arr[20] = &grid[z-1][y+1][x+1];	
					arr[21] = &grid[z-1][y-1][x];
					arr[22] = &grid[z-1][y-1][x+1];
					arr[23] = &grid[z-1][y][x-1];
					arr[24] = &grid[z-1][y+1][x-1];
					arr[25] = &grid[z-1][y-1][x-1]; 

					
				}
			}
		}	
	}
	//if the particle is an insulator return an empty array
	else if  (p->type == '.'){
         p->ng = 0;
   }
	
}




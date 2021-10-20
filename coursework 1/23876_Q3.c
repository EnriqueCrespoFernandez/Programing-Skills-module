#include <stdio.h>
#include <math.h>
//Array of pointers of the functions
float(*f[2])(float,float);
//Ventor F(x)
float F[2];
//Jacobian matrix
float m[2][2];

//Number of significant figures
int e;

float f1 (float x, float y){
	return pow(x+1,2) + pow (y+1,2)-25;
}

float f2 (float x, float y){
	return x*y + pow(y,2) - 5;
}

float dfx(int i, float x, float y){	
	return (f[i](x,y) - f[i](x +0.001,y))/(0.001);
}

float dfy (int i,float x, float y){
	return (f[i](x,y) - f[i](x,y +0.001))/(0.001);
}

//Calculates de jacobian matrix
void J(float r[2]){

	//Aproximate de derivatives
	m[0][0] = dfx(0,r[0],r[1]);
	m[0][1] = dfy(0,r[0],r[1]);
	m[1][0] = dfx(1,r[0],r[1]);
	m[1][1] = dfy(1,r[0],r[1]);
	
	// inverts the matix
	float det;
	det = m[0][0] * m[1][1] - m[1][0]*m[0][1];
	float inv[2][2];
	inv[0][0] =   m[1][1] / det;
	inv[1][0] = - m[1][0] / det;
	inv[0][1] = - m[0][1] / det;
	inv[1][1] =   m[0][0] / det;
	
	// saves the found values on the matrix declared above
	for (int i = 0 ; i < 2 ; i++){
		for (int j = 0 ; j < 2 ; j++){
			m[i][j] = inv[i][j];
		}
	}
}

float *delta(float r[2]){
	
	//Create the jacobian
	J(r);
	
	static float d[2];
	//Find the delta
	for (int i = 0 ; i < 2; i++){
		d[i] = m[i][0] * f[0](r[0],r[1])+ m[i][1] * f[1](r[0],r[1]);
	}
	
	return d;
}

//Find the norm of F(x)
float norm(float f[], int size){
	
	float n = 0;
	for(int i = 0; i < size; i++){
		n = n + fabs(f[i]);
	}
	return n;
}

void main (){
	
	printf("Please type the number of significant figures required: \n");
	scanf("%d", &e);
		
	//Put the functions in the array
	f[0] = f1;
	f[1] = f2;

	float r[2];
	
	//Array to store the values to plot the graph
	float p[1001][4];
 
	int n = 0,m = 0;

	//Array to store all the roots found
	float a[1001][2];
 
	//iterate to change the initial value of (x,y)
	for( float t = 0; t < 100 ; t= t + 0.1){
		
		float *x = &r[0];
    		float *y = &r[1];
     
		r[0] = 0.1*(cos(t) + t*sin(t));
		r[1] = 0.1*(sin(t) - t*cos(t));
		
		p[n][0] = *x;
		p[n][1] = *y;
			
		F[0] = f[0](*x,*y);
		F[1] = f[1](*x,*y);
			
		float norm_F = norm(F, 2);
		
		int n_iterations = 0;
		while (fabs(norm_F) > pow(10,-e) && n_iterations < 100){
			
			float *d = delta(r);
			
			r[0] = r[0] + d[0];
			r[1] = r[1] + d[1];
			
			F[0] = f[0](*x,*y);
			F[1] = f[1](*x,*y);
			norm_F = norm(F, 2);
			n_iterations++;
		}
		
		if (!isnan(r[0]) && !isnan(r[1]) && n_iterations < 100){
			
			a[n][0] = *x;
			a[n][1] = *y;	
			
			p[n][2] = *x;
			
			m++;
			n++;
		}
	}

	//remove duplicates
	int i,j,k; 
	for(i=0; i<n; i++){

    		for(j=i+1; j<n; j++){
      			
			// If any duplicate found
			if(fabs(a[i][1] - a[j][1]) < pow(10,-e) && fabs(a[i][0]-a[j][0])< pow(10,-e)){
        			
				// Delete the current duplicate element
				for(k=j; k<n; k++){
					a[k][0] = a[k + 1][0];
					a[k][1] = a[k + 1][1];
				}
				//Decrement size after removing duplicate element
				n--;
        			// If shifting of elements occur then don't increment j
        			j--;
			}
		}
	}
        

	// fill the 4th column with the indices and write it on the CSV file
	FILE *fp;
	fp = fopen("mapa.csv", "w");
	for(i = 0 ; i<m; i++){
		//give a value 1 to n to the 4th column depending on which root it is
		for( j = 0; j<n ; j++){
			if (fabs( p[i][2] - a[j][0]) < pow(10,-e)){
				p[i][3] = j;
                		fprintf(fp,"%f, %f, %f\n",p[i][0], p[i][1],p[i][3]);

			}
		}
	}
	fclose(fp);

	//Print array after deleting duplicate elements
	printf("\nThe program has found %d solutions : \n", n);
  	
	for(i=0; i<n; i++){
		printf("x%d = %f, y = %f\n",i+1, a[i][0],a[i][1]);
	}
  
}

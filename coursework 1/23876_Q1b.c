#include<stdio.h>
#include<math.h>
FILE *fp;

const float pi = M_PI;

//Set the wave length at 500 nm
float L = 500; 
//Asume Io = 1
int Io = 1;

float y(float t, float X, int m){
	/*the function inside de integral of Jm(x)*/
	return cos(m*t- X * sin(t));
}

float J(int m,float X){
	int N = 10000;
	float h = pi / (float) (N-1);
	
	int i = 1;
	float a = 0;
	while(i < N){
	a = a + y(h*i ,X,m);
	i++;
	}

	return (1/pi) * 0.5 * h * ( y(0.0, X,m) + 2*a + y(pi, X, m) );
	
}

float Intensity(float r){
	//Simplifing the formula for x using r in μm and L in nm
	float x = pi * r * 100 / L;
	return Io*pow(2*J(1,x)/x,2);

}


void main(){
	//open csv file
	fp = fopen("data_1b.csv", "w");
	// Table headers
	fprintf(fp, "r, I\n");	
	float I;

	float r = -25.0;
	while (r < 25.1 ){
		//Exception when x = 0 because it would be undefied with Bessel's formula
		if (fabs(r) < 0.01){ 
			I = Io;
		}else{
			I = Intensity(r);
		}
		
		fprintf(fp, "%f,%f\n",r, I);
		r= r +0.1;
	}
	fclose(fp);
}

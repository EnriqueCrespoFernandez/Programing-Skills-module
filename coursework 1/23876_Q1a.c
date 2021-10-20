#include<stdio.h>
#include<math.h>
FILE *fp;

const float pi = M_PI;

//for the sake of convinience i define the function y which is the function inside the integral on Bessel's function
float y(float t, float X, int m){

	return cos(m*t- X * sin(t));
}

//A function that aproximates the value of J(x) using the trapezium method
float J(int m,float X){
	
	int N = 10000;

	float h = pi / (float) (N-1);
	
	int i = 1;
	float a = 0;
	while(i < N+1){
		a = a + y(h*i ,X,m);
		i++;
	}

	return (1/pi) * 0.5 * h * ( y(0.0, X,m) + 2*a + y(pi, X, m) );
	
}



void main(){
	//Open a .csv file to write the calculated values
	fp = fopen("data_1a.csv", "w");

	//Table headers
	fprintf(fp, "x,J0(x),J1(x),J2(x)\n");
	
	//Calculate the values of x between 0 and 20 for m = 0,1,2
	float x = 0.0;
	while(x <= 20){
		float a[3];
		for(int m = 0; m < 3; m++){
			a[m] = J(m,x);
		}
		//Print the values of each x for m=0,1,2
		fprintf(fp, "%.2f,%f,%f,%f\n",x, a[0],a[1],a[2]);

		x = x + 0.1;
	}	
	fclose(fp);

}

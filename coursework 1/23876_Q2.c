#include <stdio.h>
#include <math.h>

//Define the function
float f(float x){
	
	return 1/pow(x+1,2) + 1/pow(x-1,2) - 10;

}

//Secand method equation
float sec(float x1,float x2){ 

	return x2 - f(x2) * (x2-x1)/(f(x2) - f(x1));

}

float findRoot(float x1,float x2, int e){
		float x3 = 0.0; 
		int n_iterations = 0;
		//Execute the secant method
		while (fabs(f(x3))> pow(10,-e)){
			if (n_iterations< 100){
				x3 = sec(x1,x2);  
				x1 = x2;
				x2 = x3;
				n_iterations++;
			}else{
				return 0.0/0.0;
			}
		}
		return x3;	
}

void main(){
	
	
	//Define the how many decimal posistions close is enough
	int e;
	printf("Type the number (1 to 5) of significant figures:  ");
	scanf("%d", &e);

	float x1, x2;
	//Array that will store the roots of f(x)	
	float sol[100];
	//Count the roots found
	int n = 0;

	// Loop to change the initial value of x2
	for (float t = -2.0; t < 2.1; t = t +0.1){
		// Assaing initial values to x1, x2, x3
		x2 = t;
		x1 = 0.0;
		float root = findRoot(x1,x2,e);
		if(!isnan(root)){
			sol[n] = root;
			n++;
		}
	}
	
	

	// Check for duplicated roots and remove them

	int i,j,k;
	for(i=0; i<n; i++){
	
		for(j=i+1; j<n; j++){
			
			// If any duplicate found 
			if(fabs(sol[i] - sol[j]) < pow(10,-e)){
				// Delete the current duplicate element
				for(k=j; k<n; k++){ 
					sol[k] = sol[k + 1];
				}
                		//Decrement size after removing duplicate element
                		n--;

                		// If shifting of elements occur then don't increment j
                		j--;
            		}
        	}
	}
	
    	//Print array after deleting duplicate elements
    
	printf("\nThe program has found %d roots: \n", n);

    	for(i=0; i<n; i++){
		printf("x%d = %f\n",i+1, sol[i]);
	}
}


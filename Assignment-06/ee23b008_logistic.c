/*
Roll No: EE23B008
Date:26-09-2023
Description: Generating a Logistic map using c and displaying it on a graph using gnuplot
input arguements :
1. niter: number of iterations of x for each r value
2. rstep : incrementation in the value of r
3. error : accepted error value below which iterations stops for some x.

*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
// Defining the logistic map function as graph
float graph(float r, float x){
	float y = r*x*(1-x);
	return y;
}

int main(int argc, char **argv){
	FILE *f1 = fopen("out.txt", "w");
// Getting input from command line
	int niter = atoi(argv[1]);
	float rstep = atof(argv[2]);
	float error = atof(argv[3]);

    // Loop through different r values
	for(float r=0.1;r<=4;r=r+rstep){
		float x=0.5; 
		for (int i=0; i < niter; i++){
			float n_x = graph(r, x);
			float e= (fabs(n_x-x)/x)*100;
			x = n_x;
		 // Break if x exceeds 1
                	if (x>1){break;}
		 // Break if error is below the accepted threshold
			if (e<error){
				fprintf(f1, "%-10.6f %-10.6f\n" ,r,x);
				break;
			}
	        // Print data after 10% of iterations
			if (i>ceil(niter/10)){
				fprintf(f1, "%-10.6f %-10.6f\n" ,r,x);
			}
		}
	}
	fclose(f1);
}
  


		

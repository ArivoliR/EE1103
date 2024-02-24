// EE23B008
// 18th August 2023
// Version 1.0
// A C program that displays the estimated value of sin(x) using the truncated series and the error between the estimated value and the true value of the sin(x) function.
// fact function returns the factorial of the given number
// n is the number of truncated terms in the sin(x) series expansion
// Input: executible name, number of terms for taylor series, value of angle
// Output: sine value, error value


#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <number of terms> <value of x>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    float x = atof(argv[2]);

    float estimated_sin;
    float true_sin;
    true_sin = sin(x);
    float error = 0.0;

    int fact(int c){
	    int tmp = 1;
	    int j;
	    for (int j=1; j<=c; j++){
		    tmp = tmp * j;
	    }
	    return tmp;
    }
    for (int i = 0; i < n; i++) {
        int exponent;
	exponent= 2 * i + 1;
	float term=0;
       	term= pow(x, exponent) / fact(exponent);
        if (i % 2 == 0) {
            estimated_sin += term;
        } else {
            estimated_sin -= term;
        }
    }

    error = fabs(true_sin - estimated_sin);
    printf("%.3f, %.3f\n", estimated_sin, error);

    return 0;
}

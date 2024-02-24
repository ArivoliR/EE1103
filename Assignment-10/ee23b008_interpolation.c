/*
Name: Arivoli Ramamoorthy
Roll no: EE23B008
Description:
-This program demonstrates polynomial interpolation using both Lagrange and Newton methods.
-It generates equidistant points on a specified interval, calculates y values for a given function,
and performs Lagrange interpolation to find y values for new x points. It then uses the results
from Lagrange interpolation as inputs to perform Newton interpolation to find the y value
at a specific point x0.
Usage: ./a.out polynomial_order xstart xend x0
 - polynomial_order: Degree of the polynomial (n)
 - xstart: Start of the interval
 - xend: End of the interval
 - x0: The point at which we interpolate the y value
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// function f(x)
double f(double x) {
    return 1.0 / (1.0 + 25.0 * x * x);
}

// Lagrange interpolation function to calculate the interpolated value at a point x
double lagrange(double x, double xi[], double yi[], int n) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        double term = yi[i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                term *= (x - xi[j]) / (xi[i] - xi[j]);
            }
        }
        result += term;
    }
    return result;
}

// function for newton interpolation to calculate the interpolated value at a point x0
double newton(double x, double xi[], double yi[], int n) {
// arrays to store intermediate results
    double yint[n];
    double ea[n];

    for (int i = 0; i < n; i++) {
        yint[i] = yi[i];
        ea[i] = yi[i];
    }

    double result = yint[0];
    double term = 1.0;

    for (int order = 1; order < n; order++) {
        term *= (x - xi[order - 1]);

        for (int i = 0; i < n - order; i++) {
            ea[i] = (yint[i + 1] - yint[i]) / (xi[i + order] - xi[i]);
            yint[i] = ea[i];
        }

        result += term * yint[0];
    }

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s polynomial_order xstart xend x0\n", argv[0]);
        return 1;
    }
// Parsing command line arguments
    int polynomial_order = atoi(argv[1]);
    double xstart = atof(argv[2]);
    double xend = atof(argv[3]);
    double x0 = atof(argv[4]);

    int n = polynomial_order + 1;
    double xi[n], yi[n];

    // Generate equidistant points
    for (int i = 0; i < n; i++) {
        xi[i] = xstart + i * (xend - xstart) / polynomial_order;
        yi[i] = f(xi[i]); 
    }

    double step = (xend - xstart) / polynomial_order;
    double ynewt[n];
    double xnewt[n];
    for (int i = 0; i < n; i++) {     // adding dx to the x coordinate and calculate corresponding y values
        xnewt[i] = xi[i] + step / 20;
        ynewt[i] = lagrange(xnewt[i], xi, yi, n);
    }

    float y = newton(x0, xnewt, ynewt, n);
    printf("%f\n", y);  //printing value of newt(x0)

    return 0;
}

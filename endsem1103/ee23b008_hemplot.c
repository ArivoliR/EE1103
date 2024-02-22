/*
Name: Arivoli Ramamoorthy
Roll number: ee23b008
Date: 14/11/2023
Version: 1.0
Description: Generates and plots a Fibonacci spiral in polar coordinates.
Inputs: Center coordinates (xo, yo), initial radius (ro), number of iterations
(iter). {All are hardcoded as mentioned in question) Output: Saves the generated
coordinates to a file
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Function to plot the Fibonacci spiral in polar coordinates and save it to a
// file
void hemplot(int xo, int yo, double ro, int iter, const char *output_file) {
  FILE *output = fopen(output_file, "w");
  if (output == NULL) {
    perror("Error opening output file");
    return;
  }

  double x, y, r, theta;
  int a = 2, b = 1; // Current and previous Hem numbers

  for (int i = 0; i < iter; i++) {
    r = ro * (double)a / b;
    theta = (2 * M_PI * a) / b; // Generates the Fibonacci spiral
    x = xo + r * cos(theta);
    y = yo + r * sin(theta);
    fprintf(output, "%lf %lf\n", x, y);

    // Calculate the next Fibonacci number
    a = a + b;
    // Update the previous Fibonacci number
    b = a - b;
  }

  fclose(output);

  // Call Gnuplot commands for visualization
  FILE *gnuplotPipe = popen("gnuplot", "w");
  if (gnuplotPipe != NULL) {
    fprintf(gnuplotPipe, "set term png size 800,800\n");
    fprintf(gnuplotPipe, "set output 'ee23b008_hemplot.jpg\n");
    fprintf(gnuplotPipe, "set title 'ee23b008_hemplot'\n");
    fprintf(gnuplotPipe, "set xlabel 'X'\n");
    fprintf(gnuplotPipe, "set ylabel 'Y'\n");
    fprintf(
        gnuplotPipe,
        "plot 'fibonacci_spiral.txt' with points title 'Fibonacci Spiral'\n");
    fprintf(gnuplotPipe, "exit\n");
    pclose(gnuplotPipe);
  } else {
    perror("Error opening Gnuplot pipe");
  }
}

int main() {
  int xo = 0;                                       // Center x-coordinate
  int yo = 0;                                       // Center y-coordinate
  double ro = 1;                                    // Initial radius
  int iter = 200;                                   // Number of iterations
  const char *output_file = "fibonacci_spiral.txt"; // Output file name

  hemplot(xo, yo, ro, iter, output_file);

  return 0;
}

/*
Name: Arivoli Ramamoorthy
Roll number: EE23B008
Date: 13-10-2023
Description: 
-Convert the pseudocode for Elimination, Pivoting and Substitution into C code
-Read the system of equations from a file (the file will contain N rows and N+1 columns(each row being one linear equation))
-Using Gaussian elimination, solve the system of equations
Input: inputfilename N
Output: Solutions for x1,x2,x3,....,xN
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void Eliminate(double **a, double *s, int n, double *b, double tol, int *er);
void Pivot(double **a, double *b, double *s, int n, int k);
void Substitute(double **a, int n, double *b, double *x);

void Gauss(double **a, double *b, int n, double *x, double tol, int *er) {
    int k;
    double *s = malloc(n * sizeof(double));
    
    for (int i = 0; i < n; i++) {
        s[i] = fabs(a[i][0]);  
        for (int j = 0; j < n; j++) {
            double abs_a = fabs(a[i][j]);
            if (abs_a > s[i]) {
                s[i] = abs_a;
            }
        }
    }
    
    Eliminate(a, s, n, b, tol, er);
    if (*er != -1) {                // If Gaussian elimination was successful, perform substitution to find the solution
        Substitute(a, n, b, x);
    }
    free(s);
}

void Eliminate(double **a, double *s, int n, double *b, double tol, int *er) { // Function to perform Gaussian elimination
    for (int k = 0; k < n - 1; k++) {
        Pivot(a, b, s, n, k);
        if (fabs(a[k][k] / s[k]) < tol) {
            *er = -1;
            break;
        }
        for (int i = k + 1; i < n; i++) {
            double factor = a[i][k] / a[k][k];
            for (int j = k + 1; j < n; j++) {
                a[i][j] -= factor * a[k][j];
            }
            b[i] -= factor * b[k];
        }
    }
    if (fabs(a[n - 1][n - 1] / s[n - 1]) < tol) {  
        *er = -1;
    }
}

void Pivot(double **a, double *b, double *s, int n, int k) { // Function to pivot rows for numerical stability
    int p = k;
    double big = fabs(a[k][k] / s[k]);

    for (int i1 = k + 1; i1 < n; i1++) {
        double dummy = fabs(a[i1][k] / s[i1]);
        if (dummy > big) {
            p = i1;
            big = dummy;
        }
    }

    if (p != k) {
        for (int j1 = k; j1 < n; j1++) {
            double temp = a[k][j1];
            a[k][j1] = a[p][j1];
            a[p][j1] = temp;
        }
        double temp = b[p];
        b[p] = b[k];
        b[k] = temp;

        temp = s[p];
        s[p] = s[k];
        s[k] = temp;
    }
}

void Substitute(double **a, int n, double *b, double *x) {      // Function to substitute and find the solution
    x[n - 1] = b[n - 1] / a[n - 1][n - 1]; 
    for (int i = n - 2; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += a[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / a[i][i];
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Format: %s <filename> <N>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int N = atoi(argv[2]);
    
    // Allocate memory
    double **a = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        a[i] = (double *)malloc((N + 1) * sizeof(double));
    }

    double *b = (double *)malloc(N * sizeof(double));
    double *x = (double *)malloc(N * sizeof(double));
    int er = 0;
    double tol = 0.0000000001;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
            if (fscanf(file, "%lf", &a[i][j]) != 1) {
                printf("Error reading data from the file.\n");
                return 1;
            }
        }
    }

    fclose(file);

    for (int i = 0; i < N; i++) {
        b[i] = a[i][N];
    }

    Gauss(a, b, N, x, tol, &er);

    if (er == -1) {
        printf("No unique solution for the given matrix.\n");
        return 1;
    }

    printf("Results:\n");
    for (int i = 0; i < N; i++) {
        printf("%.6f\n", x[i]);
    }

    // Clean up allocated memory
    for (int i = 0; i < N; i++) {
        free(a[i]);
    }
    free(a);
    free(b);
    free(x);

    return 0;
}

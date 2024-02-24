/*
Name : Rohita Datta Nalluri
       Arivoli R
Roll Number : EE23B065
              EE23B008
Input : Number of spline functions/ number of intervals, xu(point for which interpolation is to be done)
Output : interpolated value for xu ie, f(xu)
*/

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

void initialise(int N, float xstart, float xend, float *x, float *y); //function that initialises values for N+1 points with the function 1/1+25x^2
void tridiag(float *x, float *y, int N, float *e, float*f, float*g, float*r); //function that forms the tridiagonal matrix with e,f,g which is multiplied with f'' to give r
void Gauss(float **a, float *r, int N, int*er, float tol,float*e, float*g, float*f); //gauss elimination to solve the tridiagonal matrix
void Substitute(float **a, float *r, int N, float *d2x); // back substitution to find solutions for the entire matrix
void pivot(float **a, float *r, int N, int row); //partial pivoting to prevent highly sensitive calculations during back substitution
void Interpol(float*x, float*y, int N, float*d2x,float xu); //finds yu 

int main(int argc, char*argv[]){

int N = atoi(argv[1]); //argv input for number of intervals we divide [-1,1] into
float xu = atof(argv[2]);//argv input for the value of xu f

float*x = malloc((N + 1) * sizeof(float)); //dynamic memory allocation
float*y = malloc((N + 1) *sizeof(float)); //dynamic memory allocation
    
float **a = malloc((N-1) * sizeof(float *)); //dynamic memory allocation
for(int i = 0; i < N-1; i++)
  a[i] = malloc((N) * sizeof(float));
        
float *r = malloc((N+1) * sizeof(float)); //dynamic memory allocation
float *d2x = malloc((N+1) * sizeof(float)); //dynamic memory allocation
float *e= malloc((N+1) * sizeof(float)); //dynamic memory allocation
float*f=malloc((N+1) * sizeof(float)); //dynamic memory allocation
float*g=malloc((N+1) * sizeof(float)); //dynamic memory allocation

//initialising
for(int i=0; i<N+1; i++){
  r[i]=0;
  d2x[i]=0;
  e[i]=0;
  f[i]=0;
  g[i]=0;
  }

float xstart = -1.0; //given value of xstart
float xend = 1.0; //given value of xend

int*er = 0; // Error variable
float tol = 0.0000001; // Tolerance

initialise(N, xstart, xend, x, y);
tridiag(x,y, N,e, f, g, r);
Gauss(a, r, N, er, tol,e, g, f);
Substitute(a, r, N, d2x);
Interpol(x, y, N, d2x,xu);

}

void initialise(int N, float xstart, float xend, float *x, float *y){
    float commond = (xend - xstart)/N; //common difference to divide given interval into n equal parts
    for (int i = 0; i<= N; i++)
    {
        x[i] = xstart + (i * commond);
        y[i] = 1/(1 + 25 * (x[i]*x[i])); //use function 1/(1+25x^2) to get y values
    }
}

void tridiag(float *x, float *y, int N, float *e, float*f, float*g, float*r){
int i= 1;
//EQUATION WE ARE TRYING TO SOLVE :
// e*f''(x[i-1]) + f*f''(x[i]) + g*f''(x[i+1]) = r
//e,f,g,r are array elements corresponding to i
f[1] = 2 *(x[2]- x[0]);
g[1]= x[2]- x[1];
r[1]= 6/(x[2]- x[1])*(y[2]-y[1]);
r[1] = r[1] + 6/(x[1]-x[0])*(y[0]-y[1]);
   for(i= 2; i<=N-2 ; i++){
     e[i]= x[i]- x[i-1];
     f[i]= 2*(x[i+1] - x[i-1]);
     g[i]= x[i+1]- x[i];
     r[i]= 6/(x[i+1]- x[i])*(y[i+1]-y[i]);
     r[i]= r[i] + 6/(x[i] - x[i-1])*(y[i-1]-y[i]);
  }
e[N-1]= x[N-1]- x[N-2];
f[N-1]= 2*(x[i+1]- x[i-1]);
r[N-1]= 6/(x[N]- x[N-1])*(y[N]-y[N-1]);
r[N-1]= r[N-1] + 6/(x[N-1]- x[N-2]) * (y[N-2]- y[N-1]);
}

//gaussian elimination
void Gauss(float **a, float *r, int N, int *er, float tol,float*e, float*g, float*f){
int i,j;
for(i = 1; i< N; i++){ 
      for (j = 1; j< N; j++){
        a[i-1][j-1]=0;
        }
      }
      
for(i= 1; i< N; i++){
   j = i;
     a[i-1][j-1]= f[i];
     }
    
for( i = 2; i < N; i++){
  j = i-1;
  a[i-1][j-1] = e[i];
  }
  
for ( i = 1; i< N-1; i ++){
 j = i+1;
 a[i-1][j-1]= g[1];
 }
 
 for (i = 0; i< N-1; i++) {
        pivot(a, r, N, i);
        for (j = i+1; j < N-1; j++) {
            float factor = a[j][i] / a[i][i];
            for (int k = i; k < N-1; k++) {
                a[j][k] -= factor * a[i][k];
            }
            r[j+1] -= factor * r[i+1];
        }
        if (fabs(a[i][i]) < tol) {
            *er = -1; // Set error flag if division by zero may occur
            printf("no solutions");
            return; // Exit function if division by zero may occur
        }
    }
}
//back substitution that solves the tridiagonal 
void Substitute(float **a, float *r, int N, float *d2x) {
    for (int i = N - 2; i >= 0; i--) {
        float sum = 0;
        for (int j = i + 1; j < N-1; j++) {
            sum += a[i][j] * d2x[j+1];
        }
        d2x[i+1] = (r[i+1] - sum) / a[i][i];
    }
}

//partially pivoting
void pivot(float **a, float *r, int N, int row) {
    int p = row;
    for (int i = row+1; i < N-1; i++) {
        if (fabs(a[i][row]) > fabs(a[p][row])) {
            p = i;
        }
    }
    // Swap rows in 'a' and elements in 'b'
    float *temp = a[row];
    a[row] = a[p];
    a[p] = temp;
    float temp_r = r[row+1];
    r[row+1] = r[p+1];
    r[p+1] = temp_r;
}
    
void Interpol(float*x, float*y, int N, float*d2x,float xu){
int flag = 0;
float yu=0.0;
int i = 1;
do {
 if (xu >= x[i-1] && xu<= x[i]){
   float c1= d2x[i-1]/6/(x[i]-x[i-1]);
   float c2= d2x[i]/6/(x[i]-x[i-1]);
   float c3= y[i-1]/(x[i]- x[i-1]) - (d2x[i-1]* (x[i]- x[i-1])/6);
   float c4= y[i]/(x[i]-x[i-1]) - (d2x[i]*(x[i]-x[i-1])/6);
   float t1 = c1* pow((x[i]- xu),3);
   float t2 = c2* pow((xu- x[i-1]),3);
   float t3= c3* (x[i]- xu);
   float t4= c4*(xu - x[i-1]);
   yu = t1+t2+t3+t4;
   flag = 1;
   }
  else{
  i = i+1;}
  }while( i!= N ||flag!= 1);
printf("%f",yu);
if (flag == 0){printf("outside range");}
}

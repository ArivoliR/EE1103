/*
Program to find the roots of the given function in the range [0.5, 1.0]
Roll Numbers, Names : EE23B065, Rohita Datta Nalluri
                      EE23B008 Arivoli R
Inputs : 1 for Bisection method, 2 for False position method
output : Root or closest value to root such that error calculated is less than given epsilon = 10
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>


float func(float x){
return(-25 + 82*x - 90*pow(x,2) + 44*pow(x,3) - 8*pow(x,4) + 0.7*pow(x,5));
}


float bisect();
float falsepos();


int main(int argc, char**argv){
if (atoi(argv[1])==1)
{
bisect();
}
if(atoi(argv[1])==2)
{
falsepos();
}
}


//BISECTION METHOD
float bisect(){
float xl,xu,xr,etrial,egiven,temp;
int i=100; 
/*We're defining maximum number of iterations, if the Error value is still greater than given epsilon,
we want the loop to end after i iterations.*/
xl= 0.5; // Mentioned lower limit 
xu= 1.0; //Mentioned upper limit
egiven = 10; //Epsilon value, i.e, allowed error 
etrial= 100; 
temp=0;
while(etrial> egiven)
{
xr= (xu+xl)/2; 
//For bisection method, we check the value of the function at the midpoint of lower and upper limits.
etrial = fabsf((xr-temp)*100/xr);
        if( func(xl)*func(xr) < 0 )
        {
        xu = xr; //Root lies in lower half 
        }
        else 
                if (func(xr)*func(xu)<0)
                {
                xl=xr; // Root lies in upper half of the branch
                }
temp=xr;
i--;
      if (func(xr)==0  || i<0) 
      {
      printf("%f",xr);
      exit(0);
      }
}
printf("%f", xr);
}


//FALSE POSITION METHOD
float falsepos(){
float xl,xu,xr,etrial,egiven,temp;
int i=100;
xl= 0.5;
xu= 1.0;
egiven = 10;
etrial= 100;
temp=0;
while(etrial> egiven)
{
xr= xu - func(xu)*(xl-xu)/(func(xl)-func(xu)); 
/*For false position method, we first draw a line with the two points (lower limit, func(xl)) and (upper limit, func(xu))
and consider the x coordinate of the point where this line cuts the x axis as the new upper or lower limit */
etrial = fabsf((xr-temp)*100/xr);
        if( func(xl)*func(xr) < 0 )
        {
        xu = xr; //Root lies in lower half
        }
        else 
                if (func(xr)*func(xu)<0)
                {
                xl=xr; //Root lies in upper half
                }
temp=xr;
i--;
      if (func(xr)==0  || i<0)
      {
      printf("%f",xr);
      exit(0);
      }
}
printf("%f", xr);
}



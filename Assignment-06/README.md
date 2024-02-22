# Assgn 6:Fixed point iteration

It is possible to find the root of a polynomial f(x) - x = 0  by iterating x = f(x).  

Practice

Use simple fixed point iteration to find the roots of f(x) = exp(-x) -x. 
Define a convergence criterion (% change in the root) and exit the iteration.
Attempt Problem 6.1 from your text book
Assignment - The logistic map is a discrete time demographic model written as x[n+1] = r x[n] (1-x[n])

Iterate the equation for the parameter range r = [0,4] with x between 0 and 1.
Save the data as two columns (r,x), plot it (gnuplot is efficient) to generate the bifurcation plot
Submit:  

rollnum_logistic.c with command line inputs for Niter, rstep and error, and 
a jpg image of the final bifurcation plot

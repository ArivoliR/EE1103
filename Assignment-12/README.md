# Assgn12: Lorentzian versus Gaussian

Start with a baseline noisy series of length N with zero mean and standard deviation sigma_n (you can reuse the code from a previous assignment on the Box-Muller transform that converts uniform random distribution to a normal distribution)
Add to it a Lorentzian curve of the form f(x) = 1/(1+25 x^2), with x ranging from -2 to 2.
Fit the data to a Gaussian of the from g(x) = A * exp(-x^2/(2*sigma_g^2))
Plot the goodness of fit R^2 versus sigma_n. Label both axis of the plot.
inputs: N sigma_n 
outputs:  sigma_n A sigma_g R^2. (Although sigma_n is an input, having it also as an output helps you generate the plot easily)
submit: rollnum_noisyfits.c  and Rsquare.jpg
You can generate Rsquare.jpg in many ways. 

Write your own c-code to fit the data to a Gaussian and calculate R^2, and run the code in a shell script
Run your code with different inputs.  Use gnuplot to fit your data and manually read the values of the fit off the screen
Figure out how to read back the fit values from gnuplot into your c-code and print them out
(optional) Try this exercise with a Rayleigh function (which isn't even symmetric about x=0) instead of the Lorentzian

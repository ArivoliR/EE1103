# Assgn7: Time series analysis

Generate normal distributions for noise eps_T, eps_a, n
  Use a randn() or similar function or write a function to implement the Box - Muller transform 
Generate a time series of Lorentzians  s(t) separated by T with width proportional to a
 (a^2/((t-m*T)^2+a^2), where m = 1 to M
  Define a structure for each peak, with its location, amplitude and width as attributes.
Add "normal" noise to the location and the width of each Lorentzian
  a -> a + eps_a
  mT -> mT + eps_T
Add "normal" noise n(t) to the amplitude 
  s(t) + n(t)
Identify the locations of the peaks and estimate
  The average time <T> and the average width <a> and their standard deviations
  Compare it to the values of T and a that you used
  (optional) study the effect of eps_a, eps_T and n(t) on the difference between calculated and assumed values of T and a
  (optional) use the trapezoidal rule to calculate the area under each pulse and plot the area versus the width of all the pulses

Program: rollnum_timeseries.c
Inputs:  Take M, T, a and type (Gaussian or Lorentzian) as argv inputs to your program
Outputs: avg(T) avg(a) stdev(T) stdev(a)

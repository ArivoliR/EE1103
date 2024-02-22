# ENDSEM

The Hemachandra sequence is a series of integers starting with 0 and 1. Subsequent integers are the sum of the previous two integers

Write a C-program, rollnum_hem.c, to find integers in the Hemachandra sequence. 
    Assume that 0 and 1 are the 1st and 2nd numbers in the sequence. 
    Take as argv input M  
    Use recursion to return an integer from hem(int n), calling hem() from main()
Write a bash script, rullnum_hem.sh, that 
    Calls rollnum_hem twice in a loop with i and i+1 as the two integers
    Uses bc (basic calculator) to find the ratio of the i+1 and ith integers
    Redirects the output to rollnum_hem.txt. [rollnum_hem.txt should have three columns i, ith value, and ratio]
    create a gnuplot script file rollnum_hem.gp to plot data, label axis, etc
    call gnuplot (from within your bash script) to run rollnum_hem.gp and plot 
        ith value versus i on primary y-axis (left-side)
        ratio versus i on secondary y-axis (right-side)
        add as a label, on the plot, the asymptotic value of the ratio (for large values of i)
You now have all the tools you need to visualize your data. Write a new program rollnum_hemplot.c  with hem() and a new function hemplot() that will take as inputs x0, y0 and r0
    Define the center point (x0, y0) and the initial radius r0. [pick what you think will work]
    Define two variables, a and b, to represent the current and previous Hem numbers, respectively. Initialize a to 1 and b to 0.
    Loop through the desired number of iterations:
        Call hem(a)...if you need to
        Calculate the new radius r = r0 * a / b.
        Calculate the angle theta = (2 * pi * a) / b
        Update and calculate the new point (x, y) using the polar coordinates (r, theta):
            x = x0 + r * cos(theta)
            y = y0 + r * sin(theta)
        Update the values of a and b by swapping a and b and setting a = a + b.
    End the loop
    Plot y versus x...you should see the Fibonacci spiral.  You can adjust the starting point, number of iterations, and other parameters to customize the spiral to your liking.


Submissions:
rollnum_hem.c
rollnum_hem.sh
rollnum_hemgp.txt
rollnum_hem.jpg
rollnum_hemplot.c
rollnum_hemplot.jpg

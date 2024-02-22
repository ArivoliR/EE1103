set term png size 800,800
set output 'ee23b008_hemplot.jpg'
set title 'Fibonacci Spiral'
set xlabel 'X'
set ylabel 'Y'
plot 'fibonacci_spiral.txt' with points title 'Fibonacci Spiral'

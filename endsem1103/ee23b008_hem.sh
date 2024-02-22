#!/bin/bash

#Bash script to create and call gnuplot script file to plot 
#     1) ith value of sequence vs i
#     2) ratio vs i


# Compile the C program
gcc ee23b008_hem.c -o ee23b008_hem

# Number of iterations
N=10

# Output file
output_file="ee23b008_hem.txt"

# Create or overwrite the output file
>$output_file

# Loop to calculate the Hemachandra sequence and ratios
for i in $(seq 0 $((N - 1))); do
	./ee23b008_hem $i >tmp1.txt
	./ee23b008_hem $((i + 1)) >tmp2.txt
	ratio=$(bc <<<"scale=6; $(cat tmp2.txt) / $(cat tmp1.txt)")
	echo "$i $(cat tmp1.txt) $ratio" >>$output_file
done

# Create a gnuplot script file
gnuplot_script="ee23b008_hem.gp"
echo "set terminal jpeg size 1000,500" >$gnuplot_script
echo "set output 'ee23b008_hem.jpg'" >>$gnuplot_script
echo "set xlabel 'i'" >>$gnuplot_script
echo "set ylabel 'ith value'" >>$gnuplot_script
echo "set y2label 'Ratio'" >>$gnuplot_script
echo "set y2tics" >>$gnuplot_script
echo "set key right" >>$gnuplot_script
echo "plot '$output_file' using 1:2 with lines title 'ith value' lt 1 lc rgb 'blue', '' using 1:3 with lines title 'Ratio' lt 2 lc rgb 'red'" >>$gnuplot_script

# Calculate the asymptotic value of the ratio
asymptotic_value=$(bc <<<"scale=6; (1 + sqrt(5)) / 2")

# Add a label to the plot
echo "set label 'Asymptotic Value: $asymptotic_value' at graph 0.5,0.8 center" >> $gnuplot_script

# Run gnuplot with the script
gnuplot $gnuplot_script

# Clean up temporary files
rm tmp1.txt tmp2.txt ee23b008_hem

echo "Plot generated as ee23b008_hem.jpg"

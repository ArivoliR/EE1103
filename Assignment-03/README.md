# Assign3: Generating random bits

Use the functions in the math library to generate a sequence of N random bits in the output file randbits.txt

Write a main program which will use flags -n -s -t and -h. The program can be called with one or more flags
Take N as input on command line with the "-n" flag
Take the seed as input with the "-s" flag
Dynamically set the seed to the current time using if the program is called with the "-t" flag
Compare the Hamming distance between two input bit stream files  when using the -h flag. 
The two input files need not have the same number of random bits. The max Hamming distance would then be the shorter of the two bit sequences.
Try to write this code using pointer to elements in an array.
These programs are going to get more complicated, and carry more marks. Define and use functions, comment your code.
If you are working with someone, please make sure both roll numbers are in the header comments
You can use strcmp to check argv for the flags, but it is better to learn to use getopt
Download the NIST test suite, compile it, and run it against different random bit sequences. Report the results as Comments on Moodle along with your submission

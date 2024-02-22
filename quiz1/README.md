# Quiz 1

Submit a c-program as rollnum_minHam.c that

Is properly commented, both header and within the code
Take as argv input four integers: N Nseed M Mseed [Expect to have e.g. M=100 and N=10000]
Check  that M < N, and M and N are integers, else print an error and stop. 
Allocate memory for N and M integers, refer to them as nbits and mbits
Use Nseed and Mseed to create N and M random binary bits, respectively, store as nbits and mbits.
Write these bits, separated by a space, into Nfile.dat and Mfile.dat
Use pointers to address the locations of the allocated memory. 
Start with the first M bits of nbits, and find the Hamming distance between mbits and M bits of nbits
Increment the pointers appropriately, and find the minimum Hamming distance of mbits within nbits.
Only print two integers as your output: 
location_of_minimum minimum_Hamming_distance
if you have multiple locations with the same minimum Hamming distance, print the first location
Through this quiz, you are demonstrating the following learning outcomes

Good coding practices, with proper comments (header and in the body of the code)
The use of command line inputs argc, argv and checking for errors in input
Generating and using random integers
Writing to a file
Use of pointers

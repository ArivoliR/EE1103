/*
Name: Arivoli Ramamoorthy
Roll number: ee23b008
Date: 14/11/2023
Version: 1.1
Description: 
This program calculates the nth number in the Hemachandra sequence using recursion. 
It takes an integer M as a command-line argument and prints the Mth number of the sequence.
Uses recursion by calling hem() from main()
Inputs: M
Output: Value of M in sequence
*/

#include <stdio.h>
#include <stdlib.h>

int hem(int n) {  
  if (n == 0)
    return 0;
  else if (n == 1)
    return 1;
  else
    return hem(n - 1) + hem(n - 2);       //recursive function to calculate nth hemachandra sequence term
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s M\n", argv[0]);
    return 1;
  }

  int M = atoi(argv[1]);  //taking input from command line

  printf("%d\n", hem(M-1)); 

  return 0;
}

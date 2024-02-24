// EE23B008
// 25th August 2023
// Version 1.0
// The purpose of the code is to calculate the hamming distance between two different random bitsStreams.
// Input: Executible name, -n number of random bits, -h inputfile1 inputfile2
// Output: Hamming distance 


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define MAX_BITS 1000000

// Calculate Hamming distance between two bit streams
int calculateHammingDistance(const char *bitStream1, const char *bitStream2) {
    int len1 = strlen(bitStream1);
    int len2 = strlen(bitStream2);
    int minLen = len1 < len2 ? len1 : len2;

    int hammingDistance = 0;
    for (int i = 0; i < minLen; i++) {
        if (bitStream1[i] != bitStream2[i]) {
            hammingDistance++;
        }
    }

    return hammingDistance;
}

int main(int argc, char *argv[]) {
    int N = -1;                
    unsigned int seed = 0;     
    int useTimeSeed = 0;       // Flag for taking seed as current time
    int compareHamming = 0;    // Flag for comparing Hamming distance of the streams

    char input1[MAX_BITS]; // input file names
    char input2[MAX_BITS]; 

    int opt;
    while ((opt = getopt(argc, argv, "n:s:th")) != -1) {
        switch (opt) {
            case 'n':
                N = atoi(optarg); // Get number of random bits
                break;
            case 's':
                seed = atoi(optarg); // Get seed value from command line
                break;
            case 't':
                useTimeSeed = 1; 
                break;
            case 'h':
                compareHamming = 1; // Enable Hamming distance comparison
                if (optind < argc) {
                    strcpy(input1, argv[optind]); // Get first input file name from command line
                    optind++;
                }
                if (optind < argc) {
                    strcpy(input2, argv[optind]); // Second input file name
                }
                break;
            default:
                fprintf(stderr, "Usage: %s [-n N] [-s seed] [-t] [-h file1 file2]\n", argv[0]);
                return 1;
        }
    }

    if (N <= 0) {
        fprintf(stderr, "Invalid or missing value for -n flag.\n");
        return 1;
    }

    if (useTimeSeed) {
        seed = (unsigned int)time(NULL); // Set seed to current time if -t flag is provided
    }

    int randomBits[N];  // Array to store generated random bits

    srand(seed);
    FILE * fp = fopen("randbits.txt" , "w");
 		for(int i=0;i<N;i++){
 		fprintf(fp,"%d",rand()%2);
    }

    if (compareHamming) {
        FILE *inputFile1 = fopen(input1, "r");
        FILE *inputFile2 = fopen(input2, "r");

        if (!inputFile1 || !inputFile2) {
            perror("Error opening input files");
            return 1;
        }

        char bitStream1[MAX_BITS];
        char bitStream2[MAX_BITS];

        fgets(bitStream1, sizeof(bitStream1), inputFile1);
        fgets(bitStream2, sizeof(bitStream2), inputFile2);

        // Calculate Hamming distance between bit streams
        int hammingDistance = calculateHammingDistance(bitStream1, bitStream2);
        printf("Hamming Distance: %d\n", hammingDistance);

        fclose(inputFile1);
        fclose(inputFile2);
    }

    return 0;
}

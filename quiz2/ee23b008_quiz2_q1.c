/*
Name : ARIVOLI RAMAMOORTHY
Roll Number : EE23B008
Description: Program uses Quick Union-Find Method.
Input : a file with the first line containing the number of cities, the number of inputs and then a series of pairs of numbers(representing cities) that are checked if wheter to be connected or not.
Output : a file called ee23b008_quiz2_q1_output with 1 printed everytime a road is built and 0 if a road is not built, and the time taken for the execution of the program.
Sources: https://geeksforgeeks.org for the C programming syntaxes, chatgpt and https://algs4.cs.princeton.edu/15uf/ for the Union-Find algorithms, and a lot of peer group discussions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Function to initialize the parent array with each element as its own parent
void initialize(int n, int *parent) {
  for (int i = 0; i < n; i++)
    parent[i] = i;
}

// Function to find the root of a set to which element x belongs
int find(int x, int *parent) {
  while (x != parent[x])
    x = parent[x];
  return x;
}

// Function to connect two elements, x and y, into the same set and return 1 if a road is built, 0 otherwise
int connect(int x, int y, int *parent) {
  int rootX = find(x, parent);
  int rootY = find(y, parent);
  if (rootX != rootY) {
    parent[rootX] = rootY;
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <input_file>\n", argv[0]);
    return 1;
  }

  FILE *input = fopen(argv[1], "r");
  if (!input) {
    printf("Error opening input file.\n");
    return 1;
  }

  int n, m;
  fscanf(input, "%d %d", &n, &m);

  int *parent = malloc(n * sizeof(int));
  initialize(n, parent);

  FILE *output = fopen("ee23b008_quiz2_q1_output.txt", "w");
  if (!output) {
    printf("Error opening output file.\n");
    return 1;
  }

  struct timeval start, end;
  gettimeofday(&start, NULL);

  for (int i = 0, x, y; i < m; i++) {
    fscanf(input, "%d %d", &x, &y);
    int roadBuilt = connect(x, y, parent);
    fprintf(output, "%d", roadBuilt);
  }

  gettimeofday(&end, NULL);
  double executionTime = (end.tv_sec - start.tv_sec) * 1000.0 +
                         (end.tv_usec - start.tv_usec) / 1000.0;

  fprintf(output, "\n%.0f ms\n", executionTime);

  free(parent);
  fclose(input);
  fclose(output);

  return 0;
}

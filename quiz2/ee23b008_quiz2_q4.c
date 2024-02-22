/*
Name : ARIVOLI RAMAMOORTHY
Roll Number : EE23B008
Description: Program uses Weighted Quick Union-Find without path compression.
Input : a file with the first line containing the number of cities, the number of inputs and then a series of pairs of numbers(representing cities) that are checked if wheter to be connected or not.
Output : a file called ee23b008_quiz2_q1_output with 1 printed everytime a road is built and 0 if a road is not built, and the time taken for the execution of the program.
Sources: https://geeksforgeeks.org for the C programming syntaxes, chatgpt and https://algs4.cs.princeton.edu/15uf/ for the Union-Find algorithms, and a lot of peer group discussions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Structure to represent a disjoint set
typedef struct {
    int *parent;
    int *weight;
} DisjointSet;

// Function to initialize the sets
void initialize(int n, DisjointSet* set) {
    set->parent = (int *)malloc(n * sizeof(int));
    set->weight = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        set->parent[i] = i;
        set->weight[i] = 1;
    }
}

// Function to find the root of a set
int find(int x, DisjointSet* set) {
    while (x != set->parent[x]) {
        x = set->parent[x];
    }
    return x;
}

// Function to connect two realms and print 1 if a road is built, 0 otherwise
int connect(int x, int y, DisjointSet* set) {
    int rootX = find(x, set);
    int rootY = find(y, set);

    if (rootX != rootY) {
        if (set->weight[rootX] < set->weight[rootY]) {
            set->parent[rootX] = rootY;
            set->weight[rootY] += set->weight[rootX];
        } else {
            set->parent[rootY] = rootX;
            set->weight[rootX] += set->weight[rootY];
        }
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    char *input_file_name = argv[1];
    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    int n, m;
    fscanf(input_file, "%d %d", &n, &m);

    DisjointSet set;
    initialize(n, &set);

    FILE *output_file = fopen("ee23b008_quiz2_q4_output.txt", "w");
    if (output_file == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < m; i++) {
        int x, y;
        fscanf(input_file, "%d %d", &x, &y);
        int road_built = connect(x, y, &set);
        fprintf(output_file, "%d", road_built);
    }

    gettimeofday(&end, NULL);
    double execution_time = (double)(end.tv_sec - start.tv_sec) * 1000.0 +
                           (double)(end.tv_usec - start.tv_usec) / 1000.0;

    fprintf(output_file, "\n%.0f ms\n", execution_time);

    free(set.parent);
    free(set.weight);
    fclose(input_file);
    fclose(output_file);

    return 0;
}

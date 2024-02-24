#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

float randn() {
    time_t t = clock();
    float s = ((float)(t) * 1000000 / CLOCKS_PER_SEC);
    srand(s);

    float x = (float)(rand()) / RAND_MAX;
    float y = (float)(rand()) / RAND_MAX;
    float z = sqrt(-2.0 * log(x)) * cos(2 * M_PI * y);
    return z;
}

float f(float x) {
    return 1 / (1 + 25 * pow(x, 2));
}

int main(int argc, char** argv) {
    float sig_n = atof(argv[2]);
    float n = atof(argv[1]);
    float t = 0;

    FILE* gp_file = fopen("gnuinst.gp", "w");
    fprintf(gp_file, "mean(x) = m\nfit mean(x) 'plot.txt' using 1:2 via m\nSST = FIT_WSSR / (FIT_NDF + 1)\n");
    fprintf(gp_file, "f(x) = a * exp(-(x**2) / (2 * (g**2)))\nfit f(x) 'plot.txt' using 1:2 via a, g\nSSE = FIT_WSSR / (FIT_NDF)\n");
    fprintf(gp_file, "SSR = SST - SSE\nR2 = SSR / SST\nset print \"ee23b008_graph.txt\"\nprint R2\nprint a\nprint g\nset print");
    fclose(gp_file);

    FILE* plot_file = fopen("plot.txt", "w");
    for (t = -2; t < 2; t += (float)(4 / n)) {
        fprintf(plot_file, "%f %f\n", t, f(t) + sig_n * randn());
    }
    fclose(plot_file);

    FILE* log_file = fopen("dummy.log", "w");
    system("gnuplot gnuinst.gp > /dev/null 2>&1");
    fclose(log_file);

    float R2;
    float a;
    float g;
    FILE* output_file = fopen("ee23b008_graph.txt", "r");
    fscanf(output_file, "%f", &R2);
    fscanf(output_file, "%f", &a);
    fscanf(output_file, "%f", &g);
    fclose(output_file);

    printf("%f %f %f %f\n", sig_n, a, g, R2);
}

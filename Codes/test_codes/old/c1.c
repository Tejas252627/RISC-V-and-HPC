#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>

#define NUM_ENTRIES 1000

double get_time_us() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

void fmaddsub(double *a, double *b, double *c, double *result, int n) {
    for (int i = 0; i < n; i++) {
        result[i] = a[i] * b[i] + ((i % 2 == 0) ? c[i] : -c[i]);
    }
}

int main() {
    double veca[NUM_ENTRIES];
    double vecb[NUM_ENTRIES];
    double vecc[NUM_ENTRIES];
    double result[NUM_ENTRIES];

    // Initialize vectors
    for (int i = 0; i < NUM_ENTRIES; i++) {
        veca[i] = 6.0;
        vecb[i] = 2.0;
        vecc[i] = 7.0;
    }

    // Perform the operation
    uint64_t begin = get_time_us();
    fmaddsub(veca, vecb, vecc, result, NUM_ENTRIES);
    uint64_t elapsed = get_time_us() - begin;

    // Display the result
    printf("Result for the first %d entries:\n", NUM_ENTRIES);
    for (int i = 0; i < NUM_ENTRIES; i++) {
        printf("%lf ", result[i]);
    }
    printf("\n\nTime taken for normal c operation: %lu us\n", elapsed);

    return 0;
}


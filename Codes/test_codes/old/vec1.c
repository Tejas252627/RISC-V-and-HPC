#include <immintrin.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>

#define n 1000
uint64_t get_time_us() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000) + tv.tv_usec;
}
int main() {
    // Initialize vectors with constant values
    __m256d veca = _mm256_set1_pd(6.0);
    __m256d vecb = _mm256_set1_pd(2.0);
    __m256d vecc = _mm256_set1_pd(7.0);

    // Initialize result array to store 1000 result values
    double result[n];

 	uint64_t begin = get_time_us();
    // Perform the operation for 1000 entries
 	srand(time(NULL));
    for (int i = 0; i < n; i += 4) {
        __m256d result_vec = _mm256_fmaddsub_pd(veca, vecb, vecc);
        _mm256_storeu_pd(&result[i], result_vec);
    }

     uint64_t elapsed = get_time_us() - begin;

    // Display a few elements of the result array
    printf("Results for first few elements:\n");
    for (int i = 0; i < 10; i++) {
        printf("%lf ", result[i]);
    }
    printf("\n");
     printf("\nTime taken for vector addition : %lu us\n", elapsed);

    return 0;
}


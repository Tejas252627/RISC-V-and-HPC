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
  
  __m256d veca = _mm256_setr_pd(6.0, 6.0, 6.0, 6.0);

  __m256d vecb = _mm256_setr_pd(2.0, 2.0, 2.0, 2.0);
  
  __m256d vecc = _mm256_setr_pd(7.0, 7.0, 7.0, 7.0);


  /* Alternately subtract and add the third vector
     from the product of the first and second vectors */

	uint64_t begin = get_time_us();
  __m256d result = _mm256_fmaddsub_pd(veca, vecb, vecc);
   uint64_t elapsed = get_time_us() - begin;
  
  /* Display the elements of the result vector */
  double* res = (double*)&result;
  printf("%lf %lf %lf %lf\n", res[0], res[1], res[2], res[3]);
  printf("\nTime taken for vector addition : %lu us\n", elapsed);
  
  return 0;
}

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#define n 1000
uint64_t get_time_us() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

int main() {
    double a[n] = {0};
    double b[n] = {0};
    double c[n] = {0};

     srand(time(NULL));

        for(int i=0; i < n; i++)
        {
                a[i] = 6.0; 					//rand() % 1000;
                b[i] = 2.0;                                      //rand() % 1000;
		c[i] = 7.0;						//rand() % 1000;
        }
    /* Alternately subtract and add the third vector
       from the product of the first and second vectors */
    uint64_t begin = get_time_us();
    double result[n];
    for (int i = 0; i < n; i++) {
        result[i] = a[i] * b[i] + (i % 2 == 0 ? c[i] : -c[i]);
    }
    uint64_t elapsed = get_time_us() - begin;

     for (int i = 0; i < 10; i++) {
    /* Display the elements of the result vector */
    printf("%lf %lf %lf %lf\n", result[i]);
     }
    printf("\nTime taken for normal C addition : %lu us\n", elapsed);

    return 0;
}


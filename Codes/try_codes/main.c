#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define MAXELEM		1000

uint64_t get_time_us() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000) + tv.tv_usec;
}


extern void vvaddint32(size_t n, const int *x, const int *y, int *z);

int main()
{
	int x[MAXELEM] = {0};
	int y[MAXELEM] = {0};
	int z[MAXELEM] = {0};

	srand(time(NULL));

	for(int i=0; i < MAXELEM; i++)
	{
		x[i] = rand() % 1000;
		y[i] = rand() % 1000;
	}

	uint64_t begin = get_time_us();
	vvaddint32(MAXELEM, x, y, z);
	uint64_t elapsed = get_time_us() - begin;

	printf("\nTime taken for vector addition : %lu us\n", elapsed);

	

}

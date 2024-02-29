#include <stdio.h>

// Define vector length
#define VL 4

// Function to add two arrays using RVV
void vector_add(int *a, int *b, int *result, size_t size) {
    size_t i;

    // Loop with vectorization
    for (i = 0; i < size; i += VL) {
        __asm__ __volatile__ (
            "vle32.v v0, (%0)\n"   // Load vector from a
            "vle32.v v1, (%1)\n"   // Load vector from b
            "vadd.vv v2, v0, v1\n"  // Vector addition
            "vse32.v v2, (%2)\n"    // Store result vector
            : "+r" (a), "+r" (b), "+r" (result)
            :
            : "v0", "v1", "v2"
        );
    }
}

int main() {
    // Test arrays
    int a[] = {1, 2, 3, 4};
    int b[] = {5, 6, 7, 8};
    int result[VL];

    // Calculate array size
    size_t size = sizeof(a) / sizeof(a[0]);

    // Perform vector addition
    vector_add(a, b, result, size);

    // Print result
    printf("Result: ");
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
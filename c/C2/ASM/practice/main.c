#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <emmintrin.h>

void
print_matrix(const float* matrix, const char* name) {
    printf("%s\n", name);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%f ", matrix[i+j]);
        }
        printf("\n");
    }
}

uint64_t
msecs_since_epoch() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return (uint64_t)(tv.tv_sec) * 1000 +
           (uint64_t)(tv.tv_usec) / 1000;
}

void
init_matrices(float* A, float* B, float* r) {
    for(int i = 0; i < 16; i++) {
        A[i] = i+1;
        B[i] = i+1;
        r[i] = 0.0;
    }
}

void
timer(void (*func)(const float*, const float*, float*), const float* A, const float* B, float* r, const char* name) {
    static const int runs = 10;
    static const int iter = 5000000;
    time_t total_time = 0;

    for(int i = 0; i < runs; i++) {
        time_t s0 = msecs_since_epoch();
        for(int j = 0; j < iter; j++) {
            func(A, B, r);
        }
        time_t s1 = msecs_since_epoch();
        total_time += s1 - s0;
    }
    printf("%i iterations of %s: %lu\n", iter, name, total_time / runs);
}

void
multiply_naive(const float* A, const float* B, float* result) {
    for (int i = 0; i < 16; i += 4) {
        for (int j = 0; j < 4; j++) {
            result[i+j] = B[i] * A[j] +
                          B[i+1] * A[j+4] +
                          B[i+2] * A[j+8] +
                          B[i+3] * A[j+12];
        }
    }
}

void
multiply_sse(const float* A, const float* B, float* result) {
    const float* a = A;
    const float* b = B;
          float* r = result;

    __m128 a_line, b_line, r_line;
    for(int i = 0; i < 16; i += 4) {
        memset(&r_line, '\0', sizeof(__m128));
        for(int j = 0; j < 4; j++) {
            a_line = _mm_load_ps(&a[j*4]);
            b_line = _mm_set1_ps(b[i+j]);
            r_line = _mm_add_ps(
                _mm_mul_ps(a_line, b_line),
                r_line
            );
        }
        _mm_store_ps(&r[i], r_line);
    }
}

void
multiply_sse_asm(const float* A, const float* B, float* result) {
    /* Registers map
     * rcx:  i-loop counter
     * rax:  j-loop counter
     * r8:   A-matrix current row address
     * r9:   B-matrix current scalar address
     * xmm0: Accumulator line
     * xmm1: Result line
     */

    asm __volatile__ (
    "   mov rcx, 4;"                     // Set i-loop counter to 4
    " ILoop:"
    "     mov   rax, 4;"                 // Set j-loop counter to 4
    "     pxor  xmm1, xmm1;"             // Set result line to 0
    "     mov   r9, %0;"                 // Copy A-addr to r9
    "   JLoop:"
    // Load B[i+j] to XMM0 (scalar)
    "       movss   xmm0, [%1];"         // Move B to xmm0
    "       lea     %1,   [%1+4];"       // B addr + 1
    "       shufps  xmm0, xmm0, 0;"      // Broadcast B to all xmm0 parts
    // Multiply XMM0 by A[4*j], write to XMM0
    "       mulps   xmm0, [r9];"
    "       lea     r9,   [r9+16];"      // A addr + 4 (line)
    // Add XMM0 to XMM1, write to XMM1
    "       addps   xmm1, xmm0;"

    "       dec     rax;"                // Decrement j-counter
    "       jnz     JLoop;"              // Jump if j-counter != 0
    // Save XMM3 to result
    "     movaps [%2], xmm1;"            // Write result vector to current result line
    "     lea %2, [%2+16];"              // result addr + 4 (line)
    "     dec rcx;"                      // Decrement i-counter
    "     jnz ILoop;"                    // Jump if i-counter != 0
    :
    : "r" (A), "r" (B), "r" (result)
    : "rcx", "rax", "r9","xmm0", "xmm1"
    );
}

int main() {
    float A[16]      __attribute__ ((aligned (16)));
    float B[16]      __attribute__ ((aligned (16)));
    float result[16] __attribute__ ((aligned (16)));

    init_matrices(A, B, result);
    //print_matrix(A, "Matrix A");
    //printf("\n\n");
    //print_matrix(B, "Matrix B");
    //printf("\n\n");

    //timer(multiply_naive, A, B, result, "Naive multiplication");
    //print_matrix(result, "Naive multiplication");
    //printf("\n\n");

    //init_matrices(A, B, result);
    timer(multiply_sse, A, B, result, "SSE multiplication");
    //print_matrix(result, "SSE multiplication");
    //printf("\n\n");

    //init_matrices(A, B, result);
    timer(multiply_sse_asm, A, B, result, "SSE multiplication, ASM");
    //print_matrix(result, "SSE multiplication, ASM");
    //printf("\n\n");

    return 0;
}

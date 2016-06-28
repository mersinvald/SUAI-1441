#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <emmintrin.h>
#define M_SIZE 4

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
timer(void (*func)(const float*, const float*, float*), const float* A, const float* B, float* r, const char* name) {
    static const int iter = 1000000;
    time_t s0 = msecs_since_epoch();
    for(int i = 0; i < iter; i++) {
        func(A, B, r);
    }
    time_t s1 = msecs_since_epoch();
    printf("%i iterations of %s: %lu\n", iter, name, s1 - s0);
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
    asm __volatile__ (
    "   mov r8,  %0;"                     // load addresses of input and output arrays
    "   mov r9,  %1;"
    "   mov r10, %2;"
    "   xor rcx, rcx;"                    // set i-loop counter to 0
    " ILoop:"                             // push i-loop counter
    "     xor   rdx, rdx;"                // set j-loop counter to 0
    "     pxor  xmm1, xmm1;"              // set result line to 0
    "     mov   rsi, r8;"                 // copy A addr to rsi
    "     lea   rdi, [r9 + 4 * rcx];"     // copy B addr to rdi
    "   JLoop:"
    // Load B[i+j] to XMM0 (scalar)
    "       movss   xmm0, [rdi];"
    "       add     rdi,  4;"             // B addr + 1 (i+j)
    "       shufps  xmm0, xmm0, 0;"
    // Multiply XMM0 by A[4*j], write to XMM0
    "       mulps   xmm0,  [rsi];"
    "       add     rsi,   16;"           // A addr + 16 (j*4)
    // Add XMM0 to XMM1, write to XMM1
    "       addps   xmm1, xmm0;"

    "       inc    rdx;"                  // increment j-loop counter
    "       cmp    rdx, 4;"               // jump to JLoop if rcx < 4
    "       jl     JLoop;"
    // Save XMM3 to result
    "     movaps [r10 + 4*rcx], xmm1;"
    "     add rcx, 4;"                    // increment j-loop counter by 4
    "     cmp rcx, 16;"                   // jump to ILoop if rcx < 0
    "     jl ILoop;"
    :
    : "m" (A), "m" (B), "m" (result)
    : "r8", "r9", "r10", "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "xmm0", "xmm1"
    );
}

int main() {
    float A[16]      __attribute__ ((aligned (16)));
    float B[16]      __attribute__ ((aligned (16)));
    float result[16] __attribute__ ((aligned (16)));

    for(int i = 0; i < 16; i++) {
        A[i] = i+1;
        B[i] = i+1;
        result[i] = 0.0;
    }

    timer(multiply_naive, A, B, result, "Naive multiplication");
    print_matrix(result, "Naive multiplication");
    printf("\n\n");

    for(int i = 0; i < 16; i++) {
        A[i] = i+1;
        B[i] = i+1;
        result[i] = 0.0;
    }

    timer(multiply_sse, A, B, result, "SSE multiplication");
    print_matrix(result, "SSE multiplication");
    printf("\n\n");

    for(int i = 0; i < 16; i++) {
        A[i] = i+1;
        B[i] = i+1;
        result[i] = 0.0;
    }

    timer(multiply_sse_asm, A, B, result, "SSE multiplication, ASM");
    //multiply_sse_asm(A, B, result);
    print_matrix(result, "SSE multiplication, ASM");
    printf("\n\n");

    return 0;
}

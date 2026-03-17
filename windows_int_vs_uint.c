#include <windows.h>
//
#include <profileapi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN (1 << 15)

#define PERFORMANCE_LOOP(T, arr)                                                          \
    {                                                                                     \
        printf(#T "\n");                                                                  \
                                                                                          \
        T* rand_arr = (T*)(_aligned_malloc(LEN * sizeof(*rand_arr), 64));                 \
        double* seconds_arr = (double*)(_aligned_malloc(LEN * sizeof(*seconds_arr), 64)); \
                                                                                          \
        for (T i = 0; i < LEN; ++i) {                                                     \
            rand_arr[i] = (T)(rand());                                                    \
        }                                                                                 \
                                                                                          \
        T one = (T)(1);                                                                   \
        LARGE_INTEGER f, t0, tf;                                                          \
        QueryPerformanceFrequency(&f);                                                    \
        for (T _ = 0; _ < LEN; ++_) {                                                     \
            QueryPerformanceCounter(&t0);                                                 \
            for (T i = 0; i < LEN; ++i) {                                                 \
                T r = rand_arr[i];                                                        \
                T lhs = r + i;                                                            \
                T rhs = r >> one;                                                         \
                T sub = lhs - rhs;                                                        \
                arr[i] = sub;                                                             \
            }                                                                             \
            for (T i = 1; i < LEN; ++i) {                                                 \
                T lhsl = arr[i - one];                                                    \
                T lhsr = arr[i];                                                          \
                T lhs = lhsl * lhsr;                                                      \
                T div = lhs / i;                                                          \
                arr[i] = div;                                                             \
            }                                                                             \
            QueryPerformanceCounter(&tf);                                                 \
                                                                                          \
            double s = (double)(tf.QuadPart - t0.QuadPart) / f.QuadPart;                  \
            seconds_arr[_] = s;                                                           \
        }                                                                                 \
        for (T _ = 0; _ < LEN; ++_) {                                                     \
            double s = seconds_arr[_];                                                    \
            printf("%f\n", 1000000.0 * s);                                                \
        }                                                                                 \
        _aligned_free(rand_arr);                                                          \
        _aligned_free(seconds_arr);                                                       \
    }

#define PERFORMANCE_LOOP_NODIV(T, arr)                                                    \
    {                                                                                     \
        printf(#T "\n");                                                                  \
                                                                                          \
        T* rand_arr = (T*)(_aligned_malloc(LEN * sizeof(*rand_arr), 64));                 \
        double* seconds_arr = (double*)(_aligned_malloc(LEN * sizeof(*seconds_arr), 64)); \
                                                                                          \
        for (T i = 0; i < LEN; ++i) {                                                     \
            rand_arr[i] = (T)(rand());                                                    \
        }                                                                                 \
                                                                                          \
        T one = (T)(1);                                                                   \
        LARGE_INTEGER f, t0, tf;                                                          \
        QueryPerformanceFrequency(&f);                                                    \
        for (T _ = 0; _ < LEN; ++_) {                                                     \
            QueryPerformanceCounter(&t0);                                                 \
            for (T i = 0; i < LEN; ++i) {                                                 \
                T r = rand_arr[i];                                                        \
                T lhs = r + i;                                                            \
                T rhs = r >> one;                                                         \
                T sub = lhs - rhs;                                                        \
                arr[i] = sub;                                                             \
            }                                                                             \
            for (T i = 1; i < LEN; ++i) {                                                 \
                T lhsl = arr[i - one];                                                    \
                T lhsr = arr[i];                                                          \
                T lhs = lhsl * lhsr;                                                      \
                arr[i] = lhs;                                                             \
            }                                                                             \
            QueryPerformanceCounter(&tf);                                                 \
                                                                                          \
            double s = (double)(tf.QuadPart - t0.QuadPart) / f.QuadPart;                  \
            seconds_arr[_] = s;                                                           \
        }                                                                                 \
        for (T _ = 0; _ < LEN; ++_) {                                                     \
            double s = seconds_arr[_];                                                    \
            printf("%f\n", 1000000.0 * s);                                                \
        }                                                                                 \
        _aligned_free(rand_arr);                                                          \
        _aligned_free(seconds_arr);                                                       \
    }

#define PERFORMANCE_LOOP_NODIVMULT(T, arr)                                                \
    {                                                                                     \
        printf(#T "\n");                                                                  \
                                                                                          \
        T* rand_arr = (T*)(_aligned_malloc(LEN * sizeof(*rand_arr), 64));                 \
        double* seconds_arr = (double*)(_aligned_malloc(LEN * sizeof(*seconds_arr), 64)); \
                                                                                          \
        for (T i = 0; i < LEN; ++i) {                                                     \
            rand_arr[i] = (T)(rand());                                                    \
        }                                                                                 \
                                                                                          \
        T one = (T)(1);                                                                   \
        LARGE_INTEGER f, t0, tf;                                                          \
        QueryPerformanceFrequency(&f);                                                    \
        for (T _ = 0; _ < LEN; ++_) {                                                     \
            QueryPerformanceCounter(&t0);                                                 \
            for (T i = 0; i < LEN; ++i) {                                                 \
                T r = rand_arr[i];                                                        \
                T lhs = r + i;                                                            \
                T rhs = r >> one;                                                         \
                T sub = lhs - rhs;                                                        \
                arr[i] = sub;                                                             \
            }                                                                             \
            QueryPerformanceCounter(&tf);                                                 \
                                                                                          \
            double s = (double)(tf.QuadPart - t0.QuadPart) / f.QuadPart;                  \
            seconds_arr[_] = s;                                                           \
        }                                                                                 \
        for (T _ = 0; _ < LEN; ++_) {                                                     \
            double s = seconds_arr[_];                                                    \
            printf("%f\n", 1000000.0 * s);                                                \
        }                                                                                 \
        _aligned_free(rand_arr);                                                          \
        _aligned_free(seconds_arr);                                                       \
    }

int main() {
    // cl /O2 /c /FAs prepro.c
    // movdqu
    // Ice Lake (https://www.agner.org/optimize/instruction_tables.pdf)
    // https://www.intel.la/content/www/xl/es/products/sku/232160/intel-core-i71355u-processor-12m-cache-up-to-5-00-ghz/specifications.html
    srand(time(NULL));

    int32_t* s_arr = (int32_t*)(_aligned_malloc(LEN * sizeof(*s_arr), 64));
    uint32_t* u_arr = (uint32_t*)(_aligned_malloc(LEN * sizeof(*u_arr), 64));

#if defined(BASE)
    PERFORMANCE_LOOP(int32_t, s_arr);
    PERFORMANCE_LOOP(uint32_t, u_arr);
#elif defined(NODIV)
    PERFORMANCE_LOOP_NODIV(int32_t, s_arr);
    PERFORMANCE_LOOP_NODIV(uint32_t, u_arr);
#elif defined(NODIVMULT)
    PERFORMANCE_LOOP_NODIVMULT(int32_t, s_arr);
    PERFORMANCE_LOOP_NODIVMULT(uint32_t, u_arr);
#else
#error ERROR
#endif

    return 0;
}

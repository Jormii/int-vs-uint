#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN (1 << 15)

#define PERFORMANCE_LOOP(T, arr)                                                        \
    {                                                                                   \
        printf(#T "\n");                                                                \
                                                                                        \
        T* rand_arr = (T*)(aligned_alloc(64, LEN * sizeof(*rand_arr)));                 \
        clock_t* clocks_arr = (clock_t*)(aligned_alloc(64, LEN * sizeof(*clocks_arr))); \
                                                                                        \
        for (T i = 0; i < LEN; ++i) {                                                   \
            rand_arr[i] = (T)(rand());                                                  \
        }                                                                               \
                                                                                        \
        T one = (T)(1);                                                                 \
        for (T _ = 0; _ < LEN; ++_) {                                                   \
            clock_t t0 = clock();                                                       \
            for (T i = 0; i < LEN; ++i) {                                               \
                T r = rand_arr[i];                                                      \
                T lhs = r + i;                                                          \
                T rhs = r >> one;                                                       \
                T sub = lhs - rhs;                                                      \
                arr[i] = sub;                                                           \
            }                                                                           \
            for (T i = 1; i < LEN; ++i) {                                               \
                T lhsl = arr[i - one];                                                  \
                T lhsr = arr[i];                                                        \
                T lhs = lhsl * lhsr;                                                    \
                T div = lhs / i;                                                        \
                arr[i] = div;                                                           \
            }                                                                           \
            clock_t tf = clock();                                                       \
                                                                                        \
            clocks_arr[_] = tf - t0;                                                    \
        }                                                                               \
        for (T _ = 0; _ < LEN; ++_) {                                                   \
            clock_t elapsed = clocks_arr[_];                                            \
            printf("%ld\n", elapsed);                                                   \
        }                                                                               \
        free(rand_arr);                                                                 \
        free(clocks_arr);                                                               \
    }

#define PERFORMANCE_LOOP_NODIV(T, arr)                                                  \
    {                                                                                   \
        printf(#T "\n");                                                                \
                                                                                        \
        T* rand_arr = (T*)(aligned_alloc(64, LEN * sizeof(*rand_arr)));                 \
        clock_t* clocks_arr = (clock_t*)(aligned_alloc(64, LEN * sizeof(*clocks_arr))); \
                                                                                        \
        for (T i = 0; i < LEN; ++i) {                                                   \
            rand_arr[i] = (T)(rand());                                                  \
        }                                                                               \
                                                                                        \
        T one = (T)(1);                                                                 \
        for (T _ = 0; _ < LEN; ++_) {                                                   \
            clock_t t0 = clock();                                                       \
            for (T i = 0; i < LEN; ++i) {                                               \
                T r = rand_arr[i];                                                      \
                T lhs = r + i;                                                          \
                T rhs = r >> one;                                                       \
                T sub = lhs - rhs;                                                      \
                arr[i] = sub;                                                           \
            }                                                                           \
            for (T i = 1; i < LEN; ++i) {                                               \
                T lhsl = arr[i - one];                                                  \
                T lhsr = arr[i];                                                        \
                T lhs = lhsl * lhsr;                                                    \
                arr[i] = lhs;                                                           \
            }                                                                           \
            clock_t tf = clock();                                                       \
                                                                                        \
            clocks_arr[_] = tf - t0;                                                    \
        }                                                                               \
        for (T _ = 0; _ < LEN; ++_) {                                                   \
            clock_t elapsed = clocks_arr[_];                                            \
            printf("%ld\n", elapsed);                                                   \
        }                                                                               \
        free(rand_arr);                                                                 \
        free(clocks_arr);                                                               \
    }

#define PERFORMANCE_LOOP_NODIVMULT(T, arr)                                              \
    {                                                                                   \
        printf(#T "\n");                                                                \
                                                                                        \
        T* rand_arr = (T*)(aligned_alloc(64, LEN * sizeof(*rand_arr)));                 \
        clock_t* clocks_arr = (clock_t*)(aligned_alloc(64, LEN * sizeof(*clocks_arr))); \
                                                                                        \
        for (T i = 0; i < LEN; ++i) {                                                   \
            rand_arr[i] = (T)(rand());                                                  \
        }                                                                               \
                                                                                        \
        T one = (T)(1);                                                                 \
        for (T _ = 0; _ < LEN; ++_) {                                                   \
            clock_t t0 = clock();                                                       \
            for (T i = 0; i < LEN; ++i) {                                               \
                T r = rand_arr[i];                                                      \
                T lhs = r + i;                                                          \
                T rhs = r >> one;                                                       \
                T sub = lhs - rhs;                                                      \
                arr[i] = sub;                                                           \
            }                                                                           \
            clock_t tf = clock();                                                       \
                                                                                        \
            clocks_arr[_] = tf - t0;                                                    \
        }                                                                               \
        for (T _ = 0; _ < LEN; ++_) {                                                   \
            clock_t elapsed = clocks_arr[_];                                            \
            printf("%ld\n", elapsed);                                                   \
        }                                                                               \
        free(rand_arr);                                                                 \
        free(clocks_arr);                                                               \
    }

int main() {
    // gcc -O2 -Wall -Wextra -Wpedantic
    // movdqu
    // Ice Lake (https://www.agner.org/optimize/instruction_tables.pdf)
    // https://www.intel.la/content/www/xl/es/products/sku/232160/intel-core-i71355u-processor-12m-cache-up-to-5-00-ghz/specifications.html
    srand(time(NULL));

    int32_t* s_arr = (int32_t*)(aligned_alloc(64, LEN * sizeof(*s_arr)));
    uint32_t* u_arr = (uint32_t*)(aligned_alloc(64, LEN * sizeof(*u_arr)));

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

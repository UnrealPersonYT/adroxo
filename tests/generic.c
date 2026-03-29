#include <adroxo.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

// -----------------------------------------
// DETERMINISM TESTS
// -----------------------------------------

static void test_adroxo32_q_determinism(void) {
    uint32_t s_a[4] = {0x1, 0x2, 0x3, 0x4};
    uint32_t s_b[4] = {0x1, 0x2, 0x3, 0x4};
    uint32_t r_a = adroxo32_q(s_a);
    uint32_t r_b = adroxo32_q(s_b);
    assert(r_a == r_b);
    assert(memcmp(s_a, s_b, 16) == 0);
}

static void test_adroxo64_q_determinism(void) {
    uint64_t s_a[4] = {0x1, 0x2, 0x3, 0x4};
    uint64_t s_b[4] = {0x1, 0x2, 0x3, 0x4};
    uint64_t r_a = adroxo64_q(s_a);
    uint64_t r_b = adroxo64_q(s_b);
    assert(r_a == r_b);
    assert(memcmp(s_a, s_b, 32) == 0);
}

// -----------------------------------------
// SPEED TESTS
// -----------------------------------------

static void test_adroxo32_q_speed(void) {
    uint32_t state[4] = {1, 2, 3, 4};
    uint32_t sum = 0;
    const int iterations = 10000000;
    clock_t start = clock();
    for (int i = 0; i < iterations; i++) {
        sum ^= adroxo32_q(state);
    }
    clock_t end = clock();
    double sec = (double)(end - start) / CLOCKS_PER_SEC;
    printf("  adroxo32_q Speed: %.2f M ops/sec (Sum: %u)\n", 
           iterations / sec / 1000000.0, (unsigned int)sum);
}

static void test_adroxo64_q_speed(void) {
    uint64_t state[4] = {1, 2, 3, 4};
    uint64_t sum = 0;
    const int iterations = 10000000;
    clock_t start = clock();
    for (int i = 0; i < iterations; i++) {
        sum ^= adroxo64_q(state);
    }
    clock_t end = clock();
    double sec = (double)(end - start) / CLOCKS_PER_SEC;
    printf("  adroxo64_q Speed: %.2f M ops/sec (Sum: %llu)\n", 
           iterations / sec / 1000000.0, (unsigned long long)sum);
}

// -----------------------------------------
// VOID MIXER WRAPPER
// -----------------------------------------

static void test_void_speed(const char* name, void (*fn)(void*), size_t bits) {
    uint8_t data[64] = {0};
    const int iterations = 1000000;
    clock_t start = clock();
    for(int i = 0; i < iterations; i++) {
        fn(data);
    }
    clock_t end = clock();
    double sec = (double)(end - start) / CLOCKS_PER_SEC;
    printf("  %s Speed (%zu-bit): %.2f M ops/sec\n", name, bits, iterations / sec / 1000000.0);
}

// -----------------------------------------
// MAIN
// -----------------------------------------

int main(void) {
    printf("--- Testing Adroxo _q Primitives ---\n");
    
    test_adroxo32_q_determinism();
    test_adroxo32_q_speed();
    printf("  adroxo32_q OK\n\n");

    test_adroxo64_q_determinism();
    test_adroxo64_q_speed();
    printf("  adroxo64_q OK\n\n");

    printf("--- Testing Adroxo Full Mixers ---\n");
    test_void_speed("adroxo128", adroxo128, 128);
    test_void_speed("adroxo256", adroxo256, 256);
    test_void_speed("adroxo512", adroxo512, 512);
    printf("  Full Mix Tests OK\n\n");

    printf("All Adroxo tests passed successfully.\n");
    return 0;
}
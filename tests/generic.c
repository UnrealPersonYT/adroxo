#include <adroxo.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>

// -----------------------------------------
// Determinism test (unchanged)
// -----------------------------------------
static void test_determinism(void (*fn)(void*), size_t len){
    uint8_t a[64] = {0};
    uint8_t b[64] = {0};

    for(size_t i = 0; i < len; i++){
        a[i] = (uint8_t)i;
        b[i] = (uint8_t)i;
    }

    fn(a);
    fn(b);

    assert(memcmp(a, b, len) == 0);
}

// -----------------------------------------
// SPEED TEST (NEW)
// -----------------------------------------
static void test_speed(void (*fn)(void*), size_t len){
    uint8_t data[64];

    for(size_t i = 0; i < len; i++)
        data[i] = (uint8_t)i;

    const int iterations = 1000000;

    clock_t start = clock();

    for(int i = 0; i < iterations; i++){
        fn(data);
    }

    clock_t end = clock();

    double sec = (double)(end - start) / CLOCKS_PER_SEC;

    printf("  Speed (%zu bytes): %.2f M ops/sec\n",
           len, iterations / sec / 1000000.0);
}

// -----------------------------------------
// AVALANCHE SCORE (IMPROVED)
// -----------------------------------------
static void test_avalanche_score(void (*fn)(void*), size_t len){
    uint8_t a[64] = {0};
    uint8_t b[64] = {0};

    a[0] = 0x00;
    b[0] = 0x01;

    fn(a);
    fn(b);

    int diff_bits = 0;

    for(size_t i = 0; i < len; i++){
        uint8_t x = a[i] ^ b[i];
        for(int j = 0; j < 8; j++){
            diff_bits += (x >> j) & 1;
        }
    }

    double total_bits = len * 8;
    double avalanche = diff_bits / total_bits;

    printf("  Avalanche score (%zu bytes): %.3f\n", len, avalanche);

    // Weak threshold check (adjust if needed)
    assert(avalanche > 0.3);
}

// -----------------------------------------
// Run tests per function
// -----------------------------------------
static void run_tests(const char* name,
                      void (*fn)(void*),
                      size_t len){
    printf("Testing %s...\n", name);

    test_determinism(fn, len);
    test_speed(fn, len);
    test_avalanche_score(fn, len);

    printf("  OK\n\n");
}

// -----------------------------------------
// Main
// -----------------------------------------
int main(void){
    run_tests("adroxo32",  adroxo32,  4);
    run_tests("adroxo64",  adroxo64,  8);
    run_tests("adroxo128", adroxo128, 16);
    run_tests("adroxo256", adroxo256, 32);
    run_tests("adroxo512", adroxo512, 64);

    printf("All tests passed.\n");
    return 0;
}
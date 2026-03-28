#include <stdint.h>
#include <stddef.h>

const size_t ADROXO_GENERIC_ROUNDS = 8;

// 64-bit words

static inline uint64_t rol64(uint64_t x, size_t r){
    return (x << r) | (x >> (64 - r));
}

void adroxo512_r(void* __restrict state, size_t r){
    for(size_t rnd = 0; rnd < r; ++rnd)
    for(size_t i = 0; i < 8; ++i)
        if(!(i % 2))
            ((uint64_t*)state)[i] = rol64(((uint64_t*)state)[(i + 7) % 8] + ((uint64_t*)state)[i], !(i % 4) ? 29: 16);
        else
            ((uint64_t*)state)[i] ^= ((uint64_t*)state)[(i + 7) % 8];
}
void adroxo512(void* __restrict state){
    adroxo512_r(state, ADROXO_GENERIC_ROUNDS);
}
void adroxo256_r(void* __restrict state, size_t r){
    for(size_t rnd = 0; rnd < r; ++rnd)
    for(size_t i = 0; i < 4; ++i)
        if(!(i % 2))
            ((uint64_t*)state)[i] = rol64(((uint64_t*)state)[(i + 3) % 4] + ((uint64_t*)state)[i], !(i % 4) ? 29: 16);
        else
            ((uint64_t*)state)[i] ^= ((uint64_t*)state)[(i + 3) % 4];
}
void adroxo256(void* __restrict state){
    adroxo256_r(state, ADROXO_GENERIC_ROUNDS);
}

// 32-bit words

static inline uint32_t rol32(uint32_t x, size_t r){
    return (x << r) | (x >> (32 - r));
}

void adroxo128_r(void* __restrict state, size_t r){
    for(size_t rnd = 0; rnd < r; ++rnd)
    for(size_t i = 0; i < 4; ++i)
        if(!(i % 2))
            ((uint32_t*)state)[i] = rol32(((uint32_t*)state)[(i + 3) % 4] + ((uint32_t*)state)[i], !(i % 4) ? 13: 8);
        else
            ((uint32_t*)state)[i] ^= ((uint32_t*)state)[(i + 3) % 4];
}
void adroxo128(void* __restrict state){
    adroxo128_r(state, ADROXO_GENERIC_ROUNDS);
}

// 16-bit words

static inline uint16_t rol16(uint16_t x, size_t r){
    return (x << r) | (x >> (16 - r));
}

void adroxo64_r(void* __restrict state, size_t r){
    for(size_t rnd = 0; rnd < r; ++rnd)
    for(size_t i = 0; i < 4; ++i)
        if(!(i % 2))
            ((uint16_t*)state)[i] = rol16(((uint16_t*)state)[(i + 3) % 4] + ((uint16_t*)state)[i], !(i % 4) ? 7: 4);
        else
            ((uint16_t*)state)[i] ^= ((uint16_t*)state)[(i + 3) % 4];
}
void adroxo64(void* __restrict state){
    adroxo64_r(state, ADROXO_GENERIC_ROUNDS);
}

// 8-bit words

static inline uint8_t rol8(uint8_t x, size_t r){
    return (x << r) | (x >> (8 - r));
}

void adroxo32_r(void* __restrict state, size_t r){
    for(size_t rnd = 0; rnd < r; ++rnd)
    for(size_t i = 0; i < 4; ++i)
        if(!(i % 2))
            ((uint8_t*)state)[i] = rol8(((uint8_t*)state)[(i + 3) % 4] + ((uint8_t*)state)[i], !(i % 4) ? 3: 2);
        else
            ((uint8_t*)state)[i] ^= ((uint8_t*)state)[(i + 3) % 4];
}
void adroxo32(void* __restrict state){
    adroxo32_r(state, ADROXO_GENERIC_ROUNDS);
}
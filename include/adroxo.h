/**
 * @file adroxo.h
 * @brief Adroxo: a tiny, in-place ARX mixing primitive.
 *
 * Each function mixes a fixed-size state buffer (32–512 bits) in place.
 * The `_r` variants apply an explicit number of rounds.
 * The non-`_r` variants apply ADROXO_GENERIC_ROUNDS, a stable default.
 * The `_q` variants are for quick high entropy 32,64 bit integers.
 *
 * The `state` pointer must reference a buffer of the exact size:
 *   - adroxo32*  :  4 bytes
 *   - adroxo64*  :  8 bytes
 *   - adroxo128* : 16 bytes
 *   - adroxo256* : 32 bytes
 *   - adroxo512* : 64 bytes
 *
 * Buffers may be byte arrays or integer arrays; alignment is not required.
 * All functions mutate the state in place.
 */
#ifndef ADROXO_H
#define ADROXO_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"{
#endif  // __cplusplus

// Internal rounds used for generic adroxo functions
extern const size_t ADROXO_GENERIC_ROUNDS;

/// @brief       Mixes a 512-bit `state` for `r` rounds
/// @param state 512-bit buffer to mix
/// @param r     Total rounds to mix
extern void adroxo512_r(void* __restrict state, size_t r);
/// @brief       Mixes a 512-bit `state` for `ADROXO_GENERIC_ROUNDS` round
/// @param state 512-bit buffer to mix
extern void adroxo512(void* __restrict state);
/// @brief       Mixes a 256-bit `state` for `r` rounds
/// @param state 256-bit buffer to mix
/// @param r     Total rounds to mix
extern void adroxo256_r(void* __restrict state, size_t r);
/// @brief       Mixes a 256-bit `state` for `ADROXO_GENERIC_ROUNDS` round
/// @param state 256-bit buffer to mix
extern void adroxo256(void* __restrict state);
/// @brief       Mixes a 256-bit state with one round and returns a 64-bit integer
/// @param state 256-bit buffer to mix
/// @return      High entropy 64-bit
extern uint64_t adroxo64_q(void* __restrict state);
/// @brief       Mixes a 128-bit `state` for `r` rounds
/// @param state 128-bit buffer to mix
/// @param r     Total rounds to mix
extern void adroxo128_r(void* __restrict state, size_t r);
/// @brief       Mixes a 128-bit `state` for `ADROXO_GENERIC_ROUNDS` round
/// @param state 128-bit buffer to mix
extern void adroxo128(void* __restrict state);
/// @brief       Mixes a 128-bit state with one round and returns a 32-bit integer
/// @param state 128-bit buffer to mix
/// @return      High entropy 32-bit
extern uint32_t adroxo32_q(void* __restrict state);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // ADROXO_H
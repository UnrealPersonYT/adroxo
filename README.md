# Adroxo: Tiny, In-Place ARX Mixing

**Adroxo** is a minimalist, high-performance C library for mixing data in-place. It is designed for applications requiring high-speed, high-entropy statistical randomness, such as **Monte Carlo simulations**, **procedural generation**, and **data compression pipelines**.

By utilizing a **3-operation/2-word (3p2w)** mixing logic, Adroxo achieves extreme instruction density and throughput while maintaining a high statistical "quality floor."

---

## Features
* **Zero-Dependency:** Standard C99/C23 compatible.
* **Branchless & Inline-Ready:** Optimized for modern CPUs with zero jumps in the hot path.
* **Zero Allocations:** Operates entirely in-place on user-provided buffers.
* **Quick Variants (`_q`):** Specialized 1-round functions that return high-entropy integers in ~15 instructions.

---

## API Overview

### High-Speed Extraction
The `_q` variants are the fastest way to generate a single random number. These use a **4:1 state-to-output ratio** to ensure maximum entropy per call. For a 32-bit result, provide a 128-bit (16-byte) state. For a 64-bit result, provide a 256-bit (32-byte) state.

```c
uint32_t val = adroxo32_q(state128); 
uint64_t val = adroxo64_q(state256); 
```

### Full State Mixing
These functions shuffle the entire provided buffer. The standard versions default to 8 rounds of mixing, which is recommended for most non-cryptographic applications to ensure deep bit diffusion. You can also use the `_r` variants to manually define the total number of mixing rounds if your application requires specific performance tuning or research-grade security margins.

```c
void adroxo128(void* state);
void adroxo256(void* state);
void adroxo512(void* state);
void adroxo256_r(void* state, size_t r);
```

---

## Implementation Details

Adroxo uses a tight **ARX** pattern (Addition-Rotation-XOR). The `_q` variants compress multiple 32/64 bit lanes into a high entropy output. This acts as a powerful statistical filter to hide internal state patterns and ensure high entropy even with a single mixing round.

## License
[LICENSE](LICENSE)
# Adroxo

Adroxo is a tiny, in‑place ARX mixing primitive implemented in portable C.  
It provides fast, deterministic mixing functions for fixed‑size state buffers (32–512 bits), with both explicit‑round and default‑round variants.  
The entire library consists of one header, one source file, and one static library.

## Features

- Minimal API surface
- In‑place mixing (no allocations)
- Supports 32, 64, 128, 256, and 512‑bit state sizes
- Explicit‑round (`*_r`) and default‑round variants
- Portable C implementation (GCC, Clang, MSVC)
- Simple `make` build or install
- No dependencies, no globals, no hidden state

## Building & Installing

To build and install:

```sh
make
make install
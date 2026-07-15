# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

YalAA (Yet Another Library for Affine Arithmetic) is a C++ template library for affine arithmetic (AA). Unlike interval arithmetic which only tracks bounds, AA tracks first-order dependencies during computation, often yielding tighter bounds at the cost of increased computational effort.

## Build Commands

```bash
# Configure (CXSC_ROOT points at the interval backend's install prefix,
# i.e. the directory containing include/ and lib/)
cmake -S . -B build -DCXSC_ROOT=<CXSC-PATH>

# Build (library + examples by default)
cmake --build build

# Install
cmake --install build

# Run tests (requires -DYALAA_ENABLE_TESTS=ON and GTest findable via find_package)
cmake -S . -B build -DYALAA_ENABLE_TESTS=ON
cmake --build build
ctest --test-dir build --output-on-failure

# Generate documentation (requires Doxygen; not wired into the CMake build)
doxygen Doxyfile
```

### CMake Options

- `-DYALAA_IV_BACKEND=cxsc|filib|profil_bias|custom` - Interval backend (default `cxsc`)
- `-DCXSC_ROOT=<path>` / `-DFILIB_ROOT=<path>` / `-DPROFIL_BIAS_ROOT=<path>` - Hint variable
  for the corresponding `Find<Backend>.cmake` module in `cmake/` (or set `CMAKE_PREFIX_PATH`)
- `-DYALAA_BUILD_EXAMPLES=ON|OFF` - Build the example programs (default `ON`)
- `-DYALAA_ENABLE_TESTS=ON|OFF` - Build the unit tests, requires GTest (default `OFF`)
- `-DCMAKE_BUILD_TYPE=Debug|Release|RelWithDebInfo|MinSizeRel` - Build type (defaults to `Release`)

## Architecture

### Template Structure

The core `AffineForm<T, ET, AC, AR, AP, EP, IV>` template combines:

- **T** - Base floating-point type (double, float, long double)
- **ET** - Error term template (`ErrorTermImpl`)
- **AC** - Affine combination template (`AffineCombImpl`)
- **AR** - Arithmetic kernel (`ExactErrorFP`)
- **AP** - Affine policy (AF0, AF1, AF2)
- **EP** - Error policy (`ErrorPolStd`, `ErrorPolDec`)
- **IV** - Interval type (from underlying interval library)

### Key Components

**Affine Policies** (`src/pol/`):
- `AF0` - Standard affine arithmetic (Stolfi et al.) - new noise symbol per error
- `AF1` - Extended model (Messine, 2002) - errors accumulated in single term
- `AF2` - Extended model with positive/negative/general error separation (partially supported)

**Error Policies** (`src/pol/`):
- `ErrorPolStd` - Standard error handling (NONE, EMPTY, R states)
- `ErrorPolDec` - P1788-style decorations (D0-D5, DE states for tracking domain validity)

**Arithmetic Kernel** (`src/kernel/`):
- `ExactErrorFP` - Combines affine operations, multiplication, Chebyshev approximations, and misc functions for IEEE754 types

**Traits** (`src/traits/`):
- `base_traits<T>` - Specializations for float, double, long double
- `interval_traits<IV>` - Adapter for interval libraries (cxsc, filib, profil, custom)

### Predefined Types

All in namespace `yalaa`:
- `aff_e_d` - Standard AF0 with double, ExactErrorFP kernel
- `aff_af1_e_d` - AF1 variant
- `aff_e_d_dec` - AF0 with decorations
- `aff_af1_e_d_dec` - AF1 with decorations

### Elementary Functions

Supported via friend functions on `AffineForm`: `sqr`, `sqrt`, `pown`, `exp`, `exp2`, `exp10`, `log`, `log2`, `log10`, `sin`, `cos`, `tan`, `asin`, `acos`, `atan`, `sinh`, `cosh`, `tanh`, `asinh`, `acosh`, `atanh`, `abs`, `pow`, `powr`.

## Dependencies

- One interval library: C-XSC >= 2.5.0, filib++ >= 3.0.2, or PROFIL/BIAS >= 2.0.8
- Google Test (optional, for unit tests)

## Custom Interval Library

To use a custom interval library, provide a specialization of `yalaa::traits::interval_traits<YourIVType>` with the required operations. See `src/traits/custom_iv_traits.hpp` for the interface.

## Git Commits

Never add a `Co-Authored-By` trailer (or similar attribution) to commit messages.

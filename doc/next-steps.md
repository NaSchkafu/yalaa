# YalAA Modernization Plan

YalAA is a C++03-era template library (last commit 2016, targeting GCC 4.5 / VS2010) that
uses Boost as a polyfill for features that are now standard C++. This document lists
concrete modernization items based on an analysis of the codebase, roughly ordered by impact.

## 1. Drop Boost entirely — Done

Boost is used almost exclusively as a C++11 polyfill:

- `boost::enable_if`, `boost::is_fundamental`, `boost::mpl::if_`,
  `BOOST_MPL_HAS_XXX_TRAIT_DEF`, `boost::add_const`/`boost::add_reference`
  (`src/affineform.hpp:34-40`)
- `BOOST_FOREACH` in the tests

All of these have direct `<type_traits>` equivalents since C++11. The only structural use
is `boost::arithmetic<>` operator generation (`src/affineform.hpp:76-82`), which is easily
replaced by hidden-friend operators.

Removing the Boost >= 1.47 requirement makes the library dramatically easier to adopt.

## 2. Target a modern C++ standard (C++17 or C++20)

The code is deliberately C++03-compatible — see the `#ifdef _MSC_VER` workaround for
`friend EP<T, IV>` at `src/affineform.hpp:349-356`, which is unnecessary since C++11.
Concrete wins:

- **Simplify the template signature.** The seven-parameter template-template signature
  `AffineForm<T, ET, AC, AR, AP, EP, IV>` with its `YALAA_AFF_TEMPLATE` macro wall is the
  hardest part of the codebase to work with. Default template arguments plus alias
  templates (or a redesign around plain type parameters and C++20 concepts) would simplify
  both the implementation and custom policy authoring.
- **Real concepts.** `src/concepts/` contains documentation-only "concepts" — C++20
  `concept` definitions would turn these into compiler-checked interfaces.
- **Move semantics.** An `AffineForm` owns a container of error terms, so move
  constructors/assignment are a real performance win in expression-heavy code, not just
  cosmetics.
- **`if constexpr`** to replace tag-dispatch/SFINAE in the kernels.

## 3. Replace autotools with CMake, delete the parallel MSVC build — Done

There are currently two build systems:

1. autoconf/automake with hand-written m4 macros, including a `AC_CXX_COMPILE_STDCXX_0X`
   check that is long obsolete
2. checked-in VS2010 `.vcxproj`/`.sln` files

One `CMakeLists.txt` with options for the interval backend replaces both, enables
`find_package` for consumers, and unlocks vcpkg/Conan packaging later.

## 4. Go header-only

The library is already ~95% header-only structurally. The compiled `libyalaa` consists of
only two translation units:

1. `helper/fphelper.cpp` (~146 lines) — the `RndControl` rounding-mode wrapper around
   `fesetround`/`_controlfp`. Trivially made header-only by marking the functions `inline`.
2. `yalaa_fp_impl.cpp` — no unique logic; it `#include`s the template `.cpp` files and
   performs *explicit instantiations* of the predefined types (`aff_e_d`, `aff_af1_e_d`,
   decorated/float/long-double variants). The compiled library only buys consumers
   pre-instantiation, i.e. compile time — not functionality.

Plan:

- Ship header-only by default (CMake `INTERFACE` target). Backend selection becomes a
  plain compile definition in the consumer — no more building/installing the library
  against the right interval backend.
- Optionally keep a compiled target that declares `extern template` for the predefined
  types and builds the instantiations once, for compile-time-sensitive users.
- Rename the `.cpp`-as-template-implementation files (`kernel/nonaff/*.cpp`, `comb/*.cpp`)
  to `.inl` or merge them into their headers — files named `.cpp` that must never be
  compiled standalone confuse build systems and humans.
- `static` locals in template functions (e.g. `static const T S_PINF` in
  `ChebyshevFP::sin`, marked `// TODO: thread safe`) are fine in headers linkage-wise,
  and C++11 magic statics fix the thread-safety TODO for free.
- **Licensing decision required:** YalAA is LGPL-3.0, whose mechanics hinge on the linking
  boundary. With a header-only template library everything is compiled into the user's
  binary, so LGPL effectively degrades toward GPL-ish obligations. Header-only libraries
  overwhelmingly use MIT, BSL, or Apache-2.0; alternatively add an eigen/FLTK-style
  linking/template exception.

## 5. Fix correctness/portability landmines

- **Reserved identifiers in include guards.** All include guards use reserved identifiers
  (`__YALAA_HPP__` etc.). The most recent commit ("Typo in include guard") is exactly the
  kind of bug this invites. Use `#pragma once` or a `YALAA_`-prefixed scheme.
- **UB in the primary `base_traits` template.** `src/traits/base_traits.hpp` has non-void
  static functions with *empty bodies* — instantiating the primary template is undefined
  behavior instead of a compile error. These should be `= delete` or
  `static_assert(dependent_false<T>)`.
- **Non-conforming in-class initialization.** `src/tests/test_main.cpp` initializes
  `static const double` members in-class, which was non-conforming before C++17 and only
  compiled by GCC leniency.
- **Rounding-mode machinery.** `src/helper/fphelper.cpp` (`_controlfp`/`fesetround`,
  `-frounding-math`) needs re-verification against modern optimizing compilers.
  Longer-term, error-free transformations (TwoSum/TwoProd via `std::fma`) could remove
  rounding-mode switching from hot paths entirely.

## 6. Reconsider the interval backend story

The default backend C-XSC last released in 2014, and filib++/PROFIL are similarly
unmaintained. Options:

- Promote the `custom_ivlib` traits mechanism.
- Add a maintained backend (e.g. Boost.Interval — ironic given item 1 — or GAOL).
- Ship a small self-contained double-interval implementation so YalAA works out of the box
  with zero dependencies. This would be the single biggest usability improvement.

## 7. Repository hygiene

Checked-in editor/IDE artifacts and dead code to delete:

- `trunk.suo` (binary VS user state), `*.vcxproj.user`
- `create_*.sh~` emacs backup files
- `src/intervaladapt_old`, `src/helper/ivhelper_cpp`, `src/helper/ivhelper_hpp`
- `src/main.cpp` — an ad-hoc test driver with German debug output that duplicates the
  gtest suite

Add a `.gitignore`.

## 8. CI and tests

No CI exists. A GitHub Actions matrix (GCC/Clang/MSVC × the supported backends) is cheap
once CMake lands.

The test suite is a single 260-line file covering only elementary-function ranges for one
configuration (`AFF_TYPE` is switched by editing a `#define`). It should cover:

- arithmetic operators
- all three affine policies (AF0/AF1/AF2)
- decorations (`ErrorPolDec`)
- special-value handling

parameterized over configurations rather than recompiled.

## 9. Documentation and distribution

- `README.md` is three lines pointing to a university URL that likely no longer resolves.
  Write a modern README with a quick-start example.
- The Doxygen mainpage — Done, it now describes the CMake build instead of the old
  VS2010/autotools workflow. Still to do: publish the generated docs via GitHub Pages.
- Headers currently live flat in `src/`; move to an `include/yalaa/` install layout.
- Make an explicit decision: finish or remove the "partially supported" AF2 policy.

## Suggested sequencing

1. **CMake first** — everything else hangs off being able to build easily. Done.
2. **Boost removal** — done, kept on the existing C++11 baseline as a smaller, separately
   reviewable step rather than bundling it with the C++17 bump below.
3. **C++17 baseline + header-only conversion** in one pass, since they touch the same lines.
4. **CI.**
5. **Backend/API redesign** (items 2 and 6).

Items 5 and 7 are quick wins that can happen anytime.

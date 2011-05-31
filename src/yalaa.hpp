#ifndef __YALAA_HPP__
#define __YALAA_HPP__

// fwds
#include "yalaa_fwd.hpp"

// traits
#include "traits/base_traits.hpp"
#ifdef HAVE_CXSC
#include "traits/cxsc_traits.hpp"
#elif HAVE_FILIB
#include "traits/filib_traits.hpp"
#else
#error No supported interval library
#endif
#include "traits/float_traits.hpp"
#include "traits/double_traits.hpp"
#ifdef HAVE_LONG_DOUBLE_WIDER
#include "traits/l_double_traits.hpp"
#endif

// errterm
#include "errortermimpl.hpp"
// comb
#include "comb/affinecombimpl.hpp"
//kernel
#include "kernel/exacterror.hpp"
// aff pol
#include "pol/af0.hpp"
// err pol
#include "pol/errorpolstd.hpp"
#include "pol/errorpoldec.hpp"
// aff
#include "affineform.hpp"
#include "affineform_double.hpp"
#include "yalaa_ios.hpp"


#endif /*__YALAA_HPP__*/

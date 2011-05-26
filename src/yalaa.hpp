#ifndef __YALAA_HPP__
#define __YALAA_HPP__
// This file and its associated source file take care of
// instantiating the AffineForm template for some standard
// template parameters.
// If you want to use custom parameters, you have to write
// your own instantiations or you will get some nice linker errors ;-).

// configuration
#include "config.h"

// traits
#include "traits/base_traits.hpp"
#include "traits/float_traits.hpp"
#include "traits/double_traits.hpp"
#ifdef HAVE_LONG_DOUBLE_WIDER
#include "traits/l_double_traits.hpp"
#endif
#ifdef HAVE_CXSC
#include "traits/cxsc_traits.hpp"
#elif HAVE_FILIB
#include "traits/filib_traits.hpp"
#else
#error No supported interval library
#endif
// Standard Errorterm
#include "errortermimpl.hpp"
// Standard affine combination
#include "comb/affinecombimpl.hpp"
// Standard affine combination operations
#include "comb/affinecombopimpl.hpp"
// Exact error kernel
#include "kernel/exacterror.hpp"
// Standardpolicy
#include "pol/af0.hpp"
// ErrorPolicy
#include "pol/errorpol.hpp"
// AffineForm
#include "affineform.hpp"
#include "affineform_double.hpp"
// I/O
#include "yalaa_ios.hpp"

namespace yalaa 
{
  /// Affine Form with the ExactError kernel for double
  typedef AffineForm<double, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP, 
		     yalaa::pol::AF0, yalaa::pol::ErrorPolImpl, details::sel_iv_t> aff_e_d;
#if 0
  typedef AffineForm<float, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP, 
		     yalaa::pol::AF0, yalaa::pol::ErrorPolImpl, details::sel_iv_t> aff_e_f;
#endif

// You can use this typedef for a long double type
// Note that you interval library has to support long double for this to work
#if defined(HAVE_LONG_DOUBLE_WIDER) && 0
  typedef AffineForm<long double, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP, 
		     yalaa::pol::AF0, yalaa::pol::ErrorPolImpl, details::sel_iv_t> aff_e_ld;
#endif

}

#endif /*__YALAA_HPP__*/

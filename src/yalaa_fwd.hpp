#ifndef __YALAA_FWD_HPP__
#define __YALAA_FWD_HPP__
// This file and its associated source file take care of
// instantiating the AffineForm template for some standard
// template parameters.
// If you want to use custom parameters, you have to write
// your own instantiations or you will get some nice linker errors ;-).

// configuration
#include "config.h"

// iv selector
#include "yalaa_iv.hpp"

// AffineForm
#include "affineform_fwd.hpp"


namespace yalaa 
{
  namespace details
  {
    template<typename T>
    class ErrorTermImpl;
    template<typename T, template<typename> class ET>
    class AffineCombImpl;
  }

  namespace kernel 
  {
    template<typename T, template<typename> class ET, 
	     template<typename, template<typename> class> class AC, class IV>
    class ExactErrorFP;
  }

  namespace pol 
  {
    template<typename T, typename IV>
    class ErrorPolStd;
    template<typename, template<typename> class, template<typename, template<typename> class> class>
    class AF0;
  }

}

namespace yalaa 
{
#ifdef HAVE_FLOAT_IV
  /// Standard affine form with the ExactError kernel for float
  typedef AffineForm<float, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP, 
		     yalaa::pol::AF0, yalaa::pol::ErrorPolStd, details::float_iv_t> aff_e_f;
#endif

#ifdef HAVE_DOUBLE_IV
  /// Standard affine form with the ExactError kernel for double
  typedef AffineForm<double, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP, 
		     yalaa::pol::AF0, yalaa::pol::ErrorPolStd, details::double_iv_t> aff_e_d;
#endif

#ifdef HAVE_L_DOUBLE_IV
  /// Standard affine form with the ExactError kernel for long double
  typedef AffineForm<long double, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP,
		     yalaa::pol::AF0, yalaa::pol::ErrorPolStd, details::l_double_iv_t> aff_e_ld;
#endif

}

#endif /*__YALAA_FWD_HPP__*/

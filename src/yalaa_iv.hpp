#ifndef __YALAA_IV_HPP__
#define __YALAA_IV_HPP__

#include "config.h"

#undef HAVE_DOUBLE_IV
#undef HAVE_FLOAT_IV
#undef HAVE_L_DOUBLE_IV

#ifdef HAVE_CXSC
    #include <interval.hpp>
    #include <imath.hpp>
#elif HAVE_FILIB
    #include <interval/interval.hpp>
#endif

namespace yalaa 
{
  namespace details 
  {
#ifdef HAVE_CXSC
    typedef cxsc::interval double_iv_t;
    #define HAVE_DOUBLE_IV 1
#elif HAVE_FILIB
    typedef filib::interval<double> double_iv_t;
    #define HAVE_DOUBLE_IV 1
    // typedef filib::interval<float> float_iv_t;
// #define HAVE_FLOAT_IV 1
#endif

// #if defined(HAVE_LONG_DOUBLE_WIDER) && defined(HAVE_FILIB)
//     typedef filib::interval<float> l_double_iv_t;
//     #define HAVE_L_DOUBLE_IV 1
// #endif
  }
}

#endif /*__YALAA_IV_HPP__*/

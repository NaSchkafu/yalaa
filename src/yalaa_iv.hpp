/*
  Copyright 2011 Stefan Kiel <kiel@inf.uni-due.de>
  
  This file is part of yalaa.
  
  yalaa is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, version 3 of the License.
  
  yalaa is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public License
  along with yalaa.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef __YALAA_IV_HPP__
#define __YALAA_IV_HPP__

#include "config_sel.h"

#undef YALAA_HAVE_DOUBLE_IV
#undef YALAA_HAVE_FLOAT_IV
#undef YALAA_HAVE_L_DOUBLE_IV

#ifdef YALAA_HAVE_CXSC
    #include <interval.hpp>
    #include <imath.hpp>
#include "traits/cxsc_traits.hpp"
#elif YALAA_HAVE_FILIB
    #include <interval/interval.hpp>
#include "traits/filib_traits.hpp"
#endif

namespace yalaa 
{
  namespace details 
  {
#ifdef YALAA_HAVE_CXSC
    typedef cxsc::interval double_iv_t;
    #define YALAA_HAVE_DOUBLE_IV 1
#elif YALAA_HAVE_FILIB
    typedef filib::interval<double> double_iv_t;
    #define YALAA_HAVE_DOUBLE_IV 1
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

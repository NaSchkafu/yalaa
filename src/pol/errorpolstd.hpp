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


#ifndef __ERRORPOLSTD_HPP__
#define __ERRORPOLSTD_HPP__

#include "affineform_fwd.hpp"

#define YALAA_SPEC_TEMPLATE_DEF template<template<typename> class ET,   \
                                         template<typename, template<typename> class> class AC, \
                                         template<typename, template<typename> class, \
						  template<typename, template<typename> class> class, class> class AR, \
                                         template<typename, template<typename> class, \
						  template<typename, template<typename> class> class> class AP>
#define YALAA_SPEC_TEMPLATE_T yalaa::AffineForm<base_t, ET, AC, AR, AP, \
						yalaa::pol::ErrorPolStd, iv_t>


namespace yalaa 
{
  namespace pol
  {
    /// Implementation of the \c ErrorPolicy concept using the common affine error model
    /**
     * This class provides the common affine arithmetic error handling approach as described 
     * in (de Figueiredo and Stolfi, 1997). 
     */
    template<typename T, typename IV>
    class ErrorPolStd
    {
    public:
      enum special_t { NONE = 0, EMPTY = 2, R = 1 };

      typedef IV iv_t;
      typedef T base_t;
      typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;
      typedef yalaa::details::ArithmeticError<T> aerror_t;

      /**
       * Function called prior to an operation
       *
       * @param af1 affine form 1
       * @param af2 affine form 2
       *
       * @return true if a special form is generated
       */
      YALAA_SPEC_TEMPLATE_DEF
      inline static bool pre_op(YALAA_SPEC_TEMPLATE_T *af1, const YALAA_SPEC_TEMPLATE_T &af2);

      YALAA_SPEC_TEMPLATE_DEF
      inline static bool pre_op(YALAA_SPEC_TEMPLATE_T *af1, const iv_t &iv);

      YALAA_SPEC_TEMPLATE_DEF
      inline static bool pre_op(YALAA_SPEC_TEMPLATE_T *af, base_ref_t s);

      YALAA_SPEC_TEMPLATE_DEF
      inline static bool pre_op(YALAA_SPEC_TEMPLATE_T *af);


      YALAA_SPEC_TEMPLATE_DEF
      inline static void post_op(YALAA_SPEC_TEMPLATE_T *af1, const YALAA_SPEC_TEMPLATE_T &af2,
                                 const aerror_t &err);

      YALAA_SPEC_TEMPLATE_DEF
      inline static void post_op(YALAA_SPEC_TEMPLATE_T *af1, const iv_t &iv,
                                 const aerror_t &err);

      YALAA_SPEC_TEMPLATE_DEF
      inline static void post_op(YALAA_SPEC_TEMPLATE_T *af, base_ref_t s, const aerror_t &err);

      YALAA_SPEC_TEMPLATE_DEF
      inline static void post_op(YALAA_SPEC_TEMPLATE_T *af, const aerror_t &err);

      YALAA_SPEC_TEMPLATE_DEF
      inline static bool new_form(YALAA_SPEC_TEMPLATE_T *af, base_ref_t s);

      YALAA_SPEC_TEMPLATE_DEF
      inline static bool new_form(YALAA_SPEC_TEMPLATE_T *af, const iv_t& iv);

      /**
       * Determines whether the affine form has a special value
       *
       * @param val value to check
       *
       * @return true if val indicates a special value
       */
      YALAA_SPEC_TEMPLATE_DEF
      inline static bool valid(const YALAA_SPEC_TEMPLATE_T &af);
      // ****************************************************************

    private:
      inline static special_t to_special(const aerror_t& err);

      YALAA_SPEC_TEMPLATE_DEF
      inline static bool adjust_central(YALAA_SPEC_TEMPLATE_T *af);

    };
    #include "errorpolstd.inl"
  }
}


#undef YALAA_SPEC_TEMPLATE_T
#undef YALAA_SPEC_TEMPLATE_DEF

#endif /*__ERRORPOL_HPP__*/

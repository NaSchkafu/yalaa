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


#ifndef __ERRORPOL_HPP__
#define __ERRORPOL_HPP__

#include "affineform_fwd.hpp"

#include <boost/type_traits/is_floating_point.hpp>
#include <boost/utility/enable_if.hpp>

#define YALAA_SPEC_TEMPLATE_DEF template<template<typename> class ET,   \
                                         template<typename, template<typename> class> class AC, \
                                         template<typename, template<typename> class, \
						  template<typename, template<typename> class> class, class> class AR, \
                                         template<typename, template<typename> class, \
						  template<typename, template<typename> class> class> class AP>
#define YALAA_SPEC_TEMPLATE_T yalaa::AffineForm<T, ET, AC, AR, AP, yalaa::pol::ErrorPolDec, IV>

namespace yalaa
{
  /// Namespace for AffinePolicy and ErrorPolicy implementations
  namespace pol
  {
    /// An \c ErrorPolicy providing a decoration like error handling
    /**
     * This class implements the \c ErrorPolicy concept and provides a
     * decoration like approach, roughly following the decorations proposed
     * for the upcoming P1788 interval arithmetic standard.
     * 
     */
    template<typename T, typename IV>
    struct ErrorPolDec
    {
      // ****************************************************************
      // ErrorPol Concept Impl
      // ****************************************************************

      /// Decorations supported by \c YalAA
      /**
       * D5: certainly defined, continuous and bounded<br>
       * D4: defined and cont<br>
       * D3: defined<br>
       * D2: possibly defined<br>
       * D1: certainly undefined<br>
       * D0: empty set<br>
       * DE: error occurred<br>
       */
      enum deco_t { D5 = 6, D4 = 5, D3 = 4, D2 = 3, D1 = 2, D0 = 1, DE = 0 };

      typedef T base_t;
      typedef deco_t special_t;
      typedef IV iv_t;
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
       * Determines whether the affine form has a valid numerical value
       *
       * @param af affine form to check
       *
       * @return true if val indicates a special value
       */
      YALAA_SPEC_TEMPLATE_DEF
      inline static bool valid(const YALAA_SPEC_TEMPLATE_T &af);
      // ****************************************************************

      // ****************************************************************
      // Extra Functions
      // ****************************************************************


    private:
      inline static special_t to_deco(const aerror_t &err);
      inline static special_t iv_deco(const iv_t &err);
      inline static special_t scal_deco(const base_t &err);

      YALAA_SPEC_TEMPLATE_DEF
      inline static void adjust_central(YALAA_SPEC_TEMPLATE_T *af, const aerror_t *aerr = 0);

    };

    #include "errorpoldec.inl"
  }
}

#undef YALAA_SPEC_TEMPLATE_DEF
#undef YALAA_SPEC_TEMPLATE_T

#endif /*__ERRORPOLDEC_HPP__*/

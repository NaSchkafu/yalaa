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

/**
 * @file   errorpolicy.hpp
 * @author Stefan Kiel <kiel@inf.uni-due.de>
 * @date   Fri Oct 28 10:36:43 2011
 * 
 * @brief  Provides a structure describing the ErrorPolicy concept
 * 
 * 
 */


#define YALAA_SPEC_TEMPLATE_DEF template<template<typename> class ET,   \
                                         template<typename, template<typename> class> class AC, \
                                         template<typename, template<typename> class, \
						  template<typename, template<typename> class> class, class> class AR, \
                                         template<typename, template<typename> class, \
						  template<typename, template<typename> class> class> class AP>
#define YALAA_SPEC_TEMPLATE_T yalaa::AffineForm<base_t, ET, AC, AR, AP, \
						yalaa::concepts::ErrorPolicy, iv_t>


namespace yalaa 
{
  namespace concepts
  {
    /// Concept for managing errors and special values during the computation process
    /**
     * The ErrorPolicy is responsible for managing errors (domain violations, overflows, ...) 
     * which occurred during the computation. Furthermore, it provides a special value type
     * which can either used for indicating that an affine form is invalid or for adding additional
     * meta informations to the form.
     * 
     * @param T Type for partial deviations
     * @param IV Type of intervals of T
     * 
     */
    template<typename T, typename IV>
    struct ErrorPolicy
    {
    public:
      /// Type for special values. Every AffineForm using the ErrorPolicy has a member of this type.
      enum special_t {  };
      /// Interval type
      typedef IV iv_t;
      /// Type of partial deviations
      typedef T base_t;
      /// Const reference or base_t depending whether base_t is a fundamental type. 
      typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;
      /// 
      typedef yalaa::details::ArithmeticError<T> aerror_t;

      /**
       * Called by AffineForm prior to an operation
       * The special_t member of af1 should be adjusted if necessary. <br>
       * The operation call is not performed if false is returned.
       * 
       * @param af1 first argument of the operation to call
       * @param af2 second argument of the operation to call
       *
       * @return false if a special form is generated
       */
      YALAA_SPEC_TEMPLATE_DEF
       static bool pre_op(YALAA_SPEC_TEMPLATE_T *af1, const YALAA_SPEC_TEMPLATE_T &af2);

      /**
       * Called by AffineForm prior to an operation
       * The special_t member of af should be adjusted if necessary. <br>
       * The operation call is not performed if false is returned.
       * 
       * @param af first argument of the operation to call
       * @param iv second argument of the operation to call
       *
       * @return false if a special form is generated
       */
      YALAA_SPEC_TEMPLATE_DEF
       static bool pre_op(YALAA_SPEC_TEMPLATE_T *af, const iv_t &iv);

      /**
       * Called by AffineForm prior to an operation
       * The special_t member of af should be adjusted if necessary. <br>
       * The operation call is not performed if false is returned.
       * 
       * @param af first argument of the operation to call
       * @param s second argument of the operation to call
       *
       * @return false if a special form is generated
       */
      YALAA_SPEC_TEMPLATE_DEF
       static bool pre_op(YALAA_SPEC_TEMPLATE_T *af, base_ref_t s);

      /**
       * Called by AffineForm prior to an operation
       * The special_t member of af should be adjusted if necessary. <br>
       * The operation call is not performed if false is returned.
       * 
       * @param af argument of the operation to call
       *
       * @return false if a special form is generated
       */
      YALAA_SPEC_TEMPLATE_DEF
       static bool pre_op(YALAA_SPEC_TEMPLATE_T *af);

      /** 
       * Called by AffineForm after an operation
       * The special_t member of af1 should be adjusted if necessary. <br>
       * 
       * @param af1 first argument of the operation called
       * @param af2 second argument of the operation called
       * @param err error information returned by ArithmeticKernel
       */
      YALAA_SPEC_TEMPLATE_DEF
       static void post_op(YALAA_SPEC_TEMPLATE_T *af1, const YALAA_SPEC_TEMPLATE_T &af2,
                                 const aerror_t &err);

      /** 
       * Called by AffineForm after an operation
       * The special_t member of af should be adjusted if necessary. <br>
       * 
       * @param af first argument of the operation called
       * @param iv second argument of the operation called
       * @param err error information returned by ArithmeticKernel
       */
      YALAA_SPEC_TEMPLATE_DEF
       static void post_op(YALAA_SPEC_TEMPLATE_T *af1, const iv_t &iv,
                                 const aerror_t &err);

      /** 
       * Called by AffineForm after an operation
       * The special_t member of af should be adjusted if necessary. <br>
       * 
       * @param af first argument of the operation called
       * @param s second argument of the operation called
       * @param err error information returned by ArithmeticKernel
       */
      YALAA_SPEC_TEMPLATE_DEF
       static void post_op(YALAA_SPEC_TEMPLATE_T *af, base_ref_t s, const aerror_t &err);

      /** 
       * Called by AffineForm after an operation
       * The special_t member of af should be adjusted if necessary. <br>
       * 
       * @param af  argument of the operation called
       * @param err error information returned by ArithmeticKernel
       */
      YALAA_SPEC_TEMPLATE_DEF
       static void post_op(YALAA_SPEC_TEMPLATE_T *af, const aerror_t &err);

      /** 
       * Called by AffineForm before creating a new affine form.
       * The special_t member of af should be adjusted if necessary. <br>
       * 
       * @param af new form to construct
       * @param s partial deviation of the new form
       * 
       * @return false if the new form is a special form
       */
      YALAA_SPEC_TEMPLATE_DEF
      static bool new_form(YALAA_SPEC_TEMPLATE_T *af, base_ref_t s);

      /** 
       * Called by AffineForm before creating a new affine form.
       * The special_t member of af should be adjusted if necessary. <br>
       * 
       * @param af new form to construct
       * @param iv interval to enclose by af
       * 
       * @return false if the new form is a special form
       */
      YALAA_SPEC_TEMPLATE_DEF
       static bool new_form(YALAA_SPEC_TEMPLATE_T *af, const iv_t& iv);

      /**
       * Determines whether the affine form has a valid numerical value
       *
       * @param af affine form to check
       *
       * @return true if the form has a valid numerical value
       */
      YALAA_SPEC_TEMPLATE_DEF
      static bool valid(const YALAA_SPEC_TEMPLATE_T &af);
      // ****************************************************************
    };

  }
}


#undef YALAA_SPEC_TEMPLATE_T
#undef YALAA_SPEC_TEMPLATE_DEF


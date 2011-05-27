#ifndef __ERRORPOL_HPP__
#define __ERRORPOL_HPP__

#include "affineform_fwd.hpp"

#define YALAA_SPEC_TEMPLATE_DEF template<template<typename> class ET,	\
					 template<typename, template<typename> class> class AC,	\
					 template<typename, template<typename> class, template<typename, template<typename> class> class, class> class AR,\
					 template<typename, template<typename> class, template<typename, template<typename> class> class> class AP>
#define YALAA_SPEC_TEMPLATE_T yalaa::AffineForm<T, ET, AC, AR, AP, ErrorPolDec, IV>

namespace yalaa 
{

  namespace details
  {
    template<typename T> class ArithmeticError<T>;
  }

  namespace pol
  {
    template<typename T, typename IV>
    class ErrorPolDec
    {
    public:
      // ****************************************************************
      // ErrorPol Concept Impl
      // ****************************************************************
      typedef unsigned short special_t;
      typedef IV iv_t;
      typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;
      typedef aerror_t yalaa::details::ArithmeticError<T>;

      /** 
       * Function called prior to an operation
       * 
       * @param af1 affine form 1
       * @param af2 affine form 2
       * 
       * @return true if a special form is generated
       */
      YALAA_SPEC_TEMPLATE_DEF
      static bool pre_op(YALAA_SPEC_TEMPLATE_T & af1 const YALAA_SPEC_TEMPLATE_T &af2);

      YALAA_SPEC_TEMPLATE_DEF
      static bool pre_op(YALAA_SPEC_TEMPLATE_T &af1, const iv_t &iv);

      YALAA_SPEC_TEMPLATE_DEF
      static bool pre_op(YALAA_SPEC_TEMPLATE_T &af, base_ref_t s);

      YALAA_SPEC_TEMPLATE_DEF
      static bool pre_op(YALAA_SPEC_TEMPLATE_T &af);

      YALAA_SPEC_TEMPLATE_DEF
      static bool post_op(YALAA_SPEC_TEMPLATE_T &af1 const YALAA_SPEC_TEMPLATE_T &af2, 
			  const aerror_t &err);

      YALAA_SPEC_TEMPLATE_DEF
      static bool post_op(YALAA_SPEC_TEMPLATE_T &af1, const iv_t &iv, 
			  const aerror_t &err);

      YALAA_SPEC_TEMPLATE_DEF
      static bool post_op(YALAA_SPEC_TEMPLATE_T &af, base_ref_t s, const aerror_t &err);

      YALAA_SPEC_TEMPLATE_DEF
      static bool post_op(YALAA_SPEC_TEMPLATE_T &af, const aerror_t &err);

      /** 
       * Determines whether the affine form has a special value
       * 
       * @param val value to check
       * 
       * @return true if val indicates a special value
       */
      inline static bool special(special_t val);
      // ****************************************************************

      // ****************************************************************
      // Extra Functions
      // ****************************************************************
            
    }; 

    bool ErrorPolDec::valid(special_t val)
    {
      return !val;
    }
  }
}

#undef YALAA_SPEC_TEMPLATE_DEF
#undef YALAA_SPEC_TEMPLATE_T

#endif /*__ERRORPOL_HPP__*/

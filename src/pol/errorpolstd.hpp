#ifndef __ERRORPOLSTD_HPP__
#define __ERRORPOLSTD_HPP_

#include "affineform_fwd.hpp"

#define YALAA_SPEC_TEMPLATE_DEF template<template<typename> class ET,   \
                                         template<typename, template<typename> class> class AC, \
                                         template<typename, template<typename> class, template<typename, template<typename> class> class, class> class AR, \
                                         template<typename, template<typename> class, template<typename, template<typename> class> class> class AP>
#define YALAA_SPEC_TEMPLATE_T yalaa::AffineForm<T, ET, AC, AR, AP, ErrorPolStd, IV>


namespace yalaa 
{
  namespace pol
  {
    template<typename T, typename IV> class ErrorPolStd;

    template<typename T1, typename IV2>
    class ErrorPolStd
    {
    public:
      enum special_t { NONE = 0, EMPTY = 1, R = 2};

      typedef IV2 iv_t;
      typedef T1 base_t;
      typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;
      typedef yalaa::details::ArithmeticError<T1> aerror_t;

      /**
       * Function called prior to an operation
       *
       * @param af1 affine form 1
       * @param af2 affine form 2
       *
       * @return true if a special form is generated
       */
      template<template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       template<typename, template<typename> class, template<typename, template<typename> class> class, class> class AR,
	       template<typename, template<typename> class, template<typename, template<typename> class> class> class AP>
      inline static bool test(yalaa::AffineForm<T1, ET, AC, AR, AP, ErrorPolStd, IV2> &a);

      YALAA_SPEC_TEMPLATE_DEF
      inline static bool pre_op(YALAA_SPEC_TEMPLATE_T &af1 const YALAA_SPEC_TEMPLATE_T &af2);

      YALAA_SPEC_TEMPLATE_DEF
      inline static bool pre_op(YALAA_SPEC_TEMPLATE_T &af1, const iv_t &iv);

      YALAA_SPEC_TEMPLATE_DEF
      inline static bool pre_op(YALAA_SPEC_TEMPLATE_T &af, base_ref_t s);

      YALAA_SPEC_TEMPLATE_DEF
      inline static bool pre_op(YALAA_SPEC_TEMPLATE_T &af);


      YALAA_SPEC_TEMPLATE_DEF
      inline static void post_op(YALAA_SPEC_TEMPLATE_T &af1 const YALAA_SPEC_TEMPLATE_T &af2,
                                 const aerror_t &err);

      YALAA_SPEC_TEMPLATE_DEF
      inline static void post_op(YALAA_SPEC_TEMPLATE_T &af1, const iv_t &iv,
                                 const aerror_t &err);

      YALAA_SPEC_TEMPLATE_DEF
      inline static void post_op(YALAA_SPEC_TEMPLATE_T &af, base_ref_t s, const aerror_t &err);

      YALAA_SPEC_TEMPLATE_DEF
      inline static void post_op(YALAA_SPEC_TEMPLATE_T &af, const aerror_t &err);

      /**
       * Determines whether the affine form has a special value
       *
       * @param val value to check
       *
       * @return true if val indicates a special value
       */
      inline static bool special(special_t val);
      // ****************************************************************
    }; 
  }
}


#endif /*__ERRORPOL_HPP__*/

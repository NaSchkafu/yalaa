#ifndef __ERRORPOL_HPP__
#define __ERRORPOL_HPP__

#include "affineform_fwd.hpp"

#define YALAA_SPEC_TEMPLATE_DEF template<template<typename> class ET,   \
                                         template<typename, template<typename> class> class AC, \
                                         template<typename, template<typename> class, \
						  template<typename, template<typename> class> class, class> class AR, \
                                         template<typename, template<typename> class, \
						  template<typename, template<typename> class> class> class AP>
#define YALAA_SPEC_TEMPLATE_T yalaa::AffineForm<T, ET, AC, AR, AP, yalaa::pol::ErrorPolDec, IV>

namespace yalaa
{

  namespace pol
  {
    template<typename T, typename IV>
    struct ErrorPolDec
    {
      // ****************************************************************
      // ErrorPol Concept Impl
      // ****************************************************************
      typedef T base_t;
      typedef unsigned short special_t;
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


    private:
      YALAA_SPEC_TEMPLATE_DEF
      inline static special_t empty_undef(const YALAA_SPEC_TEMPLATE_T &af);
      inline static special_t to_deco(const aerror_t &err);
    };

    #include "errorpoldec.inl"
  }
}

#undef YALAA_SPEC_TEMPLATE_DEF
#undef YALAA_SPEC_TEMPLATE_T

#endif /*__ERRORPOLDEC_HPP__*/

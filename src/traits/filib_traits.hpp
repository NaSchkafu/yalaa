#ifndef __FILIB_TRAITS_HPP__
#define __FILIB_TRAITS_HPP__

#include "yalaa_iv.hpp"

namespace yalaa
{
  namespace details
  {
#define YALAA_FILIB_TRAITS(BASE)  template<>                    \
    struct base_traits<filib::interval<BASE> >                  \
    {                                                           \
      typedef filib::interval<BASE> base_t;                     \
      typedef BASE iv_base_t;                                   \
                                                                \
      static base_t my_zero()                                   \
      {                                                         \
        return base_t(0.0, 0.0);                                \
      }                                                         \
                                                                \
      static base_t my_one()                                    \
      {                                                         \
        return base_t(1.0, 1.0);                                \
      }                                                         \
                                                                \
      static base_t my_exp(const base_t &i)                     \
      {                                                         \
        return exp(i);                                          \
      }                                                         \
                                                                \
      static iv_base_t my_inf(const base_t &i)			\
      {                                                         \
        return inf(i);                                          \
      }                                                         \
                                                                \
      static iv_base_t my_sup(const base_t &i)			\
      {                                                         \
        return sup(i);                                          \
      }                                                         \
                                                                \
      static base_t my_add(const base_t &i1, const base_t &i2)  \
      {                                                         \
        return i1 + i2;                                         \
      }                                                         \
                                                                \
      static base_t my_sub(const base_t &i1, const base_t &i2)  \
      {                                                         \
        return i1 - i2;                                         \
      }                                                         \
                                                                \
      static base_t my_mul(const base_t &i1, const base_t &i2)  \
      {                                                         \
        return i1*i2;                                           \
      }                                                         \
                                                                \
      static base_t my_div(const base_t &i1, const base_t &i2)  \
      {                                                         \
        return i1/i2;                                           \
      }                                                         \
                                                                \
      static iv_base_t my_w(const base_t &i)                    \
      {                                                         \
        return diam(i);                                         \
      }                                                         \
                                                                \
      static iv_base_t my_mid(const base_t &i)                  \
      {                                                         \
        return mid(i);                                          \
      }                                                         \
                                                                \
      static base_t my_neg(const base_t &i)                     \
      {                                                         \
        return -i;                                              \
      }                                                         \
                                                                \
      static base_t my_sqr(const base_t &i)                     \
      {                                                         \
        return sqr(i);                                          \
      }                                                         \
                                                                \
      static base_t my_pow(const base_t &i, int n)              \
	{                         \
	    /*FIX*/                                                        \
	    return base_t(0.0, 0.0);               					\
      }                                                         \
                                                                \
      static base_t my_ln(const base_t &i)                      \
      {                                                         \
        return log(i);                                          \
      }                                                         \
                                                                \
      static iv_base_t my_rad(const base_t &i)                  \
      {								\
        return diam(i)*0.5;                                     \
      }                                                         \
                                                                \
      static base_t my_pi()                                     \
      {                                                         \
        return filib::interval<iv_base_t>::PI();                \
      }                                                         \
                                                                \
      static base_t my_cos(const base_t &i)                     \
      {                                                         \
        return cos(i);                                          \
      }                                                         \
                                                                \
      static base_t my_sin(const base_t &i)                     \
      {                                                         \
        return sin(i);                                          \
      }                                                         \
                                                                \
      static base_t my_sqrt(const base_t& i)                    \
      {                                                         \
        return sqrt(i);                                         \
      }                                                         \
																\
	  static bool is_empty(const base_t &i)						\
	  {															\
		return my_inf(i) > my_sup(i);							\
	  }															\
																\
	 static bool is_special(const base_t &i)					\
	 {															\
		return is_empty(i) || !_finite(my_sup(i)) || !_finite(my_inf(i)) || _isnan(my_inf(i)) || _isnan(my_sup(i)); \
	 } \
    };

    YALAA_FILIB_TRAITS(float)
    YALAA_FILIB_TRAITS(double)
  }
}

#endif /*__FILIB_TRAITS_HPP__*/

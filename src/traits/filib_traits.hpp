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


#ifndef __FILIB_TRAITS_HPP__
#define __FILIB_TRAITS_HPP__

#include "yalaa_iv.hpp"
#include <assert.h>

namespace yalaa
{
  namespace traits
  {
    namespace details
    {
      template<typename T>
      bool my_is_nan(T t)
      {
#ifdef _MSC_VER
        return _isnan(t);
#else
        return isnan(t);
#endif
      }

      template<typename T>
      bool my_is_infinity(T t)
      {
#ifdef _MSC_VER
        return !_finite(t);
#else
        return isinf(t);
#endif
      }
    }


#define YALAA_FILIB_TRAITS(BASE)  template<>                            \
    struct interval_traits<filib::interval<BASE> >                      \
    {                                                                   \
      typedef filib::interval<BASE> base_t;                             \
      typedef BASE iv_base_t;                                           \
                                                                        \
      static base_t my_zero()                                           \
      {                                                                 \
        return base_t(0.0, 0.0);                                        \
      }                                                                 \
                                                                        \
      static base_t my_one()                                            \
      {                                                                 \
        return base_t(1.0, 1.0);                                        \
      }                                                                 \
                                                                        \
      static base_t my_exp(const base_t &i)                             \
      {                                                                 \
        return exp(i);                                                  \
      }                                                                 \
      static base_t my_exp2(const base_t &i)                            \
      {                                                                 \
        return exp2(i);							\
      }                                                                 \
                                                                        \
      static base_t my_exp10(const base_t &i)                           \
      {                                                                 \
        return exp(i);							\
      }                                                                 \
                                                                        \
      static base_t my_expm1(const base_t &i)                           \
      {                                                                 \
        return expm1(i);                                                \
      }                                                                 \
                                                                        \
      static base_t my_exp2m1(const base_t &i)                          \
      {                                                                 \
        return my_exp2(i) - base_t(1.0);				\
      }                                                                 \
                                                                        \
      static base_t my_exp10m1(const base_t &i)                         \
      {                                                                 \
        return my_exp10(i) - base_t(1.0);				\
      }                                                                 \
                                                                        \
      static iv_base_t my_inf(const base_t &i)                          \
      {                                                                 \
        return inf(i);                                                  \
      }                                                                 \
                                                                        \
      static iv_base_t my_sup(const base_t &i)                          \
      {                                                                 \
        return sup(i);                                                  \
      }                                                                 \
                                                                        \
      static base_t my_add(const base_t &i1, const base_t &i2)          \
      {                                                                 \
        return i1 + i2;                                                 \
      }                                                                 \
                                                                        \
      static base_t my_sub(const base_t &i1, const base_t &i2)          \
      {                                                                 \
        return i1 - i2;                                                 \
      }                                                                 \
                                                                        \
      static base_t my_mul(const base_t &i1, const base_t &i2)          \
      {                                                                 \
        return i1*i2;                                                   \
      }                                                                 \
                                                                        \
      static base_t my_div(const base_t &i1, const base_t &i2)          \
      {                                                                 \
        return i1/i2;                                                   \
      }                                                                 \
                                                                        \
      static iv_base_t my_w(const base_t &i)                            \
      {                                                                 \
        return diam(i);                                                 \
      }                                                                 \
                                                                        \
      static iv_base_t my_mid(const base_t &i)                          \
      {                                                                 \
        return mid(i);                                                  \
      }                                                                 \
                                                                        \
      static base_t my_neg(const base_t &i)                             \
      {                                                                 \
        return -i;                                                      \
      }                                                                 \
                                                                        \
      static base_t my_sqr(const base_t &i)                             \
      {                                                                 \
        return sqr(i);                                                  \
      }                                                                 \
                                                                        \
      static base_t my_pow(const base_t &i, int n)                      \
      {                                                                 \
        /*FIX*/                                                         \
        return power(i, n);						\
      }                                                                 \
                                                                        \
      static base_t my_log(const base_t &i)                             \
      {                                                                 \
        return log(i);                                                  \
      }                                                                 \
                                                                        \
      static base_t my_log2(const base_t &i)                            \
      {                                                                 \
        return log2(i);                                                 \
      }                                                                 \
                                                                        \
      static base_t my_log10(const base_t &i)                           \
      {                                                                 \
        return log10(i);                                                \
      }                                                                 \
                                                                        \
      static base_t my_logp1(const base_t &i)                           \
      {                                                                 \
        return log1p(i);                                                \
      }                                                                 \
                                                                        \
      static base_t my_log2p1(const base_t &i)                          \
      {                                                                 \
        return log2(i+base_t(1.0));                                     \
      }                                                                 \
                                                                        \
      static base_t my_log10p1(const base_t &i)                         \
      {                                                                 \
        return log10(i+base_t(1.0));                                    \
      }                                                                 \
                                                                        \
      static iv_base_t my_rad(const base_t &i)                          \
      {                                                                 \
        return diam(i)*0.5;                                             \
      }                                                                 \
                                                                        \
      static base_t my_pi()                                             \
      {                                                                 \
        return filib::interval<iv_base_t>::PI();                        \
      }                                                                 \
                                                                        \
      static base_t my_cos(const base_t &i)                             \
      {                                                                 \
        return cos(i);                                                  \
      }                                                                 \
                                                                        \
      static base_t my_sin(const base_t &i)                             \
      {                                                                 \
        return sin(i);                                                  \
      }                                                                 \
                                                                        \
      static base_t my_sqrt(const base_t& i)                            \
      {                                                                 \
        return sqrt(i);                                                 \
      }                                                                 \
                                                                        \
      static bool is_empty(const base_t &i)                             \
      {                                                                 \
        return my_inf(i) > my_sup(i);                                   \
      }                                                                 \
                                                                        \
      static bool is_special(const base_t &i)                           \
      {                                                                 \
        return is_empty(i) || details::my_is_infinity(my_sup(i)) || details::my_is_infinity(my_inf(i)) || details::my_is_nan(my_inf(i)) || details::my_is_nan(my_sup(i)); \
      }                                                                 \
                                                                        \
      static base_t my_asin(const base_t &i)                            \
      {                                                                 \
        return asin(i);                                                 \
      }                                                                 \
                                                                        \
      static base_t my_acos(const base_t& i)                            \
      {                                                                 \
        return acos(i);                                                 \
      }                                                                 \
                                                                        \
      static base_t my_tan(const base_t& i)                             \
      {                                                                 \
        return tan(i);                                                  \
      }                                                                 \
                                                                        \
      static base_t my_sinh(const base_t& i)                            \
      {                                                                 \
        return sinh(i);                                                 \
      }                                                                 \
                                                                        \
      static base_t my_cosh(const base_t& i)                            \
      {                                                                 \
        return cosh(i);                                                 \
      }                                                                 \
                                                                        \
      static base_t my_tanh(const base_t& i)                            \
      {                                                                 \
        return tanh(i);                                                 \
      }                                                                 \
                                                                        \
      static base_t my_asinh(const base_t& i)                           \
      {                                                                 \
        return asinh(i);                                                \
      }                                                                 \
                                                                        \
      static base_t my_acosh(const base_t& i)                           \
      {                                                                 \
        return acosh(i);                                                \
      }                                                                 \
                                                                        \
      static base_t my_atanh(const base_t& i)                           \
      {                                                                 \
        return atanh(i);                                                \
      }                                                                 \
                                                                        \
      static base_t my_atan(const base_t& i)                            \
      {                                                                 \
        return atan(i);                                                 \
      }                                                                 \
                                                                        \
      static base_t my_powr(const base_t&i, int p, unsigned q)          \
      {                                                                 \
        assert(!"filib++ does not support a n-th root function.");      \
        return base_t(0.0);                                             \
      }                                                                 \
                                                                        \
      static base_t my_rootn(const base_t &i, int q)                    \
      {                                                                 \
        return my_powr(i, q < 0.0 ? -1.0 : 1.0, static_cast<unsigned>(q)); \
      }                                                                 \
    };                                                                  \

    YALAA_FILIB_TRAITS(double)
  }
}



#endif /*__FILIB_TRAITS_HPP__*/

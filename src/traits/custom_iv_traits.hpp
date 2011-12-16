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
 * @file   custom_iv_traits.hpp
 * @author Stefan Kiel <kiel@inf.uni-due.de>
 * @date   Fri Nov  4 14:29:47 2011
 * 
 * @brief  Demo file for using a custom interval library
 * 
 * 
 */


/**
 * \page custom_ivlib Usage of a custom interval library
 * 
 * The configure system can adapt \c YalAA automatically to various interval libraries.
 * However, the internal structure of \c YalAA allows the use of an arbitrary library.
 * To use a not directly supported library please follow these steps:
 * 
 * \section adaptctraits Trait classes
 * \c YalAA accesses underlying interval libraries through a trait class. You have to provide
 * an approbiate specialization for your library. To simplify matters we provided a template
 * file \link custom_iv_traits.hpp \endlink. Please modify this file directly to fit your needs.
 * Make also sure that the \c typedef \c double_iv_t points to your desired interval type.
 * 
 * \section configcustom Configure YalAA
 * After providing the trait classes you are ready for configuring the library.
 * To indicate to the \c configure that you use a custom interval library use the flag 
 * \c --with-custom_ivlib=yes. If your library needs further compiler flags and linker flags specify
 * them as environment variables.<br>
 *  For example, if you wanted to use C-XSC as a custom library the 
 * command line could be:<br> <br>
 * <tt>
 *CPPFLAGS=-I$HOME/libs/cxsc/include LDFLAGS=-L$HOME/libs/cxsc/lib LIBS=-lcxsc ./configure --with-boost=$HOME/libs/boost --with-custom_ivlib=yes 
 *</tt>
 * <br> <br>
 * You are now ready to call \c make to build \c YalAA!<br>
 * 
 */


#ifndef __CUSTOM_TRAITS_HPP__
#define __CUSTOM_TRAITS_HPP__

// Include the headers needed by YOUR library
#include <iosfwd>
#include <interval.hpp>
#include <imath.hpp>

namespace yalaa 
{

  namespace details
  {
    // This needs to be an alias of your interval type
    typedef cxsc::interval double_iv_t;
    // Enable double arithmetic
#define YALAA_HAVE_DOUBLE_IV 1
  }

  namespace traits
  {
    /// Template specialization used for accessing custom types
    /**
     * This template is used for accessing a custom interval library.
     * Please adjust to your needs
     */
    template<>
    struct interval_traits<details::double_iv_t>
    {
      typedef details::double_iv_t base_t;
      typedef double iv_base_t;

      static base_t my_zero() 
	{
	  return base_t(0.0, 0.0);
	}

      static base_t my_one() 
	{
	  return base_t(1.0, 1.0);
	}

      static base_t my_exp(const base_t &i)
	{
	  return exp(i);
	}

      static base_t my_exp2(const base_t &i)
	{
	  // TODO: Thread Safe
	  static details::double_iv_t S_LN_2(ln(base_t(2.0)));
	  return exp(i*S_LN_2);
	}

      static base_t my_exp10(const base_t &i)
	{
	  // TODO: Thread Safe
	  static details::double_iv_t S_LN_10(ln(base_t(10.0)));
	  return exp(i*S_LN_10);
	}

      static base_t my_expm1(const base_t &i)
	{
	  return expm1(i);
	}

      static base_t my_exp2m1(const base_t &i)
	{
	  return my_exp2(i) - 1.0;
	}

      static base_t my_exp10m1(const base_t &i)
	{
	  return my_exp10(i) - 1.0;
	}

      static double my_inf(const base_t &i) 
	{
	  return _double(Inf(i));
	}

      static double my_sup(const base_t &i) 
	{
	  return _double(Sup(i));
	}


      static base_t my_add(const base_t &i1, const base_t &i2) 
	{
	  return i1 + i2;
	}

      static base_t my_sub(const base_t &i1, const base_t &i2)
	{
	  return i1 - i2;
	}

      static base_t my_mul(const base_t &i1, const base_t &i2) 
	{
	  return i1*i2;
	}

      static base_t my_div(const base_t &i1, const base_t &i2) 
	{
	  return i1/i2;
	}

      static iv_base_t my_w(const base_t &i) 
	{
	  return _double(diam(i));
	}

      static iv_base_t my_mid(const base_t &i) 
	{
	  return _double(mid(i));
	}

      static base_t my_neg(const base_t &i)
	{
	  return -i;
	}

      static base_t my_sqr(const base_t &i) 
	{
	  return sqr(i);
	}

      static base_t my_pow(const base_t &i, int n) 
	{
	  return power(i, n);
	}

      static base_t my_log(const base_t &i) 
	{
	  return ln(i);
	}

      static base_t my_log2(const base_t &i) 
	{
	  return log2(i);
	}

      static base_t my_log10(const base_t &i) 
	{
	  return log10(i);
	}

      static base_t my_logp1(const base_t &i) 
	{
	  return lnp1(i);
	}

      static base_t my_log2p1(const base_t &i) 
	{
	  return log2(i+1.0);
	}

      static base_t my_log10p1(const base_t &i) 
	{
	  return log10(i+1.0);
	}

      static iv_base_t my_rad(const base_t &i)
	{
	  // TODO: underflow fixen
	  return _double(diam(i))*0.5;
	}

      // static base_t my_log(const base_t &i)
      // 	{
      // 	  return log10(i);
      // 	}

      static base_t my_pi()
	{
	  return cxsc::Pi();
	}
      
      static base_t my_cos(const base_t &i)
	{
	  return cos(i);
	}
      
      static base_t my_sin(const base_t &i)
	{
	  return sin(i);
	}

      static base_t my_sqrt(const base_t& i)
	{
	  return sqrt(i);
	}

      static base_t my_asin(const base_t& i)
	{
	  return asin(i);
	}

      static base_t my_acos(const base_t& i)
	{
	  return acos(i);
	}

      static base_t my_tan(const base_t& i)
	{
	  return tan(i);
	}

      static base_t my_sinh(const base_t& i)
	{
	  return sinh(i);
	}

      static base_t my_cosh(const base_t& i)
	{
	  return cosh(i);
	}
      
      static base_t my_tanh(const base_t& i)
	{
	  return tanh(i);
	}

      static base_t my_asinh(const base_t& i)
	{
	  return asinh(i);
	}

      static base_t my_acosh(const base_t& i)
	{
	  return acosh(i);
	}
      
      static base_t my_atanh(const base_t& i)
	{
	  return atanh(i);
	}
      
      static base_t my_atan(const base_t& i)
	{
	  return atan(i);
	}

      static base_t my_powr(const base_t&i, int p, unsigned q) 
	{
	  base_t po(power(i, p));
	  if((q & 0x1) && my_inf(po) < 0) {
	    if(my_sup(po) <= 0)
	      return -sqrt(abs(po), q);
	    base_t r(sqrt(abs(po), q));
	    Inf(r) = -Sup(r);
	    return r;
	  }
	  return sqrt(po,q);
	}
      
      static base_t my_rootn(const base_t &i, int q)
	{
	  return my_powr(i, q < 0.0 ? -1.0 : 1.0, static_cast<unsigned>(q));
	}


      static bool is_empty(const base_t& i)
	{
	  return cxsc::IsEmpty(i);
	}

      static bool is_special(const base_t &i)
	{
	  return is_empty(i) || IsInfinity(Inf(i)) || IsInfinity(Sup(i)) || 
	    IsQuietNaN(Inf(i)) || IsQuietNaN(Sup(i)) || IsSignalingNaN(Inf(i)) || IsSignalingNaN(Sup(i));
	}
    };
  }
}

#endif /*__CUSTOM_TRAITS_HPP__*/

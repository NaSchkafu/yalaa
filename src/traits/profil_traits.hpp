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
 * @file   profil_traits.hpp
 * @author Stefan Kiel <kiel@inf.uni-due.de>
 * @date   Fri Nov  4 10:53:14 2011
 * 
 * @brief  Traits class for accessing the Profil/Bias interval type
 * 
 * 
 */


#ifndef __PROFIL_TRAITS_HPP__
#define __PROFIL_TRAITS_HPP__


namespace yalaa 
{
  namespace traits
  {
    /// Template specialization used for accessing Profil/Bias
    /**
     * This template is used for accessing the Profil/Bias interval library.
     */
    template<>
    struct interval_traits<INTERVAL>
    {
      typedef INTERVAL base_t;
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
	  return Exp(i);
	}

      static base_t my_exp2(const base_t &i)
	{
	  // TODO: Thread Safe
	  static base_t S_LN_2(Log(base_t(2.0)));
	  return Exp(i*S_LN_2);
	}

      static base_t my_exp10(const base_t &i)
	{
	  // TODO: Thread Safe
	  static base_t S_LN_10(Log(base_t(10.0)));
	  return Exp(i*S_LN_10);
	}

      static base_t my_expm1(const base_t &i)
	{
	  return my_exp(i) - 1.0;
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
	  return Inf(i);
	}

      static double my_sup(const base_t &i) 
	{
	  return Sup(i);
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
	  return Diam(i);
	}

      static iv_base_t my_mid(const base_t &i) 
	{
	  return Mid(i);
	}

      static base_t my_neg(const base_t &i)
	{
	  return -i;
	}

      static base_t my_sqr(const base_t &i) 
	{
	  return Sqr(i);
	}

      static base_t my_pow(const base_t &i, int n) 
	{
	  return Power(i, n);
	}

      static base_t my_log(const base_t &i) 
	{
	  return Log(i);
	}

      static base_t my_log2(const base_t &i) 
	{
	  return Log(i)/Log(base_t(2.0, 2.0));
	}

      static base_t my_log10(const base_t &i) 
	{
	  return Log10(i);
	}

      static base_t my_logp1(const base_t &i) 
	{
	  return Log(i+1.0);
	}

      static base_t my_log2p1(const base_t &i) 
	{
	  return my_log2(i+1.0);
	}

      static base_t my_log10p1(const base_t &i) 
	{
	  return Log10(i+1.0);
	}

      static iv_base_t my_rad(const base_t &i)
	{
	  // TODO: underflow fixen
	  return Diam(i)*0.5;
	}

      // static base_t my_log(const base_t &i)
      // 	{
      // 	  return log10(i);
      // 	}

      static base_t my_pi()
	{
	  return ArcCos(base_t(-1.0, -1.0));
	}
      
      static base_t my_cos(const base_t &i)
	{
	  return Cos(i);
	}
      
      static base_t my_sin(const base_t &i)
	{
	  return Sin(i);
	}

      static base_t my_sqrt(const base_t& i)
	{
	  return Sqrt(i);
	}

      static base_t my_asin(const base_t& i)
	{
	  return ArcSin(i);
	}

      static base_t my_acos(const base_t& i)
	{
	  return ArcCos(i);
	}

      static base_t my_tan(const base_t& i)
	{
	  return Tan(i);
	}

      static base_t my_sinh(const base_t& i)
	{
	  return Sinh(i);
	}

      static base_t my_cosh(const base_t& i)
	{
	  return Cosh(i);
	}
      
      static base_t my_tanh(const base_t& i)
	{
	  return Tanh(i);
	}

      static base_t my_asinh(const base_t& i)
	{
	  return ArSinh(i);
	}

      static base_t my_acosh(const base_t& i)
	{
	  return ArCosh(i);
	}
      
      static base_t my_atanh(const base_t& i)
	{
	  return ArTanh(i);
	}
      
      static base_t my_atan(const base_t& i)
	{
	  return Tanh(i);
	}

      static base_t my_powr(const base_t&i, int p, unsigned q) 
	{
	  base_t po(Power(i, p));
	  if((q & 0x1) && my_inf(po) < 0) {
	    if(my_sup(po) <= 0)
	      return -Root(Abs(po), q);
	    base_t r(Root(Abs(po), q));
	    r = base_t(-Sup(r), Sup(r));
	    return r;
	  }
	  return Root(po,q);
	}
      
      static base_t my_rootn(const base_t &i, int q)
	{
	  return my_powr(i, q < 0.0 ? -1.0 : 1.0, static_cast<unsigned>(q));
	}


      static bool is_empty(const base_t& i)
	{
	  return Sup(i) < Inf(i);
	}

      static bool is_special(const base_t &i)
	{
	  return is_empty(i) || base_traits<iv_base_t>::is_special(Inf(i)) ||
	    base_traits<iv_base_t>::is_special(Sup(i));
	}
    };
  }
}

#endif /*__PROFIL_TRAITS_HPP__*/


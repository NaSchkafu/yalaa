#ifndef __CXSC_TRAITS_HPP__
#define __CXSC_TRAITS_HPP__


#include <iosfwd>
#include <interval.hpp>
#include <imath.hpp>

namespace yalaa 
{
  namespace details 
  {
    template<>
    struct base_traits<cxsc::interval>
    {
      typedef cxsc::interval base_t;
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

      static base_t my_ln(const base_t &i) 
	{
	  return ln(i);
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
    };
  }
}

#endif /*__CXSC_TRAITS_HPP__*/

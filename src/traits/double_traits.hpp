#ifndef __DOUBLE_TRAITS_HPP__
#define __DOUBLE_TRAITS_HPP__

namespace yalaa 
{
  namespace details 
  {
    // double specialization
    template<>
    struct base_traits<double>
    {
      static double my_zero() 
	{
	  return 0.0;
	}

      static double my_one() 
	{
	  return 1.0;
	}

      static double my_two()
	{
	  return 2.0;
	}

      static double my_sqrt(double sqr) 
	{
	  return sqrt(sqr);
	}

      static double my_neg(double d) 
	{
	  return -d;
	}

      static bool is_special(double d)
	{
#ifdef _MSC_VER
	  return _isnan || !_finite(d);
#else
	  return isnan(d) || isinf(d);
#endif
	}

      static bool is_infinity(double d)
	{
#ifdef _MSC_VER
	  return !_finite(d);
#else
	  return isinf(d);
#endif
	}

      static bool is_nan(double d)
	{
#ifdef _MSC_VER
		return _isnan(d);
#else
	  return isnan(d);
#endif
	}
    };
  }
}

#endif /*__DOUBLE_TRAITS_HPP__*/

#ifndef __L_DOUBLE_TRAITS_HPP__
#define __L_DOUBLE_TRAITS_HPP__

namespace yalaa 
{
  namespace details 
  {
    // long double specialization
    template<>
    struct base_traits<long double>
    {
      static double my_zero() 
	{
	  return 0.0l;
	}

      static double my_one() 
	{
	  return 1.0l;
	}

      static double my_two()
	{
	  return 2.0l;
	}

      static double my_sqrt(long double sqr) 
	{
	  return sqrt(sqr);
	}

      static double my_neg(long double d) 
	{
	  return -d;
	}
    };
  }
}

#endif /*__L_DOUBLE_TRAITS_HPP__*/

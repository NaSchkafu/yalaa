#ifndef __FLOAT_TRAITS_HPP__
#define __FLOAT_TRAITS_HPP__

namespace yalaa 
{
  namespace details 
  {
    // float specialization
    template<>
    struct base_traits<float>
    {
      static double my_zero() 
	{
	  return 0.0f;
	}

      static double my_one() 
	{
	  return 1.0f;
	}

      static double my_two()
	{
	  return 2.0f;
	}

      static double my_sqrt(float sqr) 
	{
	  return sqrt(sqr);
	}

      static double my_neg(float d) 
	{
	  return -d;
	}
    };
  }
}

#endif /*__FLOAT_TRAITS_HPP__*/

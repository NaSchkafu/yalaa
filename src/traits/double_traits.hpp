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

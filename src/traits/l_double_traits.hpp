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


#ifndef __L_DOUBLE_TRAITS_HPP__
#define __L_DOUBLE_TRAITS_HPP__

namespace yalaa 
{
  namespace details 
  {
    /// Template specialization for using \c long \c double types
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

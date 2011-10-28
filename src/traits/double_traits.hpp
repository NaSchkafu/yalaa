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

#include "helper/fphelper.hpp"

namespace yalaa 
{
  namespace details 
  {
    /// Template specialization for using \c double types
    template<>
    struct base_traits<double>
    {
      typedef double base_t;

      static base_t my_zero() 
	{
	  return 0.0;
	}

      static base_t my_one() 
	{
	  return 1.0;
	}

      static base_t my_two()
	{
	  return 2.0;
	}

      static base_t my_sqrt(base_t sqr) 
	{
	  return sqrt(sqr);
	}

      static base_t my_neg(base_t d) 
	{
	  return -d;
	}

      static bool is_special(base_t d)
	{
#ifdef _MSC_VER
	  return _isnan || !_finite(d);
#else
	  return isnan(d) || isinf(d);
#endif
	}

      static bool is_infinity(base_t d)
	{
#ifdef _MSC_VER
	  return !_finite(d);
#else
	  return isinf(d);
#endif
	}

      static bool is_nan(base_t d)
	{
#ifdef _MSC_VER
		return _isnan(d);
#else
	  return isnan(d);
#endif
	}

      static base_t my_add_up(base_t d1, base_t d2) 
	{
	  // TODO: posteriori Fehlerabschätzung
	  yalaa::fp::RndControl rnd;
	  rnd.upward();
	  return d1+d2;
	}

      static base_t my_sub_up(base_t d1, base_t d2) 
	{
	  // TODO: posteriori Fehlerabschätzung
	  yalaa::fp::RndControl rnd;
	  rnd.upward();
	  return d1-d2;
	}

      static base_t my_add_down(base_t d1, base_t d2) 
	{
	  // TODO: posteriori Fehlerabschätzung
	  yalaa::fp::RndControl rnd;
	  rnd.downward();
	  return d1+d2;
	}

      static base_t my_sub_down(base_t d1, base_t d2) 
	{
	  // TODO: posteriori Fehlerabschätzung
	  yalaa::fp::RndControl rnd;
	  rnd.downward();
	  return d1-d2;
	}

      static base_t my_half_up(base_t d1) 
	{
	  // TODO Underflow
	  return 0.5*d1;
	}

      static base_t my_half_down(base_t d1) 
	{
	  // TODO Underflow
	  return 0.5*d1;
	}
      

      static base_t my_abs(base_t d) 
	{
	  return fabs(d);
	}

      static base_t my_powr(base_t d, int p, unsigned q) 
	{
	  // TODO: bessere Impl?
//	  int sgn = d < 0 && (q & 0x1) ? -1 : 1;
	  base_t po(pow(d, p));
	  int sgn = po < 0 && (q & 0x1) ? -1 : 1;
          return sgn*pow(fabs(d), 1.0/q);
	}

      static base_t my_rootn(base_t d, int q)
	{
	  return my_powr(d, q < 0.0 ? -1.0 : 1.0, static_cast<unsigned>(q));
	}

    };
  }
}

#endif /*__DOUBLE_TRAITS_HPP__*/

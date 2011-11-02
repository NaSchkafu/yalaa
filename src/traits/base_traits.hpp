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


#ifndef __BASE_TRAITS_HPP__
#define __BASE_TRAITS_HPP__

#include <math.h>

namespace yalaa
{
  namespace details
  {
    /// Traits template for adapting \c YalAA to new types
    /**
     * This template defines properties of arithmetic types used in
     * yalaa::AffineForm as base type. Before using a custom type
     * you have to specialize this template.
     *
     * \todo Currently base_traits is used for intervals and the type of partial deviations.
     * Traits for intervals should be defined by a separate class. 
     * 
     * 
     * This documentation does only
     * consider the use as base type. Please refer to cxsc_traits.hpp for the use as interval
     * traits.
     */
    template<typename T>
    struct base_traits
    {
      typedef void base_t;

      /** 
       * Returns 0 
       * 
       * 
       * @return zero representation
       */
      static base_t my_zero()
        {
	  
        }

      /** 
       * Return 1 
       * 
       * 
       * @return one representation
       */
      static base_t my_one()
        {
          
        }

      /** 
       * Returns 2
       * 
       * 
       * @return two representation
       */
      static base_t my_two()
        {
          
        }

      /** 
       * Negation
       * 
       * @param d  argument
       * 
       * @return negation of d
       */
      static base_t my_neg(base_t d)
        {     }

      /** 
       * Checks for a special value
       * 
       * @param d argument to check
       * 
       * @return true if d is a special value
       */
      static bool is_special(base_t d)
        {
        }

      /** 
       * Returns a special value (no numerical value)
       * 
       * 
       * @return special value
       */
      static base_t special()
        {  }

      /** 
       * Adds two number with upward rounding (if required)
       * 
       * @param d1 operand 1
       * @param d2 operand 2
       * 
       * @return d1 + d2
       */
      static base_t my_add_up(base_t d1, base_t d2)
        {  }

      /** 
       * Subtracts two numbers with upward rounding (if required)
       * 
       * @param d1 operand 1
       * @param d2 operand 2
       * 
       * @return d1 - d2
       */
      static base_t my_sub_up(base_t d1, base_t d2)
        {     }

      /** 
       * Adds two numbers with downward rounding (if required)
       * 
       * @param d1 operand 1
       * @param d2 operand 2
       * 
       * @return d1 + d2
       */
      static base_t my_add_down(base_t d1, base_t d2)
        {      }

      /** 
       * Subtracts two numbers with downward rounding (if required)
       * 
       * @param d1 operand 1
       * @param d2 operand 2
       * 
       * @return d1 + d2
       */
      static base_t my_sub_down(base_t d1, base_t d2)
        {    }

      /** 
       * Halves a number with upward rounding (if required)
       * 
       * @param d1 argument
       * 
       * @return \f$\frac{d1}{2}\f$
       */
      static base_t my_half_up(base_t d1)
        {        }

      /** 
       * Halves a number with downward rounding (if required)
       * 
       * @param d1 argument
       * 
       * @return \f$\frac{d1}{2}\f$
       */
      static base_t my_half_down(base_t d1)
        {
          return 0.5*d1;
        }


      /** 
       * Absolute value of a number
       * 
       * @param d argument
       * 
       * @return |d|
       */
      static base_t my_abs(base_t d)
        {        }
    };
  }
}

#endif

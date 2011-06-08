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


#ifndef __ARITHMETICERROR_HPP__
#define __ARITHMETICERROR_HPP__

#include <boost/type_traits.hpp>
#include <boost/mpl/if.hpp>
#include "yalaa_assert.hpp"

namespace yalaa 
{
  namespace details 
  {
    /// Describes the error of an arithmetic operation
    /**
     * In affine arithmetic operations are subject to errors
     * The errors are split into a signed error, an unsigned error and a general.
     * (Erklärung einfügen AF1, AF2, AF, Messine, wie QF Formen behandeln?)
     */
    template<typename T>
    class ArithmeticError  
    {
    public:
      typedef T base_t;
      typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename 
				       boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;   
      
      
      enum ERROR_TYPE {POS_ERR, NEG_ERR, GEN_ERR };
      enum kerror_t { DISCONT = 1, UNBOUND = 2, P_D_VIOL = 4, C_D_VIOL = 8, 
		      OFLOW = 16, I_ERROR = 32 };

      /** 
       * Ctor
       * Constructs a new ArithmeticError object with a general error. 
       * The sum is automatically set to gen.
       * 
       * @param gen general error
       */
      ArithmeticError(base_ref_t gen, unsigned error);


      /** 
       * Ctor
       * Constructs a new ArithmeticError object
       * 
       * @param gen general error
       * @param pos positive error
       * @param neg negative error
       * @param sum sum of errors
       * @param error flags
       */
      ArithmeticError(base_ref_t gen, base_ref_t pos, base_ref_t neg, 
		      base_ref_t sum, unsigned error);

      /** 
       * Ctor
       * Constructs a new ArithmeticError object
       * The sum is calculated by ArithmeticError using the base_traits<base_t>::add_up function
       * 
       * @param gen general error
       * @param pos positive error
       * @param neg negative error
       * @param error flags
       */
      ArithmeticError(base_ref_t gen, base_ref_t pos, base_ref_t neg, unsigned error);
      
      /** 
       * Gets the sum off all errors
       * 
       * 
       * @return error sum
       */
      inline base_t sum() const;

      /** 
       * Gets the positive error
       * 
       * 
       * @return positive errors
       */
      inline base_t pos() const;
      
      /** 
       * Gets the negative error
       * 
       * 
       * @return negative errors
       */
      inline base_t neg() const;
      
      /** 
       * Gets the general error
       * 
       * 
       * @return general error
       */
      inline base_t gen() const;

      /** 
       * Gets the error flags bitmask
       * 
       * 
       * @return error flags
       */
      inline unsigned error() const;
      
      
    private:
      T m_gen;
      T m_pos;
      T m_neg;
      T m_sum;
      unsigned m_error;
    };

    #include "arithmeticerror.inl"

  }
}

#endif /*__ARITHMETICERROR_HPP__*/


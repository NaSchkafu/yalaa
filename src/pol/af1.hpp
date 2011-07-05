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
 * @file   af1.hpp
 * @author Stefan Kiel <kiel@inf.uni-due.de>
 * @date   Mon Jul  4 12:38:23 2011
 * 
 * @brief  Provides the AF1 model (Messine, 2002)
 * 
 * 
 */


#ifndef __AF1_HPP__
#define __AF1_HPP__

#include "kernel/arithmeticerror.hpp"

namespace yalaa
{
  namespace pol
  {
    // T Basis
    // ET<T> ErrorTerm
    // AC<T, ET<T> > AffComb
    /// Implements the handling of approximation/rounding errors as in the extended model AF1 (Messine, 2002)
    /**
     * Rounding/approximation errors and uncertainty are added 
     * to the same term, which is treated independently and does not model an affine dependency
     * between forms. New noise symbols are only introduced in the computation process
     * by creating a new affine form.  
     */
    template<typename T, template<typename> class ET, 
	     template<typename, template<typename> class> class AC>
    class AF1
    {
    public:
      typedef T base_t;
      typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;
 
     /// Called for adding errors (approximation, rounding errors, ...)
      /** 
       * In AF1 this adds a new independet error symbol for the error's sum
       * 
       * @param ac affine combination
       * @param err error
       */
      static void add_errors(AC<T, ET> *ac, const yalaa::details::ArithmeticError<T> &err)
        {
	  if(err.sum() != yalaa::details::base_traits<base_t>::my_zero())
	    ac->insert(typename AC<T, ET>::error_t(err.sum()));
        }

      /// Called for creating by creating a new affine form
      /** 
       * In AF1 this adds a new independet error symbol with the specified uncertainty
       * 
       * @param ac affine combination
       * @param uncert uncertainty
       */
      static void new_form(AC<T, ET> *ac, base_ref_t uncert) 
	{
	  ac->insert(typename AC<T,ET>::error_t(uncert));
	}

      /// Called for introducing uncertainty into an existing form
      /** 
       * In AF1 this acts as new_form, i.e. introducing a new independet error symbol with the
       * specified uncertainty
       * 
       * @param ac affine combination
       * @param uncert uncertainty
       */
      static void add_uncert(AC<T, ET> *ac, base_ref_t uncert)
	{
	  ac->insert(typename AC<T,ET>::error_t(uncert));
	}

    };
  }
}


#endif /*__AF1_HPP__*/

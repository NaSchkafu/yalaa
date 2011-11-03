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
 * @file   af0.hpp
 * @author Stefan Kiel <kiel@inf.uni-due.de>
 * @date   Mon Jul  4 12:38:23 2011
 * 
 * @brief  Provides the standard affine policy for uncertainty handling
 * 
 * 
 */


#ifndef __AF0_HPP__
#define __AF0_HPP__

#include "kernel/arithmeticerror.hpp"

namespace yalaa
{
  namespace pol
  {
    // T Basis
    // ET<T> ErrorTerm
    // AC<T, ET<T> > AffComb
    /// Affine policy for standard affine arithmetic
    /**
     * This policy class reassembles the original affine model as proposed by Stolfi et al.
     * Rounding and approximation errors are added in form of new independet terms to the affine
     * form. Introduction of uncertainty also yields a new noise symbol as introduction of a new
     * affine form does. 
     */
    template<typename T, template<typename> class ET, 
	     template<typename, template<typename> class> class AC>
    class AF0
    {
    public:
      typedef T base_t;
      typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;
      typedef yalaa::traits::base_traits<base_t> b_traits_t;

      /// Called for adding errors (approximation, rounding errors, ...)
      /** 
       * In AF0 this adds a new independet error symbol for the error's sum
       * 
       * @param ac affine combination
       * @param err error
       */
      inline static void add_errors(AC<T, ET> *ac, const yalaa::details::ArithmeticError<T> &err);

      /// Called for creating by creating a new affine form
      /** 
       * In AF0 this adds a new independet error symbol with the specified uncertainty
       * 
       * @param ac affine combination
       * @param uncert uncertainty
       */
      inline static void new_form(AC<T, ET> *ac, base_ref_t uncert);
      
      /// Called for introducing uncertainty into an existing form
      /** 
       * In AF0 this acts as new_form, i.e. introducing a new independet error symbol with the
       * specified uncertainty
       * 
       * @param ac affine combination
       * @param uncert uncertainty
       */
      inline static void add_uncert(AC<T, ET> *ac, base_ref_t uncert);
    };

    #include "af0.inl"
  }
}


#endif /*__AF0_HPP__*/

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
 * @file   af2.hpp
 * @author Stefan Kiel <kiel@inf.uni-due.de>
 * @date   Mon Jul  4 12:38:23 2011
 * 
 * @brief  Provides the AF2 model (Messine, 2002)
 * 
 * 
 */


#ifndef __AF2_HPP__
#define __AF2_HPP__

#include "kernel/arithmeticerror.hpp"
#include "specialterms.hpp"

namespace yalaa
{
  namespace pol
  {
    /// Affine policy for the extended model AF2
    /**
     * Reassembles the extended affine model AF2 as described in (Messine, 2002).
     * Rounding/approximation errors and uncertainty are added 
     * to three terms modeling positive, negative and general errors, which are treated independently 
     * and do not model an affine dependency between forms. New noise symbols are only introduced in
     * the computation process by creating a new affine form.  
     * 
     * \bug Currently the AF2 policy is not supported by AffineCombImpl. 
     */
    template<typename T, template<typename> class ET, 
	     template<typename, template<typename> class> class AC>
    class AF2
    {
    public:
      typedef T base_t;
      typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;
      typedef ET<base_t> error_t;
      typedef AC<base_t, ET> ac_t;
      typedef yalaa::traits::base_traits<base_t> b_traits_t;

     /// Called for adding errors (approximation, rounding errors, ...)
      /** 
       * In AF2 this adds all errors to special terms for positive, negative and unsigned errors
       * 
       * @param ac affine combination
       * @param err error
       */
      static inline void add_errors(AC<T, ET> *ac, const yalaa::details::ArithmeticError<T> &err);
      

      /// Called for creating by creating a new affine form
      /** 
       * In AF1 this adds a new independet error symbol with the specified uncertainty
       * 
       * @param ac affine combination
       * @param uncert uncertainty
       */
      inline static void new_form(AC<T, ET> *ac, base_ref_t uncert);
      
      /// Called for introducing uncertainty into an existing form
      /** 
       * In AF1 this acts as new_form, i.e. introducing a new independet error symbol with the
       * specified uncertainty
       * 
       * @param ac affine combination
       * @param uncert uncertainty
       */
      inline static void add_uncert(AC<T, ET> *ac, base_ref_t uncert);
      
    private:
      inline static void add_special(AC<T, ET> *ac, base_ref_t uncert, 
			      yalaa::details::SpecialErrTerm::special_t type);
	
    };

    #include "af2.inl"

  }
}


#endif /*__AF2_HPP__*/

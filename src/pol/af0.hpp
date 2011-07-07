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
    /// Implements the handling of approximation/rounding errors as in standard affine arithmetic
    /**
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
      typedef yalaa::details::base_traits<base_t> b_traits_t;

      /// Called for adding errors (approximation, rounding errors, ...)
      /** 
       * In AF0 this adds a new independet error symbol for the error's sum
       * 
       * @param ac affine combination
       * @param err error
       */
      static void add_errors(AC<T, ET> *ac, const yalaa::details::ArithmeticError<T> &err)
        {
	  T errn(err.gen());
	  // Scaling Pos Fehler
	  if(err.pos() != b_traits_t::my_zero()) {
	    base_t errn_p(b_traits_t::my_half_up(err.pos()));
	    base_t nc(b_traits_t::my_add_up(ac->central(), errn_p));
	    errn = b_traits_t::my_add_up(errn, b_traits_t::my_sub_up(nc,b_traits_t::my_add_down(ac->central(), b_traits_t::my_half_down(err.pos()))));
	    errn = b_traits_t::my_add_up(errn, errn_p);
	    ac->set_central(nc);
	  }
	  if(err.neg() != b_traits_t::my_zero()) {
	    base_t errn_n(b_traits_t::my_half_up(err.neg()));
	    base_t nc(b_traits_t::my_sub_up(ac->central(), errn_n));
	    errn = b_traits_t::my_add_up(errn, b_traits_t::my_sub_up(nc, b_traits_t::my_sub_down(ac->central(), b_traits_t::my_half_down(err.neg()))));
	    errn = b_traits_t::my_add_up(errn, errn_n);
	    ac->set_central(nc);
	  }

	  std::cout << errn << std::endl;

	  if(errn != b_traits_t::my_zero())
	    ac->insert(typename AC<T, ET>::error_t(errn));
        }

      /// Called for creating by creating a new affine form
      /** 
       * In AF0 this adds a new independet error symbol with the specified uncertainty
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
       * In AF0 this acts as new_form, i.e. introducing a new independet error symbol with the
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


#endif /*__AF0_HPP__*/

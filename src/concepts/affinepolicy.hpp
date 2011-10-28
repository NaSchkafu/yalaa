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
 * @file   affinepolicy.hpp
 * @author Stefan Kiel <kiel@inf.uni-due.de>
 * @date   Mon Jul  4 12:38:23 2011
 * 
 * @brief  Provides a structure describing the AffinePolicy concept
 */

namespace yalaa
{
  namespace concepts
  {
    /// Concept for managing approximation errors, uncertainties and new variables
    /**
     * This policy class reassembles the original affine model as proposed by Stolfi et al.
     * Rounding and approximation errors are added in form of new independet terms to the affine
     * form. Introduction of uncertainty also yields a new noise symbol as introduction of a new
     * affine form does. 
     * 
     * @param T Type for partial deviations 
     * @param ET Implementation of the ErrorTerm concept to use 
     * @param AC Implementation of the AffineCombination concept to use
     */
    template<typename T, template<typename> class ET, 
	     template<typename, template<typename> class> class AC>
    struct AffinePolicy
    {
    public:
      /// Type for partial deviations
      typedef T base_t;
      /// Const reference or base_t depending whether base_t is a fundamental type. 
      typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;
      /// Traits for base_t
      typedef yalaa::details::base_traits<base_t> b_traits_t;

      /** 
       * This function is called after performing an operation trough ArithmeticKernel.
       * It is responsible for adding the non-affine approximation/rounding errors to
       * the combination.
       * 
       * @param ac affine combination to manipulate
       * @param err error
       */
      static void add_errors(AC<T, ET> *ac, const yalaa::details::ArithmeticError<T> &err);

      /** 
       * This function is called if a new affine form is created, that is
       * a new independent variable is introduced into the computation process.
       * 
       * @param ac affine combination to manipulate
       * @param uncert uncertainty
       */
      void new_form(AC<T, ET> *ac, base_ref_t uncert);
      
      /** 
       * This function is called if new uncertainty is introduced into the
       * computation process. For example, if the affine form is combined with
       * an interval.
       * 
       * @param ac affine combination to manipulate
       * @param uncert uncertainty
       */
      void add_uncert(AC<T, ET> *ac, base_ref_t uncert);
    };
  }
}



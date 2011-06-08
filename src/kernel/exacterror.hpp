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


#ifndef __EXACTERROR_HPP__
#define __EXACTERROR_HPP__

#include <limits>

#include "arithmeticerror.hpp"

#include "aff/exacterroraffinefp.hpp"
#include "nonaff/mulfp.hpp"
#include "nonaff/minrangefp.hpp"
#include "nonaff/chebyshevfp.hpp"

namespace yalaa
{
  namespace kernel
  {
    // Dummy Template
    /// This template impelements the original affine arithmetic approach by Stolfi et al
    /**
     * The affine arithmetic operations provided by this template are full verified and use
     * the error determination approach by Stolfi et al. Basically the exact floating-point
     * error is computed in each step. This produces tight enclosures but is rather slow, as
     * many rounding moding changes are necessary.
     * You have to specialize this template for concrete base types T. A specialization is
     * provided for IEEE754 double
     */
    // template<typename T, template<typename T, template<typename> class ET> class AC,
    //          template<typename> class ET>
    //   template<typename T, template<typename> class ET, 
    // 	     template<typename, template<typename> class> class AC, class IV>
    // class ExactError
    // {
    //   // TODO: In Konzept verschieben
    //   typedef int aerror_t;
    //   typedef int ac_t;

    //   /**
    //    * Adds to affine forms and stores the result in ac1 (ac1 += ac2)
    //    *
    //    *
    //    * @param ac1 first form
    //    * @param ac2 second form
    //    *
    //    * @return error bounds
    //    */
    //   static aerror_t add(ac_t *ac1, const ac_t& ac2);

    //   /**
    //    * Substracts to affine forms and stores the result in ac1 (ac1 -= ac2)
    //    *
    //    * @param ac1 first form
    //    * @param ac2 second form
    //    *
    //    * @return error bounds
    //    */
    //   static aerror_t sub(ac_t *ac1, const ac_t& ac2);

    //   /**
    //    * Adds a scalar to an affine form (ac += s)
    //    *
    //    * @param ac affine form
    //    * @param s scalar
    //    *
    //    * @return error bounds
    //    */
    //   static aerror_t add(ac_t *ac, double s);

    //   /**
    //    * Multiplies an affine form with a scalar (ac *= s)
    //    *
    //    * @param ac affine form
    //    * @param s scalar
    //    *
    //    * @return error bounds
    //    */
    //   static aerror_t mul(ac_t *ac, double s);


    //   /**
    //    * Calculates square root for an affine form
    //    * For this the domain of ac is required in interval form
    //    * The result is stored in ac
    //    *
    //    * @param ac affine form
    //    * @param dlow Lower bound of domain
    //    * @param dhigh Upper bound of domain
    //    *
    //    * @return error bound
    //    */
    //   static aerror_t sqrt(ac_t *ac, T dlow, T dhigh);


    //   /**
    //    * Multiplication of two affine forms
    //    *
    //    * @param ac1
    //    * @param ac2
    //    *
    //    * @return error bounds
    //    */
    //   static aerror_t mul(ac_t *ac1, ac_t *ac2);

    //   /**
    //    * Exponential functions (ac = e^ac)
    //    *
    //    * @param ac affine form
    //    * @param dlow Lower bound of domain
    //    * @param dhigh Upper bound of domain
    //    *
    //    * @return error bounds
    //    */
    //   static aerror_t exp(ac_t *ac, double dlow, double dhigh);

    //   /**
    //    * Natural logarithm (base e) (ac = ln(ac))
    //    *
    //    * @param ac affine form
    //    * @param dlow Lower bound of domain
    //    * @param dhigh Upper bound of domain
    //    *
    //    * @return error bounds
    //    */
    //   static aerror_t ln(ac_t *ac, double dlow, double dhigh);

    //   /**
    //    * Logarithm (base 10) (ac = log(ac))
    //    *
    //    * @param ac affine form
    //    * @param dlow Lower bound of domain
    //    * @param dhigh Upper bound of domain
    //    *
    //    * @return error bounds
    //    */
    //   static aerror_t log(ac_t *ac, double dlow, double dhigh);

    //   /**
    //    * Square function (ac = ac^2)
    //    *
    //    * @param ac affine form
    //    * @param dlow Lower bound of domain
    //    * @param dhigh Upper bound of domain
    //    *
    //    * @return error bounds
    //    */
    //   static aerror_t sqr(ac_t *ac, double dlow, double dhigh);
    // };

    template<typename T, template<typename> class ET, 
	     template<typename, template<typename> class> class AC, class IV>
    struct ExactErrorFP : public details::ExactErrorAffineFP<T, ET, AC>,
			  public details::MinRangeBuiltInFP<T, ET, AC, details::ExactErrorAffineFP<T, ET,AC> >,
			  public details::MinRangeFP<T, ET, AC, details::ExactErrorAffineFP<T, ET,AC>, IV>,
			  public details::MultiplicationFP<T, ET, AC, details::ExactErrorAffineFP<T, ET, AC>, IV>,
			  public details::ChebyshevFP<T, ET, AC, details::ExactErrorAffineFP<T, ET, AC>, IV>
    {
    public:
      typedef ET<T> error_t;
      typedef AC<T, ET> ac_t;
      typedef yalaa::details::ArithmeticError<T> aerror_t;
      typedef ExactErrorFP<T, ET, AC, IV> self_t;
    };
  }
}




#endif /*__EXACTERROR_HPP__*/


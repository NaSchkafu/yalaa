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
 * @file   exacterror.hpp
 * @author Stefan Kiel <kiel@inf.uni-due.de>
 * @date   Fri Oct 28 11:05:31 2011
 * 
 * @brief  Provides the ExactErrorFP structure implementing the ArithmeticKernel concept for FP math
 * 
 * 
 */


#ifndef __EXACTERROR_HPP__
#define __EXACTERROR_HPP__

#include <limits>

#include "arithmeticerror.hpp"

#include "aff/exacterroraffinefp.hpp"
#include "nonaff/mulfp.hpp"
#include "nonaff/minrangefp.hpp"
#include "nonaff/chebyshevfp.hpp"
#include "nonaff/miscfp.hpp"

namespace yalaa
{
  /// Namespace for ArithmeticKernel implementations and associated classes
  namespace kernel
  {
    /// FP implementation of the ArithmeticKernel concept
    /**
     * This structure combines the ExactErrorAffineFP, MinRangeBuiltInFP, MinRangeFP, 
     * MultiplicationFP and ChebyshevFP structure to create a complete implementation
     * of the ArithmeticKernel concept. As its components it requires a IEEE754 base type.
     * 
     */
    template<typename T, template<typename> class ET, 
	     template<typename, template<typename> class> class AC, class IV>
    struct ExactErrorFP : public details::ExactErrorAffineFP<T, ET, AC>,
			  public details::MinRangeBuiltInFP<T, ET, AC, details::ExactErrorAffineFP<T, ET,AC> >,
			  public details::MinRangeFP<T, ET, AC, details::ExactErrorAffineFP<T, ET,AC>, IV>,
			  public details::MultiplicationFP<T, ET, AC, details::ExactErrorAffineFP<T, ET, AC>, IV>,
			  public details::ChebyshevFP<T, ET, AC, details::ExactErrorAffineFP<T, ET, AC>, IV>,
      			  public details::MiscFP<T, ET, AC, details::ExactErrorAffineFP<T, ET, AC>, IV>
    {
    public:
      typedef ET<T> error_t;
      typedef AC<T, ET> ac_t;
      typedef yalaa::details::ArithmeticError<T> aerror_t;
      typedef ExactErrorFP<T, ET, AC, IV> self_t;
      typedef IV iv_t;
      typedef yalaa::traits::interval_traits<iv_t> iv_traits;

      // Waehlt konkrete Funktion aus der rationalen Potenzfunktion aus
      static aerror_t powr(ac_t *ac, iv_t d, int p, unsigned q);
      static aerror_t rootn(ac_t *ac, iv_t d, int q);

      static aerror_t inv(ac_t *ac, const iv_t &d);
    };
  }
}




#endif /*__EXACTERROR_HPP__*/


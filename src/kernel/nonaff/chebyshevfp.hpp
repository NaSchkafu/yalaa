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


#ifndef __CHEBYSHEVFP_HPP__
#define __CHEBYSHEVFP_HPP__

#include <functional>

namespace yalaa 
{
  namespace kernel 
  {
    namespace details 
    {
      /// Floating-point Chebyshev approximations for non-affine operations
      /**
       * This structure adds support for non-affine operations which are
       * differentiable, but not strictly convex or concave in their domain
       * so that neither the MinRange nor the optimal affine Chebyshev approximations
       * proposed by de Figuerido and Stolfi is applicable.
       * 
       * The affine approximation is calcuated through interpolation at the Chebyshev nodes
       * x_k = cos(PI(2k+1)/(2+2)). A verified enclosure is obtained with the Lagrange-Remainder and
       * the use of interval analysis. (cf. Implementation Manual for details on the method) 
       */
      template<typename T, template<typename> class ET, 
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      struct ChebyshevFP
      {
	typedef ET<T> error_t;
	typedef AC<T, ET> ac_t;
	typedef yalaa::details::ArithmeticError<T> aerror_t;
	typedef AFFOP aff_op_t;
	typedef IV iv_t;
	typedef yalaa::details::base_traits<iv_t> iv_traits;
	typedef ChebyshevFP<T, ET, AC, AFFOP, IV> self_t;

	static aerror_t sin(ac_t *ac, const iv_t &d);
	static aerror_t cos(ac_t *ac, const iv_t &d);
	static aerror_t tan(ac_t *ac, const iv_t &d);

	static aerror_t asin(ac_t *ac, const iv_t &d);
	static aerror_t acos(ac_t *ac, const iv_t &d);
	static aerror_t atan(ac_t *ac, const iv_t &d);

	static aerror_t sinh(ac_t *ac, const iv_t &d);
	static aerror_t tanh(ac_t *ac, const iv_t &d);

	static aerror_t asinh(ac_t *ac, const iv_t &d);
	static aerror_t atanh(ac_t *ac, const iv_t &d);

      private:
	/** 
	 * Calculates an affine chebyshev interpolation
	 * 
	 * @param ac affine combination
	 * @param d ac's domain
	 * @param f function to approximate
	 * @param odd true if f is odd
	 * @param ddf function for determining the approximation error
	 * 
	 * @return error bounds and flags
	 */
	static aerror_t chebyshev(ac_t *ac, const iv_t &d, iv_t (*f)(const iv_t&), bool odd, 
				  std::function<T (const iv_t&, const iv_t&)>, yalaa::fp::RndControl &rnd);

	/** 
	 * Lagrange Remainder
	 * 
	 * @param d domain
	 * @param bdf bound on derivative on d
	 * 
	 * @return upper bound on approximation error
	 */
	static T lag_rem(const iv_t &d, const iv_t& bdf );

	static short sgn(T s);

	static T eval_poly_lb(T lbc0, T lbc1, T lbx);

	/** 
	 * Calculates acos and asin
	 * 
	 * @param ac affine combination
	 * @param d domain
	 * @param is_acos flag to determine function
	 * 
	 * @return error bounds and flags
	 */
	static aerror_t acos_asin(ac_t *ac, iv_t d, bool is_acos);

	// static iv_t sin(const iv_t&);
	// static iv_t dx_asin(const iv_t&i);
	// static iv_t dx_acos(const iv_t&i);

	// static const iv_t S_X[][2];
	// static const T S_PINF;
	// static const T S_PSUP;
      };
    }
  }
}


#endif /*__CHEBYSHEVFP_HPP__*/

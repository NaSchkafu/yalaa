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

namespace yalaa 
{
  namespace kernel 
  {
    namespace details 
    {
      /// Chebyshev approximation for non-affine operations
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

	static aerror_t sin(ac_t *ac, const iv_t &d);
	static aerror_t cos(ac_t *ac, const iv_t &d);

	static aerror_t asin(ac_t *ac,  iv_t d);
	static aerror_t acos(ac_t *ac, iv_t d);

	//static void init();

      private:
	/** 
	 * Calculates an affine chebyshev interpolation
	 * 
	 * @param ac affine combination
	 * @param d ac's domain
	 * @param f function to approximate
	 * @param odd true if f is odd
	 * @param ddf second derivative of f ifnot odd, third derivative otherwise
	 * 
	 * @return error bounds
	 */
	static aerror_t chebyshev(ac_t *ac, const iv_t &d, iv_t (*f)(const iv_t&), bool odd, iv_t (*ddf)(const iv_t&), yalaa::fp::RndControl &rnd);

	static short sgn(T s);
	static iv_t neg_sin(const iv_t&);
	static iv_t dx_asin(const iv_t&i);
	static iv_t dx_acos(const iv_t&i);

	// static const iv_t S_X[][2];
	// static const T S_PINF;
	// static const T S_PSUP;
      };
    }
  }
}


#endif /*__CHEBYSHEVFP_HPP__*/

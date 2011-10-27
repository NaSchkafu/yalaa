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
 * @file   arithmetickernel.hpp
 * @author Stefan Kiel <kiel@inf.uni-due.de>
 * @date   Thu Oct 27 16:03:52 2011
 *
 * @brief  Structure describing the ArithmeticKernel concept
 *
 *
 */


namespace yalaa
{
  namespace concepts
  {
    /// Concept defining the arithmetic kernel
    /**
     * The ArithmeticKernel concept provides all operations and elementary functions
     * provided by \c YalAA. It performs the affine part of the operation using the
     * elementary affine operations provided by AffineCombination. Furthermore, ArithmeticKernel
     * provides error bounds on the non-affine part of the operations and propagates them
     * and further informations like domain-violations etc. through the ArithmeticError class
     * to the higher layers of \c YalAA.
     *
     * You have to provide an implementation of this class, if you want to use \c YalAA with custom
     * types.
     *
     * @param T Type for partial deviations
     * @param ET Implementation of the ErrorTerm concept to use
     * @param AC Implementation of the AffineCombination concept to use
     * @param IV Interval type to use
     */
    template<typename T, template<typename> class ET,
             template<typename, template<typename> class> class AC, class IV>
    struct ArithmeticKernel
    {
    public:
      /// Type for partial deviations
      typedef T base_t;
      /// Type for error terms
      typedef ET<T> error_t;
      /// Type for affine combinations
      typedef AC<T, ET> ac_t;
      /// Type of the ArithmeticError template
      typedef yalaa::details::ArithmeticError<T> aerror_t;
      /// Type of *this
      typedef ArithmeticError<T, ET, AC, IV> self_t;
      /// Type of interval type
      typedef IV iv_t;
      /// Type of interval traits for IV
      typedef yalaa::details::base_traits<iv_t> iv_traits;

      /**
       * Calculates \f$ac = ac^{\frac p q}\f$
       *
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * @param p numerator of exponent
       * @param q denominator of exponent
       *
       * @return error bounds
       */
      static aerror_t powr(ac_t *ac, iv_t d, int p, unsigned q);

      /**
       * Calculates \f$ac = \sqrt[q]{ac}\f$
       *
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * @param q n
       *
       * @return error bounds
       */
      static aerror_t rootn(ac_t *ac, iv_t d, int q);

      /**
       * Inverse of an affine combination
       *
       * @param ac affine combination to manipulate
       * @param d domain of ac
       *
       * @return error bounds
       */
      static aerror_t inv(ac_t *ac, const iv_t &d);

      /**
       * Calculates \f$ac1 += ac2\f$
       *
       * @param ac1 affine combination to manipulate
       * @param ac2 affine combination to add
       *
       * @return error bounds
       */
      static aerror_t add(ac_t *ac1, const ac_t& ac2);

      /**
       * Calculates \f$ac1 -= ac2\f$
       *
       * @param ac1 affine combination to manipulate
       * @param ac2 affine combination
       *
       * @return error bounds
       */
      static aerror_t sub(ac_t *ac1, const ac_t& ac2);

      /**
       * Calculates \f$ac += s\f$
       *
       * @param ac affine combination to manipulate
       * @param s translation
       *
       * @return error bounds
       */
      static aerror_t add(ac_t *ac, T s);

      /**
       * Calculates \f$ac *= s\f$
       *
       * @param ac affine combination to manipulate
       * @param s scaling
       *
       * @return error bounds
       */
      static aerror_t scale(ac_t *ac, T s);

      /**
       * Calculates \f$ac /= s\f$
       *
       * @param ac affine combination to manipulate
       * @param s inverse scaling factor
       *
       * @return error bounds
       */
      static aerror_t inv_scale(ac_t *ac, T s);

      /**
       * Negates an affine form
       *
       * @param ac affine combination to manipulate
       *
       * @return error bounds
       */
      static aerror_t neg(ac_t *ac);

      /** 
       * Sine of an affine combination
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return error bounds
       */
      static aerror_t sin(ac_t *ac, const iv_t &d);

      /** 
       * Cosine of an affine combination
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return affine combination
       */
      static aerror_t cos(ac_t *ac, const iv_t &d);

      /** 
       * Tangent of an affine combination
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return affine combination
       */
      static aerror_t tan(ac_t *ac, const iv_t &d);

      /** 
       * Inverse sine of an affine combination
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return affine combination
       */
      static aerror_t asin(ac_t *ac, const iv_t &d);

      /** 
       * Inverse cosine of an affine combination
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return affine combination
       */
      static aerror_t acos(ac_t *ac, const iv_t &d);

      /** 
       * Inverse tangent of an affine combination
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return affine combination
       */
      static aerror_t atan(ac_t *ac, const iv_t &d);

      /** 
       * Hyperbolic sine of an affine combination
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return affine combination
       */
      static aerror_t sinh(ac_t *ac, const iv_t &d);

      /** 
       * Hyperbolic tangent of an affine combination
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return affine combination
       */
      static aerror_t tanh(ac_t *ac, const iv_t &d);

      /** 
       * Area hyperbolic sine of an affine combination
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return affine combination
       */
      static aerror_t asinh(ac_t *ac, const iv_t &d);
      
      /** 
       * Area hyperbolic tangent of an affine combination
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return affine combination
       */
      static aerror_t atanh(ac_t *ac, const iv_t &d);

      /** 
       * Calculates \f$ac = \sqrt{ac}\f$
       * 
       * @param ac affine combination to manipulate
       * @param lbx lower bound of ac's domain 
       * @param ubx upper bound of ac's domain
       * 
       * @return error bounds
       */
      static aerror_t sqrt(ac_t *ac, T lbx, T ubx);

      /** 
       * Calculates \f$ac = e^{ac}\f$
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return error bounds
       */
      static aerror_t exp(ac_t *ac, const iv_t &d);

      /** 
       * Calculates \f$ac = 2^{ac}\f$
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return error bounds
       */
      static aerror_t exp2(ac_t *ac, const iv_t &d);

      /** 
       * Calculates \f$ac = 10^{ac}\f$
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return error bounds
       */
      static aerror_t exp10(ac_t *ac, const iv_t &d);

      /** 
       * Calculates \f$ac = e^{ac} - 1\f$
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return error bounds
       */
      static aerror_t expm1(ac_t *ac, const iv_t &d);

      /** 
       * Calculates \f$ac = 2^{ac} - 1\f$
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return error bounds
       */
      static aerror_t exp2m1(ac_t *ac, const iv_t &d);

      /** 
       * Calculates \f$ac = 10^{ac} - 1\f$
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return error bounds
       */
      static aerror_t exp10m1(ac_t *ac, const iv_t &d);

      /** 
       * Calculates \f$ac = \log{ac}\f$
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return error bounds
       */
      static aerror_t log(ac_t *ac, const iv_t &d);

      /** 
       * Calculates \f$ac = \log_2{ac}\f$
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return error bounds
       */
      static aerror_t log2(ac_t *ac, const iv_t &d);

      /** 
       * Calculates \f$ac = \log_{10}{ac}\f$
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return error bounds
       */
      static aerror_t log10(ac_t *ac, const iv_t &d);

      /** 
       * Calculates \f$ac = \log(ac+1)\f$
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return error bounds
       */
      static aerror_t logp1(ac_t *ac, const iv_t &d);

      /** 
       * Calculates \f$ac = \log_2(ac+1)\f$
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return error bounds
       */
      static aerror_t log2p1(ac_t *ac, const iv_t &d);

      /** 
       * Calculates \f$ac = \log_{10}(ac+1)\f$
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return error bounds
       */
      static aerror_t log10p1(ac_t *ac, const iv_t &d);

      /** 
       * Hyperbolic cosine function
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return error bounds
       */
      static aerror_t cosh(ac_t *ac, const iv_t &d);

      /** 
       * Area hyperbolic cosine function
       * 
       * @param ac affine combination to manipulate
       * @param d domain of ac
       * 
       * @return error bounds
       */
      static aerror_t acosh(ac_t *ac, iv_t d);

      /** 
       * Calculates \f$ac1 *= ac2\f$
       * 
       * @param ac1 affine combination to manipulate
       * @param ac2 affine combination
       * @param rad1 radius of ac1 
       * @param rad2 radius of ac2
       * 
       * @return error bounds
       */
      static aerror_t mul(ac_t *ac1, const ac_t &ac2, T rad1, T rad2);

      /** 
       * Calculates \f$ac = ac^2\f$
       * 
       * @param ac affine combination to manipulate
       * @param rad radius of ac 
       * 
       * @return error bounds
       */
      static aerror_t sqr(ac_t *ac, T rad);

      /** 
       * Calculates \f$ac = ac^n\f$
       * 
       * @param ac affine combination to manipulate
       * @param n exponent
       * @param rad radius of ac
       * 
       * @return error bounds
       */
      static aerror_t pown(ac_t *ac, unsigned n, T rad);
    };
  }
}

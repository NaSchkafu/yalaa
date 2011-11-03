// -*-c++-*-
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
 * @file   minrangefp.hpp
 * @author Stefan Kiel <kiel@inf.uni-due.de>
 * @date   Thu Oct 27 16:21:11 2011
 * 
 * @brief  Declarations for non-affine operation with FP math for strictly convex/concave functions
 * 
 * 
 */


#ifndef __MINRANGEFP_HPP__
#define __MINRANGEFP_HPP__
namespace yalaa
{
  namespace kernel
  {
    namespace details
    {
      /// FP approximations for non affine strictly convex/concave functions with IA support
      /**
       * The "Min-Range" implementions described in de Figueiredo and Stolfi, 1997 are used
       * This specialized version implements square root and square for floating point numbers, 
       * which is possible without external library support.
       */
      // ET ErrorTerm
      // AC AffineComb
      // AFFOP Stucture that implements the affine operations
      template<typename T, template<typename> class ET,
               template<typename, template<typename> class> class AC,
               class AFFOP>
      struct MinRangeBuiltInFP
      {
      public:
        typedef ET<T> error_t;
        typedef AC<T, ET> ac_t;
        typedef yalaa::details::ArithmeticError<T> aerror_t;
        typedef AFFOP aff_op_t;

        static aerror_t sqrt(ac_t *ac, T lbx, T ubx);
      };


    /// FP approximations for non affine strictly convex/concave functions
    /**
     * The "Min-Range" implementions described in de Figueiredo and Stolfi, 1997 are used.
     * For ensuring a verified result the functions are evaluated with interval arithmetic instead
     * of standard floating-point math, as the most libm implementations do respect rounding modes
     * for non IEEE754 functions.
     **/
    // ET ErrorTerm
    // AC AffineComb
    // AFFOP Stucture that implements the affine operations
    // IV Interval type
      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
    struct MinRangeFP
    {
      typedef T base_t;
      typedef ET<base_t> error_t;
      typedef AC<base_t, ET> ac_t;
      typedef yalaa::details::ArithmeticError<base_t> aerror_t;
      typedef AFFOP aff_op_t;
      typedef IV iv_t;
      typedef yalaa::traits::interval_traits<iv_t> iv_traits;
      typedef yalaa::traits::base_traits<base_t> b_traits;

      static aerror_t exp(ac_t *ac, const iv_t &d);
      static aerror_t exp2(ac_t *ac, const iv_t &d);
      static aerror_t exp10(ac_t *ac, const iv_t &d);

      static aerror_t expm1(ac_t *ac, const iv_t &d);
      static aerror_t exp2m1(ac_t *ac, const iv_t &d);
      static aerror_t exp10m1(ac_t *ac, const iv_t &d);

      static aerror_t log(ac_t *ac, const iv_t &d);
      static aerror_t log2(ac_t *ac, const iv_t &d);
      static aerror_t log10(ac_t *ac, const iv_t &d);

      static aerror_t logp1(ac_t *ac, const iv_t &d);
      static aerror_t log2p1(ac_t *ac, const iv_t &d);
      static aerror_t log10p1(ac_t *ac, const iv_t &d);

      static aerror_t cosh(ac_t *ac, const iv_t &d);
      static aerror_t acosh(ac_t *ac, iv_t d);

      static aerror_t minr_powr(ac_t *ac, const iv_t &d, int p, unsigned q);
      static aerror_t minr_inv(ac_t* ac, const iv_t &d); 

      static aerror_t minr_rootn(ac_t *ac, const iv_t &d, unsigned q);

    private:
      static aerror_t expx(ac_t *ac, const iv_t &d, iv_t (*f)(const iv_t&));
      static aerror_t logx(ac_t *ac, const iv_t &d, iv_t (*f)(const iv_t&));
      static aerror_t logxp1(ac_t *ac, const iv_t &d, iv_t (*f)(const iv_t&));
    };
    }
  }
}
#endif /*__MINRANGEFP_HPP__*/

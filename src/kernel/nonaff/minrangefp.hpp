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


#ifndef __MINRANGEFP_HPP__
#define __MINRANGEFP_HPP__
namespace yalaa
{
  namespace kernel
  {
    namespace details
    {
      // Non affine approximations for strict convex/concave functions
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


    // Non affine approximations for strict convex/concave functions
    /**
     * The "Min-Range" implementions described in de Figueiredo and Stolfi, 1997 are used
     * This template calculates exp, ln, log, ??? and is implemented for floating point numbers
     * An external (library) is required, as the built-in functions of libm do not (always?)
     * respect rouding mode changes. The behaviour in case of rounding modes other than
     * round-to-nearest is "implemention defined" according to C99.
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
      typedef ET<T> error_t;
      typedef AC<T, ET> ac_t;
      typedef yalaa::details::ArithmeticError<T> aerror_t;
      typedef AFFOP aff_op_t;
      typedef IV iv_t;
      typedef yalaa::details::base_traits<iv_t> iv_traits;

      static aerror_t exp(ac_t *ac, const IV &d);
      static aerror_t ln(ac_t *ac, const IV &d);
      static aerror_t inv(ac_t *ac, const IV &d);
      //static aerror_t asin(ac_t *ac, IV d);
      // static aerror_t log(ac_t *ac, const IV &d);

      // private:
      //   static T S_LN10_SUP;
    };
    }
  }
}
#endif /*__MINRANGEFP_HPP__*/

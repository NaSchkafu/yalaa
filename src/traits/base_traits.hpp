#ifndef __BASE_TRAITS_HPP__
#define __BASE_TRAITS_HPP__

#include <math.h>

namespace yalaa 
{
  namespace details 
  {
    /// Traits template for base types used in yalaa::AffineForm
    /**
     * This template defines properties of arithmetic types used in
     * yalaa::AffineForm as base type. Before using a custom type
     * you have to specialize this template.
     */
    template<typename T>
    struct base_traits 
    { 
      typedef int base_ref_t;

      /** 
       * Returns the representation of 0 for this type
       * 
       * 
       * @return zero representation in T
       */
      static T my_zero();

      /** 
       * Returns the representation of 1 for this type
       * 
       * 
       * @return one representation in T
       */
      static T my_one();
      
      /** 
       * Adds two T objects
       * 
       * @param s1 summand 
       * @param s2 summand
       * 
       * @return sum
       */
      static T add(base_ref_t s1, base_ref_t s2);

      /** 
       * Subtracts s from m
       * 
       * @param m minuend
       * @param s subtrahend
       * 
       * @return difference
       */
      static T sub(base_ref_t m, base_ref_t s);

      /** 
       * Multiplys p1 and p2
       * 
       * @param f1 factor
       * @param f2 factor
       * 
       * @return product
       */
      static T mul(base_ref_t f1, base_ref_t f2);

      /** 
       * Divides d1 by d2
       * 
       * @param d1 dividend
       * @param d2 divisor
       * 
       * @return quotient
       */
      static T div(base_ref_t d1, base_ref_t d2);
    };
  }
}
#endif

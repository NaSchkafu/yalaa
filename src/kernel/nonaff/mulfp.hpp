#ifndef __MULFP_HPP__
#define __MULFP_HPP__

namespace yalaa
{
  namespace kernel
  {
    namespace details
    {
      /// Multiplication implemention for affine forms with floating point base types
      /**
       * This structure implements multiplication of two affine forms for floating point base types.
       * It is based on the original affine multiplication routine due to de Figueiredo
       * and Stolfi, 1997.
       */
      template<typename T, template<typename> class ET,
               template<typename, template<typename> class> class AC,
               class AFFOP, class IV>
      struct MultiplicationFP
      {
	// These operations are only verified for floating-point numbers
	// according to IEEE 754, please check the implementation carefully
	// if you are using other types
	BOOST_STATIC_ASSERT(boost::is_floating_point<T>::value);

        typedef ET<T> error_t;
        typedef AC<T, ET> ac_t;
        typedef yalaa::details::ArithmeticError<T> aerror_t;
        typedef AFFOP aff_op_t;
        typedef IV iv_t;
        typedef yalaa::details::base_traits<iv_t> iv_traits;

        static aerror_t mul(ac_t *ac1, const ac_t &ac2, T rad1, T rad2);
        static aerror_t sqr(ac_t *ac, T rad);
        static aerror_t pow(ac_t *ac, unsigned n, T rad);

      private:
        static unsigned binom(unsigned n, unsigned k);
        static T s_pow(T a, unsigned n);
        static const ac_t S_DUMMY;
      };
    }
  }
}

#endif /*__MULFP_HPP__*/

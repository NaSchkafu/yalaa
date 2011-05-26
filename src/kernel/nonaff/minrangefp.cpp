// -*-c++-*-

#include "minrangefp.hpp"

namespace yalaa
{
  namespace kernel
  {
    namespace details
    {
      /**
       * Creates a min-range approximation for a non affine function
       * (Assumes upwards rounding)
       * @param lbx lower bound of approximation domain
       * @param ubx upper bound of approximation domain
       * @param lbf lower bound of function's codomain at lbx
       * @param ubf upper bound if function's codomain at ubx
       * @param alpha slope of affine approximation
       * @param inde parameter is used for storing the independent term
       *
       * @return error bounds
       */
      template<typename T>
      T min_range(T lbx, T ubx, T lbf, T ubf, T alpha, T &inde)
      {
	T lbd = -(-lbf + alpha*lbx);
        T ubfa = (-alpha)*ubx;
        T ubd = ubf - ubfa;
        T err = ubd - lbd;
        inde = (ubd + lbd)/2; 
        return err;
      }
      // ****************************************************************


      template<typename T, template<typename> class ET,
               template<typename, template<typename> class> class AC,
               class AFFOP>
      typename MinRangeBuiltInFP<T, ET, AC, AFFOP>::aerror_t
      MinRangeBuiltInFP<T, ET, AC, AFFOP>::sqrt(ac_t *ac, T lbx, T ubx)
      {
	yalaa::fp::RndControl rnd;
	rnd.downward();
	T fa = yalaa::details::base_traits<T>::my_sqrt(lbx);
	rnd.upward();
	T fb = yalaa::details::base_traits<T>::my_sqrt(ubx);
	T alpha = 1/2*fb;
	
	T c;
	T err = min_range(lbx, ubx, fa, fb, alpha, c);
	
	// std::cout << "lbx:" << lbx << " ubx: " << ubx << " alpha: " << alpha
	//           << " c: " << c << " err: " << err << " fa: " << fa << " fb: " << fb << std::endl;

	// // Affine Approximation f = alpha*x + c mit Fehler err berechnen
	err += aff_op_t::scale_add(ac, alpha, alpha, c, rnd);
	return yalaa::details::ArithmeticError<T>(err, !yalaa::fp::is_special(err));
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::exp(ac_t *ac, const IV &d)
      {
	yalaa::fp::RndControl rnd;
	const iv_t &e = yalaa::details::base_traits<iv_t>::my_exp(d);
	T c;
	rnd.upward();
	T err = min_range(yalaa::details::base_traits<iv_t>::my_inf(d),
			  yalaa::details::base_traits<iv_t>::my_sup(d), yalaa::details::base_traits<iv_t>::my_inf(e),
			  yalaa::details::base_traits<iv_t>::my_sup(e), yalaa::details::base_traits<iv_t>::my_inf(e),
			  c);
	T err2 = aff_op_t::scale_add(ac, yalaa::details::base_traits<iv_t>::my_inf(e), 
					  yalaa::details::base_traits<iv_t>::my_inf(e), c, rnd);
	rnd.upward();
	err += err2;
	return yalaa::details::ArithmeticError<T>(err, !yalaa::fp::is_special(err));
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::ln(ac_t *ac, const IV &d)
      {
	yalaa::fp::RndControl rnd;
	const iv_t &l = yalaa::details::base_traits<iv_t>::my_ln(d);
	rnd.upward();
	T dx = 1/yalaa::details::base_traits<iv_t>::my_sup(d);
	T c;
	T err = min_range(yalaa::details::base_traits<iv_t>::my_inf(d),
			       yalaa::details::base_traits<iv_t>::my_sup(d), yalaa::details::base_traits<iv_t>::my_inf(l),
			       yalaa::details::base_traits<iv_t>::my_sup(l), dx, c);
	T err2 = aff_op_t::scale_add(ac, dx, dx, c, rnd);
	rnd.upward();
	err += err2;
	return yalaa::details::ArithmeticError<T>(err, !yalaa::fp::is_special(err));	
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::inv(ac_t *ac, const IV& d)
      {
	yalaa::fp::RndControl rnd;
	bool sgn = iv_traits::my_inf(d) < 0;
	T a = fabs(iv_traits::my_inf(d));
	T b = fabs(iv_traits::my_sup(d));
	if(a > b)
	  std::swap(a,b);
	rnd.upward();
	T alpha = -(1/(-b)*b);
	T c;
	T err = min_range(a, b, -(1/-b), 1/a, alpha, c);
	if(sgn)
	  c = -c;
	T err2 = aff_op_t::scale_add(ac, alpha, alpha, c, rnd);
	rnd.upward();
	err += err2;
	return yalaa::details::ArithmeticError<T>(err, !yalaa::fp::is_special(err));
      }
    }
  }
}

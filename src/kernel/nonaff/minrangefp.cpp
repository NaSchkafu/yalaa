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
	unsigned flags = 0;
	if(ubx < 0)
	  return aerror_t(0.0,aerror_t::C_D_VIOL);
	else if(lbx < 0)
	  flags |= aerror_t::P_D_VIOL;

	yalaa::fp::RndControl rnd;
	rnd.downward();
	T fa = yalaa::details::base_traits<T>::my_sqrt(lbx);
	rnd.upward();
	T fb = yalaa::details::base_traits<T>::my_sqrt(ubx);
	T alpha = 1/2*fb;
	
	T c;
	T err = min_range(lbx, ubx, fa, fb, alpha, c);
	
	err += aff_op_t::scale_add(ac, alpha, alpha, c, rnd);
	flags |= yalaa::fp::get_flags(err);
	return aerror_t(err, flags);
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::exp(ac_t *ac, const IV &d)
      {
	yalaa::fp::RndControl rnd;
	const iv_t &e = iv_traits::my_exp(d);
	T c;
	rnd.upward();
	T err = min_range(iv_traits::my_inf(d), iv_traits::my_sup(d), iv_traits::my_inf(e),
			  iv_traits::my_sup(e), iv_traits::my_inf(e), c);
	T err2 = aff_op_t::scale_add(ac, iv_traits::my_inf(e), iv_traits::my_inf(e), c, rnd);
	rnd.upward();
	err += err2;
	return aerror_t(err, yalaa::fp::get_flags(err));
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::ln(ac_t *ac, const IV &d)
      {
	if(iv_traits::my_sup(d) <= 0)
	  return aerror_t(0.0, aerror_t::C_D_VIOL);
	else if(iv_traits::my_inf(d) <= 0)
	  return aerror_t(0.0, aerror_t::UNBOUND | aerror_t::P_D_VIOL);

	yalaa::fp::RndControl rnd;
	const iv_t &l = iv_traits::my_ln(d);
	rnd.upward();
	T dx = 1/iv_traits::my_sup(d);
	T c;
	T err = min_range(iv_traits::my_inf(d), iv_traits::my_sup(d), 
			  iv_traits::my_inf(l), iv_traits::my_sup(l), dx, c);
	T err2 = aff_op_t::scale_add(ac, dx, dx, c, rnd);
	rnd.upward();
	err += err2;
	return aerror_t(err, yalaa::fp::get_flags(err));	
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::inv(ac_t *ac, const IV& d)
      {
	if(iv_traits::my_inf(d) <= 0 && iv_traits::my_sup(d) >= 0)
	  return aerror_t(0.0, aerror_t::UNBOUND | 
			  (iv_traits::my_inf(d) == iv_traits::my_sup(d) ? aerror_t::C_D_VIOL :  aerror_t::P_D_VIOL));
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
	return aerror_t(err, yalaa::fp::get_flags(err));
      }
    }
  }
}

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
#include <math.h>

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
      MinRangeFP<T, ET, AC, AFFOP, IV>::expx(ac_t *ac, const iv_t &d, iv_t (*f)(const iv_t&))
      {
	yalaa::fp::RndControl rnd;
	const iv_t &e = (*f)(d);
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
      MinRangeFP<T, ET, AC, AFFOP, IV>::exp(ac_t *ac, const iv_t &d)
      {
	return expx(ac, d, &iv_traits::my_exp);
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::exp2(ac_t *ac, const iv_t &d)
      {
	return expx(ac, d, &iv_traits::my_exp2);
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::exp10(ac_t *ac, const iv_t &d)
      {
	return expx(ac, d, &iv_traits::my_exp10);
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::expm1(ac_t *ac, const iv_t &d)
      {
	return expx(ac, d, &iv_traits::my_expm1);
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::exp2m1(ac_t *ac, const iv_t &d)
      {
	return expx(ac, d, &iv_traits::my_exp2m1);
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::exp10m1(ac_t *ac, const iv_t &d)
      {
	return expx(ac, d, &iv_traits::my_exp10m1);
      }


      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::logx(ac_t *ac, const iv_t &d, iv_t (*f)(const iv_t&))
      {
	if(iv_traits::my_sup(d) <= 0)
	  return aerror_t(0.0, aerror_t::C_D_VIOL);
	else if(iv_traits::my_inf(d) <= 0)
	  return aerror_t(0.0, aerror_t::UNBOUND | aerror_t::P_D_VIOL);
	yalaa::fp::RndControl rnd;
	const iv_t &l = (*f)(d);
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
      MinRangeFP<T, ET, AC, AFFOP, IV>::log(ac_t *ac, const iv_t &d)
      {
	return logx(ac, d, &iv_traits::my_log);
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::log2(ac_t *ac, const iv_t &d)
      {
	return logx(ac, d, &iv_traits::my_log2);
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::log10(ac_t *ac, const iv_t &d)
      {
	return logx(ac, d, &iv_traits::my_log10);
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::logxp1(ac_t *ac, const iv_t &d, iv_t (*f)(const iv_t&))
      {
	if(iv_traits::my_sup(d) <= -1.0)
	  return aerror_t(0.0, aerror_t::C_D_VIOL);
	else if(iv_traits::my_inf(d) <= -1.0)
	  return aerror_t(0.0, aerror_t::UNBOUND | aerror_t::P_D_VIOL);
	yalaa::fp::RndControl rnd;
	const iv_t &l = (*f)(d);
	rnd.upward();
	T dx = 1/(1.0 + iv_traits::my_sup(d));
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
      MinRangeFP<T, ET, AC, AFFOP, IV>::logp1(ac_t *ac, const iv_t &d)
      {
	return logxp1(ac, d, &iv_traits::my_logp1);
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::log2p1(ac_t *ac, const iv_t &d)
      {
	return logxp1(ac, d, &iv_traits::my_log2p1);
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::log10p1(ac_t *ac, const iv_t &d)
      {
	return logxp1(ac, d, &iv_traits::my_log10p1);
      }


      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::cosh(ac_t *ac, const iv_t &d)
      {
	yalaa::fp::RndControl rnd;

	T lbd(iv_traits::my_inf(d));
	T ubd(iv_traits::my_sup(d));
	T ubf(0);
	T lbf(0);
	if(0 > lbd && 0 < ubd)  {
	  ubf = iv_traits::my_sup(iv_traits::my_cosh(iv_t(ubd)));
	  lbf = iv_traits::my_inf(iv_traits::my_cosh(iv_t(lbd)));
	} 
	else {
	  iv_t f(iv_traits::my_cosh(d));
	  lbf = iv_traits::my_inf(f);
	  ubf = iv_traits::my_sup(f);
	}
	if(0 > ubd)
	  std::swap(lbf, ubf);
	T c;
	rnd.upward();
	T err = min_range(lbd, ubd, lbf, ubf, lbf, c);
	T err2 = aff_op_t::scale_add(ac, lbf, lbf, c, rnd);
	rnd.upward();
	err += err2;
	return aerror_t(err, yalaa::fp::get_flags(err));
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::acosh(ac_t *ac, iv_t d)
      {
	yalaa::fp::RndControl rnd;
	unsigned flags = 0;
	if(iv_traits::my_sup(d) < 1)
	  return aerror_t(0.0, aerror_t::C_D_VIOL);
	else if(iv_traits::my_inf(d) < 1) {
	  flags = aerror_t::P_D_VIOL;
	  d = iv_t(1.0, iv_traits::my_sup(d));
	}
	iv_t fd(iv_traits::my_acosh(d));
	T c;
	rnd.upward();
	T err = min_range(iv_traits::my_inf(d), iv_traits::my_sup(d), iv_traits::my_inf(fd), iv_traits::my_sup(fd),
			  iv_traits::my_sup(fd), c);
	T err2 = aff_op_t::scale_add(ac, iv_traits::my_inf(fd), iv_traits::my_inf(fd), c, rnd);
	rnd.upward();
	err += err2;
	return aerror_t(err, yalaa::fp::get_flags(err) | flags);
      }
    

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      typename MinRangeFP<T, ET, AC, AFFOP, IV>::aerror_t
      MinRangeFP<T, ET, AC, AFFOP, IV>::inv(ac_t *ac, const iv_t& d)
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

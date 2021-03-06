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


#include "mulfp.hpp"

namespace yalaa
{
  namespace kernel
  {
    namespace details
    {
      template<typename T, template<typename> class ET,
               template<typename, template<typename> class> class AC,
               class AFFOP, class IV>
      typename MultiplicationFP<T, ET, AC, AFFOP,IV>::aerror_t
      MultiplicationFP<T, ET, AC, AFFOP, IV>::mul(ac_t *ac1, const ac_t &ac2, T rad1, T rad2)
      {
	yalaa::fp::RndControl rnd;
	iv_t central(iv_traits::my_mul(iv_t(ac1->central()),iv_t(ac2.central())));
	T err = aff_op_t::affine(ac1, ac2, ac2.central(), ac1->central(),
                                               0.0, iv_traits::my_mid(central), rnd);
	rnd.upward();
	err += rad1*rad2;
	err += iv_traits::my_w(central);
	return yalaa::details::ArithmeticError<T>(err, yalaa::fp::get_flags(err));
      }
      
      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP, class IV>
      typename MultiplicationFP<T, ET, AC, AFFOP,IV>::aerror_t
      MultiplicationFP<T, ET, AC, AFFOP, IV>::pown(ac_t *ac, unsigned n, T rad)
      {
	// Sonderfaelle
	if(n < 2) {
	  if(!n) {
	    ac->clear();
	    ac->set_central(1.0);
	  }
	  return yalaa::details::ArithmeticError<T>(0.0, 0);
	}
	else if(n == 2)
	  return sqr(ac, rad);
	else if(n > static_cast<unsigned>(std::numeric_limits<int>::max()))
	  return yalaa::details::ArithmeticError<T>(0.0, yalaa::details::ArithmeticError<T>::I_ERROR);
	
	yalaa::fp::RndControl rnd;
	// central interval
	iv_t ix0(iv_traits::my_pow(iv_t(ac->central()), (int)n));
	iv_t iscale(iv_traits::my_mul(iv_t(static_cast<T>(n)), iv_traits::my_pow(iv_t(ac->central()), (int)n-1)));

	// Approx Fehler
	rnd.upward();
	T err = 0;
	T perr = 0.0, serr = 0.0;
	T prad = rad;
	for(unsigned k = 2; k <= n; k++) {
	  prad *= rad;
	  (n % 2 ? serr : perr) += fabs(binom(n,k)*prad*s_pow(ac->central(), n - k));
	}
	perr *= 0.5;     
	err = serr;
	
	// Affine OP
	T err2 = aff_op_t::scale_add(ac, 0.0, 0.0, iv_traits::my_inf(iscale), 
				     iv_traits::my_sup(iscale), iv_traits::my_inf(ix0), iv_traits::my_sup(ix0), rnd);
	rnd.upward();
	err += err2;
	
	return yalaa::details::ArithmeticError<T>(err, perr, 0.0, yalaa::fp::get_flags(err));
      }
      
      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP, class IV>
      typename MultiplicationFP<T, ET, AC, AFFOP,IV>::aerror_t
      MultiplicationFP<T, ET, AC, AFFOP, IV>::sqr(ac_t *ac, T rad)
      {
	yalaa::fp::RndControl rnd;
	iv_t csqr(iv_traits::my_sqr(iv_t(ac->central())));
	T center = iv_traits::my_mid(csqr);
	T err = aff_op_t::scale_add(ac, 0.0, 2*ac->central(), center, rnd);
	rnd.upward();
	err += iv_traits::my_w(csqr);
	rad *= rad;
	return yalaa::details::ArithmeticError<T>(err, rad, 0.0, yalaa::fp::get_flags(err));
      }

      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP, class IV>
      unsigned MultiplicationFP<T, ET, AC, AFFOP, IV>::binom(unsigned n, unsigned k)
      {
	if(k == 0)
	  return 1;
	else if(2*k > n)
	  return binom(n, n - k);
	unsigned res = n-k+1;
	for(unsigned i = 2; i <= k; i++) {
	  res *= (n-k+i);
	  res /= i;
	}
	return res;
      }

      template<typename T, template<typename> class ET,
               template<typename, template<typename> class> class AC,
               class AFFOP, class IV>
      T MultiplicationFP<T, ET, AC, AFFOP, IV>::s_pow(T a, unsigned n)
      {
	if(a)
	  return n ? (n % 2 ? a : 1)*s_pow(a*a, n/2) : 1.0;
	return a;
      }
    
      template<typename T, template<typename> class ET,
             template<typename, template<typename> class> class AC,
             class AFFOP, class IV>
    const typename MultiplicationFP<T, ET, AC, AFFOP, IV>::ac_t MultiplicationFP<T, ET, AC, AFFOP, IV>::S_DUMMY = typename MultiplicationFP<T, ET, AC, AFFOP, IV>::ac_t(0.0);
    }
  }
}

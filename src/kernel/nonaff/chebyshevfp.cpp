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


namespace yalaa
{
  namespace kernel
  {
    namespace details
    {
      template<typename T, template<typename> class ET,
               template<typename, template<typename> class> class AC,
               class AFFOP,
               class IV>
      short ChebyshevFP<T, ET, AC, AFFOP, IV>::sgn(T s)
      {
	if(s < 0)
	  return -1.0;
	return 1.0;
      }

    // template<template<typename> class ET,
    //         template<typename, template<typename> class> class AC,
    //         class AFFOP,
    //         class IV>


    // template<template<typename> class ET,
    //         template<typename, template<typename> class> class AC,
    //         class AFFOP,
    //         class IV>
    // const T ChebyshevD<ET, AC, AFFOP, IV>::S_PINF = iv_traits::my_inf(iv_traits::my_pi());

    // template<template<typename> class ET,
    //         template<typename, template<typename> class> class AC,
    //         class AFFOP,
    //         class IV>
    // const T ChebyshevD<ET, AC, AFFOP, IV>::S_PSUP = iv_traits::my_sup(iv_traits::my_pi());

    template<typename T, template<typename> class ET,
             template<typename, template<typename> class> class AC,
             class AFFOP,
             class IV>
    typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t
    ChebyshevFP<T, ET, AC, AFFOP, IV>::sin(ac_t *ac, const iv_t &d)
    {
      // TODO: thread safe
      static const T S_PINF = iv_traits::my_inf(iv_traits::my_pi());
      // TODO: Argumentenreduktion? (Cody & Wait / Payne & Hanek) implementieren
      yalaa::fp::RndControl rnd;
      rnd.upward();
      if(iv_traits::my_sup(d) - iv_traits::my_inf(d) >= 2*S_PINF) {
	ac->clear();
	ac->set_central(0.0);
	return aerror_t(1.0, false);
      }
      return chebyshev(ac, d, &iv_traits::my_sin, false, [&d](const iv_t&, const iv_t&)->T { return lag_rem(d, iv_traits::my_cos(d)); }, rnd);
    }


    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV>
    typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t ChebyshevFP<T, ET, AC, AFFOP, IV>::cos(ac_t *ac, const iv_t &d)
    {
      // TODO: thread safe
      static const T S_PINF = iv_traits::my_inf(iv_traits::my_pi());
      yalaa::fp::RndControl rnd;
      rnd.upward();
      if(iv_traits::my_sup(d) - iv_traits::my_inf(d) >= 2*S_PINF) {
	ac->clear();
	ac->set_central(0.0);
	return aerror_t(1.0, false);
      }
      return chebyshev(ac, d, &iv_traits::my_cos, false, 
		       [&d](const iv_t&, const iv_t&)->T { return lag_rem(d, iv_traits::my_neg(iv_traits::my_sin(d))); } , rnd);
    }

    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV>
    T ChebyshevFP<T, EC, AC, AFFOP, IV>::eval_poly_lb(T lbc0, T lbc1, T lbx)
    {
      // Gesucht wird der LB der Polyauswertung
      // Annahme: rnd.upward()
      return -(lbc0 - (-iv_traits::my_inf(lbc1))*iv_traits::my_inf(lbx));
    }
      

    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV>
    typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t ChebyshevFP<T, ET, AC, AFFOP, IV>::asin(ac_t *ac, iv_t d)
    {
      if(iv_traits::my_sup(d) < -1.0 || iv_traits::my_inf(d) > 1.0)
	return aerror_t(0.0, aerror_t::C_D_VIOL);
      unsigned flags = 0;
      if(iv_traits::my_sup(d) > 1.0 || iv_traits::my_inf(d) < -1.0) {
	flags = aerror_t::P_D_VIOL;
	d = iv_t(std::min(iv_traits::my_sup(d),1.0), std::max(iv_traits::my_inf(d), -1.0));
      }
      yalaa::fp::RndControl rnd;
      return chebyshev(ac, d, &iv_traits::my_asin, false, [&d](const iv_t &c0, const iv_t &c1)->T {
	  auto dasin = [](const iv_t &a) { return iv_traits::my_one()/iv_traits::my_sqrt(iv_traits::my_sub(iv_traits::my_one(),iv_traits::my_sqr(a))); };

	  if(iv_traits::my_inf(d) > -0.7 && iv_traits::my_sup(d) < 0.7)
	    return lag_rem(d, dasin(d));
	  iv_t e(iv_traits::my_sqrt(iv_traits::my_sub(iv_traits::my_one(),iv_traits::my_div(iv_traits::my_one(),iv_traits::my_sqr(c1)))));
	  
	  iv_traits x1(iv_traits::my_asin(e));
	  
	  eval_poly(

	}, rnd);
    }


      template<typename T, template<typename> class ET,
               template<typename, template<typename> class> class AC,
               class AFFOP,
               class IV>
      typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t
      ChebyshevFP<T, ET, AC, AFFOP, IV>::acos(ac_t *ac, iv_t d)
               {
                 if(iv_traits::my_sup(d) < -1.0 || iv_traits::my_inf(d) > 1.0)
                   return aerror_t(0.0, aerror_t::C_D_VIOL);
                 unsigned flags = 0;
                 if(iv_traits::my_sup(d) > 1.0 || iv_traits::my_inf(d) < -1.0) {
                   flags = aerror_t::P_D_VIOL;
                   d = iv_t(std::min(iv_traits::my_sup(d),1.0), std::max(iv_traits::my_inf(d), -1.0));
                 }
                 yalaa::fp::RndControl rnd;
                 return chebyshev(ac, d, &iv_traits::my_asin, false, &dx_asin, rnd);
               }

      // template<typename T, template<typename> class ET,
      // 	       template<typename, template<typename> class> class AC,
      // 	       class AFFOP,
      // 	       class IV>
      // // typename ChebyshevFP<T, ET, AC, AFFOP, IV>::iv_t ChebyshevFP<T, ET, AC, AFFOP, IV>::dx_asin(const iv_t& iv)
      // {
      // 	return iv_traits::my_one()/iv_traits::my_sqrt(iv_traits::my_sub(iv_traits::my_one(),iv_traits::my_sqr(iv)));
      // }

      // template<typename T, template<typename> class ET,
      // 	       template<typename, template<typename> class> class AC,
      // 	       class AFFOP,
      // 	       class IV>
      // typename ChebyshevFP<T, ET, AC, AFFOP, IV>::iv_t ChebyshevFP<T, ET, AC, AFFOP, IV>::dx_acos(const iv_t& iv)
      // {
      // 	return iv_traits::my_neg(iv_traits::my_one())/iv_traits::my_sqrt(iv_traits::my_sub(iv_traits::my_one(),iv_traits::my_sqr(iv)));
      // }
    
      
      // template<typename T, template<typename> class ET,
      // 	       template<typename, template<typename> class> class AC,
      // 	       class AFFOP,
      // 	       class IV>
      // typename ChebyshevFP<T, ET, AC, AFFOP, IV>::iv_t ChebyshevFP<T, ET, AC, AFFOP, IV>::neg_sin(const iv_t& iv)
      // {
      // 	return -iv_traits::my_sin(iv);
      // }
      
      // Lagrange Remainder
      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      T ChebyshevFP<T, ET, AC, AFFOP, IV>::lag_rem(const iv_t &d, const iv_t &bdf)
      {
	//static const T S_RMND1(192);
	static const iv_t S_RMND2(16, 16);
	T wd(iv_traits::my_w(d));
	// rnd.upward();
	wd *= wd;
	iv_t w(wd, wd);
	return iv_traits::my_sup(iv_traits::my_div(iv_traits::my_mul(w,bdf),S_RMND2));
      }
 
      template<typename T, template<typename> class ET,
               template<typename, template<typename> class> class AC,
               class AFFOP,
               class IV>
      typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t
      ChebyshevFP<T, ET, AC, AFFOP, IV>::chebyshev(ac_t *ac, const iv_t &d,
                                                   iv_t (*f)(const iv_t&), bool odd,
                                                   T (*apprerr)(const iv_t&, const iv_t&),
                                                   yalaa::fp::RndControl &rnd)
      {
	// TODO: thread safe
	static const iv_t S_X[2][2] = {
	  { iv_traits::my_div(iv_t(1.0),iv_traits::my_sqrt(iv_t(2.0))), iv_traits::my_div(iv_t(-1.0),iv_traits::my_sqrt(iv_t(2.0)))},
	  { iv_traits::my_div(iv_traits::my_sqrt(iv_t(3)),iv_t(2.0)), iv_t(0.0) }
	};
	static const T S_HALF(0.5);

	using namespace yalaa::fp;
	
	unsigned short order = odd ? 1 : 0;
	// TODO: cleanup, nur eine Modi Änderung
	T a = iv_traits::my_inf(d);
	T b = iv_traits::my_sup(d);

	// 1 Wechsel + 3 IV Mult + 2 IV Auswertungen von f
	rnd.upward();
	iv_t ibsia(fast_sub_dd_up<T, iv_t>(b,a));
	iv_t iapib(fast_add_dd_up<T, iv_t>(a,b));
	iv_t x0(S_HALF*fast_add_ii_up(iv_traits::my_mul(ibsia,S_X[order][0]), iapib));
	iv_t x1(S_HALF*fast_add_ii_up(iv_traits::my_mul(ibsia,S_X[order][1]), iapib));
	iv_t fx0((*f)(x0));
	iv_t fx1((*f)(x1));
	iv_t c0(fast_add_ii_up<iv_t>(fx0, fx1));
	iv_t c1(fast_add_ii_up<iv_t>(iv_traits::my_mul(fx0,S_X[order][0]),
				     iv_traits::my_mul(fx1,S_X[order][1])));
	c0 *= S_HALF;
	
	T err = 0.0;
	iv_t c12(iv_traits::my_inf(c1)*2, iv_traits::my_sup(c1)*2);
	c12 = iv_traits::my_div(c12, ibsia);
	err = aff_op_t::scale_add(ac, 0.0, 0.0, iv_traits::my_inf(c12), iv_traits::my_sup(c12),
				  iv_traits::my_inf(c0), iv_traits::my_sup(c0), rnd);
	
	
	err *= 0.5;
	return aerror_t(err, yalaa::fp::get_flags(err));
      }
    }
  }
}

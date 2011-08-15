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

    // Trig. Funktionen
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
      return chebyshev(ac, d, &iv_traits::my_sin, false, [&d](const iv_t&, const iv_t&)->T { 
	  return ChebyshevFP<T, ET, AC, AFFOP, IV>::lag_rem(d, iv_traits::my_neg(iv_traits::my_sin(d))); }, rnd);
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
		       [&d](const iv_t&, const iv_t&)->T { return self_t::lag_rem(d, iv_traits::my_neg(iv_traits::my_cos(d))); } , rnd);
    }

    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV>
    typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t ChebyshevFP<T, ET, AC, AFFOP, IV>::tan(ac_t *ac, const iv_t &d)
    {
      // TODO: Thread safe
      static const T S_PINF = iv_traits::my_inf(iv_traits::my_pi());
      yalaa::fp::RndControl rnd;

      T p(((unsigned)iv_traits::my_inf(d)/S_PINF)*S_PINF + S_PINF*0.5);
      rnd.upward();
      if(iv_traits::my_sup(d) - iv_traits::my_inf(d) >= S_PINF || (p >= iv_traits::my_inf(d) && p <= iv_traits::my_sup(d))) {
	ac->clear();
	ac->set_central(0.0);
	return aerror_t(0.0, aerror_t::P_D_VIOL | aerror_t::UNBOUND);
      }
      return chebyshev(ac, d, &iv_traits::my_tan, false, 
		       [&d](const iv_t&, const iv_t&)->T  { return self_t::lag_rem(d, iv_traits::my_div(iv_traits::my_mul(iv_t(2),iv_traits::my_sin(d)), 
								   iv_traits::my_pow(iv_traits::my_cos(d), 3))); }, rnd);
    }




      // Arkusfunktionen    
    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV>
    typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t ChebyshevFP<T, ET, AC, AFFOP, IV>::acos_asin(ac_t *ac, iv_t d, bool is_acos)
    {
      if(iv_traits::my_sup(d) < -1.0 || iv_traits::my_inf(d) > 1.0)
	return aerror_t(0.0, aerror_t::C_D_VIOL);
      unsigned flags = 0;
      if(iv_traits::my_sup(d) > 1.0 || iv_traits::my_inf(d) < -1.0) {
	flags = aerror_t::P_D_VIOL;
	d = iv_t(std::max(iv_traits::my_inf(d),-1.0), std::min(iv_traits::my_sup(d), -1.0));
      }
      yalaa::fp::RndControl rnd;
      iv_t (*f)(const iv_t&) = is_acos ? &iv_traits::my_acos : &iv_traits::my_asin;
      return chebyshev(ac, d, f, false, [&d, is_acos, f](const iv_t &c0, const iv_t &c1)->T {

	  // In der Mitte Lag. - Rem.
	  if(iv_traits::my_inf(d) > -0.7 && iv_traits::my_sup(d) < 0.7)
	    return self_t::lag_rem(d, (is_acos ? iv_traits::my_neg(iv_traits::my_one()) : iv_traits::my_one())
		  /iv_traits::my_sqrt(iv_traits::my_sub(iv_traits::my_one(),iv_traits::my_sqr(d))));
	  
	  // Sonst exakten Fehler bestimmen
	  // Maximaler Fehler liegt bei +/- e
	  iv_t e(iv_traits::my_sqrt(iv_traits::my_sub(iv_traits::my_one(),iv_traits::my_div(iv_traits::my_one(),iv_traits::my_sqr(c1)))));
	  
	  // rnd.upward()
	  iv_t fe((*f)(e));
	  iv_t fd((*f)(d));
	  T lbc0(iv_traits::my_inf(c0));
	  T lbc1(iv_traits::my_inf(c1));
	  T ae1(fabs(iv_traits::my_sup(fe) - self_t::eval_poly_lb(lbc0, lbc1, iv_traits::my_inf(e))));
	  T ae2(fabs(iv_traits::my_sup(iv_traits::my_neg(fe)) - self_t::eval_poly_lb(lbc0, lbc1, -iv_traits::my_sup(e))));
	  T ae3(fabs((is_acos ? iv_traits::my_sup(fd) : iv_traits::my_inf(fd)) - self_t::eval_poly_lb(lbc0, lbc1, iv_traits::my_inf(d))));
	  T ae4(fabs((is_acos ? iv_traits::my_inf(fd) : iv_traits::my_sup(fd)) - self_t::eval_poly_lb(lbc0, lbc1, iv_traits::my_sup(d))));

	  return 2*std::max(std::max(std::max(ae1, ae2), ae3), ae4);

	}, rnd, flags);
    }

    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV>
    typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t ChebyshevFP<T, ET, AC, AFFOP, IV>::asin(ac_t *ac, const iv_t &d)
    {
      return acos_asin(ac, d, false);
    }

    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV>
    typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t ChebyshevFP<T, ET, AC, AFFOP, IV>::acos(ac_t *ac, const iv_t &d)
    {
      return acos_asin(ac, d, true);
    }

    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV>
    typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t ChebyshevFP<T, ET, AC, AFFOP, IV>::atan(ac_t *ac, const iv_t &d)
    {
      yalaa::fp::RndControl rnd;
      // static const T S_PINF_H = 0.5*iv_traits::my_inf(iv_traits::my_pi());
      // unsigned flags = 0;
      // if(iv_traits::my_sup(d) < -S_PINF_H || iv_traits::my_inf(d) > S_PINF_H)
      // 	flags = aerror_t::C_D_VIOL;
      // else if((iv_traits::my_inf(d) < -S_PINF_H && iv_traits::my_sup(d) > -S_PINF_H) ||
      // 	      (iv_traits::my_inf(d) < S_PINF_H && iv_traits::my_sup(d) > S_PINF_H)) {
      // 	flags = aerror_t::P_D_VIOL | aerror_t::UNBOUND;
      // }
      // if(flags) {
      // 	ac->clear();
      // 	ac->set_central(0.0);
      // 	return aerror_t(0.0, flags);
      // }
      iv_t d2atan(atan_d2(d, rnd));
      //std::cout << "D2ATAN "  << d2atan << std::endl;
      return chebyshev(ac, d, &iv_traits::my_atan, false, [&d, d2atan](const iv_t&, const iv_t&)->T  
		       { return self_t::lag_rem(d, d2atan); }, rnd);
    }


    // Hyperbelfunktionen
    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV>
    typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t ChebyshevFP<T, ET, AC, AFFOP, IV>::sinh(ac_t *ac, const iv_t &d)
    {
      yalaa::fp::RndControl rnd;
      return chebyshev(ac, d, &iv_traits::my_sinh, false, [&d](const iv_t&, const iv_t&)->T  { return self_t::lag_rem(d, iv_traits::my_sinh(d)); }, rnd);
    }

    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV>
    typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t ChebyshevFP<T, ET, AC, AFFOP, IV>::tanh(ac_t *ac, const iv_t &d)
    {
      yalaa::fp::RndControl rnd;
      return chebyshev(ac, d, &iv_traits::my_tanh, false, [&d](const iv_t&, const iv_t&)->T  
		       { return self_t::lag_rem(d, iv_traits::my_mul(iv_t(2), 
					     iv_traits::my_mul(iv_traits::my_tanh(d), iv_traits::my_div(iv_traits::my_one(), 
													iv_traits::my_sqr(iv_traits::my_cosh(d)))))); }, rnd);
    }


    // Area Funktionen
    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV>
    typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t ChebyshevFP<T, ET, AC, AFFOP, IV>::asinh(ac_t *ac, const iv_t &d)
    {
      yalaa::fp::RndControl rnd;
      return chebyshev(ac, d, &iv_traits::my_asinh, false, [&d](const iv_t&, const iv_t&)->T  
		       { return self_t::lag_rem(d, iv_traits::my_div(iv_traits::my_neg(d), 
								     iv_traits::my_powr(iv_traits::my_add(iv_traits::my_one(),iv_traits::my_sqr(d)), 3, 2)));
						}, rnd);
    }
      
    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV>
    typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t ChebyshevFP<T, ET, AC, AFFOP, IV>::atanh(ac_t *ac, const iv_t &d)
    {
      yalaa::fp::RndControl rnd;
      if(iv_traits::my_inf(d) >= 1.0 || iv_traits::my_sup(d) <= -1.0)
	return aerror_t(0.0, aerror_t::C_D_VIOL);
      else if(iv_traits::my_inf(d) <= -1.0 || iv_traits::my_sup(d) >= 1.0)
	return aerror_t(0.0, aerror_t::P_D_VIOL | aerror_t::UNBOUND);
      return chebyshev(ac, d, &iv_traits::my_atanh, false, [&d](const iv_t&, const iv_t&)->T  
		       { return self_t::lag_rem(d, iv_traits::my_div(iv_traits::my_mul(iv_t(2), d), 
								     iv_traits::my_sqr(iv_traits::my_sub(iv_traits::my_sqr(d), iv_traits::my_one()))));  }, rnd );
    }
      



    // Lagrange Remainder
    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV>
    T ChebyshevFP<T, ET, AC, AFFOP, IV>::lag_rem(const iv_t &d, const iv_t &bdf)
    {
      //static const T S_RMND1(192);
      static const iv_t S_RMND2(16.0, 16.0);
      T wd(iv_traits::my_w(d));
      // rnd.upward();
      wd *= wd;
      iv_t w(wd, wd);
      return iv_traits::my_w(iv_traits::my_div(iv_traits::my_mul(w,bdf),S_RMND2));
    }
      
      template<typename T, template<typename> class ET,
               template<typename, template<typename> class> class AC,
               class AFFOP,
               class IV>
      typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t
      ChebyshevFP<T, ET, AC, AFFOP, IV>::chebyshev(ac_t *ac, const iv_t &d,
                                                   std::function<iv_t (const iv_t&)> f, bool odd,
                                                   std::function<T (const iv_t&, const iv_t&)> apprerr,
                                                   yalaa::fp::RndControl &rnd, unsigned flags)
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
	if(iv_traits::my_w(d) < S_USE_IV) {
	  iv_t range(f(d));
	  ac->clear();
	  if(iv_traits::my_inf(range) > iv_traits::my_sup(range))
	    flags |= aerror_t::I_ERROR;
	  else {
	    ac->set_central(iv_traits::my_mid(range));
	    flags |= yalaa::fp::get_flags(iv_traits::my_inf(range)) | 
	      yalaa::fp::get_flags(iv_traits::my_sup(range));
	  }
	  return aerror_t(iv_traits::my_w(range), flags);
	}

	iv_t ibsia(fast_sub_dd_up<T, iv_t>(b,a));
	iv_t iapib(fast_add_dd_up<T, iv_t>(a,b));
	iv_t x0(S_HALF*fast_add_ii_up(iv_traits::my_mul(ibsia,S_X[order][0]), iapib));
	iv_t x1(S_HALF*fast_add_ii_up(iv_traits::my_mul(ibsia,S_X[order][1]), iapib));
	iv_t fx0(f(x0));
	iv_t fx1(f(x1));
	iv_t c0(fast_add_ii_up<iv_t>(fx0, fx1));
	iv_t c1(fast_add_ii_up<iv_t>(iv_traits::my_mul(fx0,S_X[order][0]),
				     iv_traits::my_mul(fx1,S_X[order][1])));
	c0 *= S_HALF;



	T err = 0.0;
	//std::cout << c0 << " c1 " << c1 << std::endl;
	iv_t c12(iv_traits::my_inf(c1)*2, iv_traits::my_sup(c1)*2);
	c12 = iv_traits::my_div(c12, ibsia);

	 // std::cout << "Lineare Funktion: " << mid(c0 - iapib*c1/ibsia) << "+" << mid(c12)<<"*x" << std::endl;
	 // std::cout << "Bound " << c0 + c1*iv_t(-1,1) << std::endl;
	// c0 -= c1*iapib/ibsia;

	err = aff_op_t::scale_add(ac, 0.0, 0.0,
				  iv_traits::my_inf(c12), iv_traits::my_sup(c12),
				  iv_traits::my_inf(c0), iv_traits::my_sup(c0), rnd);
	err += apprerr(c0, c12);


	//std::cout << "c0 " << c0 << " c12 " << c12 << std::endl;
	err *= 0.5;
	return aerror_t(err, yalaa::fp::get_flags(err) | flags);
      }

    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV>
    T ChebyshevFP<T, ET, AC, AFFOP, IV>::eval_poly_lb(T lbc0, T lbc1, T lbx)
    {
      // Gesucht wird der LB der Polyauswertung
      // Annahme: rnd.upward()
      return -(lbc0 - (-lbc1)*lbx);
    }


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

      template<typename T, template<typename> class ET,
               template<typename, template<typename> class> class AC,
               class AFFOP,
               class IV>
      typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t 
      ChebyshevFP<T, ET, AC, AFFOP, IV>::cheb_powr(ac_t *ac, const iv_t &d, int p, unsigned q) 
      {
	int q1 = static_cast<int>(q);
	yalaa::fp::RndControl rnd;
	return chebyshev(ac, d, [p, q](const iv_t &a)->iv_t { return iv_traits::my_powr(a, p, q); }, 
			 false, [&d, p, q1](const iv_t&, const iv_t&)->T  
			 { return self_t::lag_rem(d, iv_traits::my_mul(iv_traits::my_div(iv_t(p*(p-q1)), iv_t(q1*q1)),
									iv_traits::my_powr(d, (p - q1) - q1, q1))); }, rnd);
      }

      template<typename T, template<typename> class ET,
               template<typename, template<typename> class> class AC,
               class AFFOP,
               class IV>
      typename ChebyshevFP<T, ET, AC, AFFOP, IV>::aerror_t 
      ChebyshevFP<T, ET, AC, AFFOP, IV>::cheb_inv(ac_t *ac, const iv_t &d) 
      {
	yalaa::fp::RndControl rnd;
	return chebyshev(ac, d, [](const iv_t &a)->iv_t { return iv_traits::my_div(iv_traits::my_one(), a); },
			 false, [&d](const iv_t&, const iv_t&)->T { 
			   return self_t::lag_rem(d, iv_traits::my_div(iv_t(2.0, 2.0), iv_traits::my_pow(d,3))); },
			 rnd);
      }


    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV>
    T ChebyshevFP<T, ET, AC, AFFOP, IV>::atan_d2_eval(T d)
    {
      return (-2*d)/((d*d+1.0)*(d*d+1.0));
    }
      

    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV>
    typename ChebyshevFP<T, ET, AC, AFFOP, IV>::iv_t ChebyshevFP<T, ET, AC, AFFOP, IV>::atan_d2(const iv_t &d, yalaa::fp::RndControl &rnd)
    {
      //std::cout << "ATAN Input " << d << std::endl;
      // TODO: Konstanten verschieben
      static T S_SQRT3_INV_INF(iv_traits::my_inf(iv_traits::my_div(iv_traits::my_one(), iv_traits::my_sqrt(iv_t(3.0, 3.0)))));
      static T S_SQRT3_INV_SUP(iv_traits::my_sup(iv_traits::my_div(iv_traits::my_one(), iv_traits::my_sqrt(iv_t(3.0, 3.0)))));
      static T S_G_MINMAX_INF(iv_traits::my_inf(iv_traits::my_div(iv_traits::my_mul(iv_t(3.0, 3.0), iv_traits::my_sqrt(iv_t(3.0, 3.0))), iv_t(8.0, 8.0))));
      static T S_G_MINMAX_SUP(iv_traits::my_sup(iv_traits::my_div(iv_traits::my_mul(iv_t(3.0, 3.0), iv_traits::my_sqrt(iv_t(3.0, 3.0))), iv_t(8.0, 8.0))));
      
      // T a(iv_traits::my_inf(d));
      // T b(iv_traits::my_sup(d));
      bool a = iv_traits::my_inf(d) > -S_SQRT3_INV_INF;
      bool b = iv_traits::my_sup(d) <  S_SQRT3_INV_SUP;
      T inf(iv_traits::my_inf(d));
      T sup(iv_traits::my_sup(d));
    
      if(a && b) {// 1
	//std::cout << "Fall 1" << std::endl;
	rnd.upward();
	T rsup(atan_d2_eval(inf));
	rnd.downward();
	return iv_t(atan_d2_eval(sup), rsup);
      }
      else if(-S_SQRT3_INV_INF > sup ||
	      S_SQRT3_INV_SUP < inf) { // 2
	//std::cout << "Fall 2" << std::endl;
	rnd.upward();
	T rsup(atan_d2_eval(sup));
	rnd.downward();
	return iv_t(atan_d2_eval(inf), rsup);
      }
      else if(inf < -S_SQRT3_INV_INF &&
	      sup >  S_SQRT3_INV_SUP) {//3 
	//std::cout << "Fall 3" << std::endl;
	return iv_t(-S_G_MINMAX_INF, S_G_MINMAX_SUP);
      }
      else if(a) { //4 
	//std::cout << "Fall 4" << std::endl;
	rnd.upward();
	return iv_t(-S_G_MINMAX_INF, std::max(atan_d2_eval(inf), atan_d2_eval(sup)));
      }
      else if(b) { // 5
	//std::cout << "Fall 5" << std::endl;
	rnd.downward();
	return iv_t(std::min(atan_d2_eval(inf), atan_d2_eval(sup)), S_G_MINMAX_SUP);
      }
      assert(!"Invalid case.");
      return iv_t(1, -1); // Dummy
    }
      


    }
  }
}

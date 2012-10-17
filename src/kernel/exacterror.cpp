namespace yalaa
{
  namespace kernel
  {
    template<typename T, template<typename> class ET,
             template<typename, template<typename> class> class AC, class IV>
    typename ExactErrorFP<T, ET, AC, IV>::aerror_t
    ExactErrorFP<T, ET, AC, IV>::rootn(ac_t *ac, iv_t d, int q)
    {
      if(!q)
	return aerror_t(0.0, aerror_t::I_ERROR);
      
      // x^1 = id(x)
      if(q == 1) {
	return aerror_t(0.0, 0);
      }

      if(q < 0 && iv_traits::my_inf(d) <= 0 && iv_traits::my_sup(d) >= 0) {
	// Funktion ist undefiniert für 0
	// TODO: ist aerror_t::UNBOUND korrekt hier?
	ac->clear();
	return aerror_t(0.0, (iv_traits::my_inf(d) == iv_traits::my_sup(d) ?
			      aerror_t::C_D_VIOL : aerror_t::P_D_VIOL) | aerror_t::UNBOUND);
      }


      unsigned flags = 0;
      if(q & 0x1) {
	if(iv_traits::my_inf(d) < 0.0 && iv_traits::my_sup(d) > 0.0)
	  return details::ChebyshevFP<T, ET, AC, details::ExactErrorAffineFP<T, ET, AC>, IV>::cheb_rootn(ac, d, q);
      }
      else if(iv_traits::my_sup(d) < 0) {
	ac->clear();
	return aerror_t(0.0, aerror_t::C_D_VIOL);
      }
      else if(iv_traits::my_inf(d) < 0) {
	d = iv_t(0, iv_traits::my_sup(d));
	flags |= aerror_t::P_D_VIOL;
      }

      // Funktion ist strikt konvex/konkav
      aerror_t e(details::MinRangeFP<T, ET, AC, details::ExactErrorAffineFP<T, ET, AC>, IV>::minr_rootn(ac, d, q));
      e.set_error(e.error() | flags);
      return e; 
    }

    template<typename T, template<typename> class ET,
             template<typename, template<typename> class> class AC, class IV>
    typename ExactErrorFP<T, ET, AC, IV>::aerror_t
    ExactErrorFP<T, ET, AC, IV>::powr(ac_t *ac, iv_t d, int p, unsigned q)
    {
      if(!q)
 	return aerror_t(0.0, aerror_t::I_ERROR);
      unsigned p1 = std::abs(p), q1 = q, t;
      while(q1) {
 	t = p1 % q1;
 	p1 = q1;
 	q1 = t;
      }
      p /= static_cast<int>(p1);
      q /= p1;

      // x^1 = id(x)
      if(p == 1 && q == 1) {
 	return aerror_t(0.0, 0);
      }

      if(p < 0 && iv_traits::my_inf(d) <= 0 && iv_traits::my_sup(d) >= 0) {
 	// Funktion ist undefiniert für 0
 	// TODO: ist aerror_t::UNBOUND korrekt hier?
 	ac->clear();
 	return aerror_t(0.0, (iv_traits::my_inf(d) == iv_traits::my_sup(d) ?
 			      aerror_t::C_D_VIOL : aerror_t::P_D_VIOL) | aerror_t::UNBOUND);
      }
      
      unsigned flags = 0;
      if(q & 0x1) {
 	if(p & 0x1) {
 	  // nicht konvex/konkaver Fall...
 	  // kein min_range
 	  return details::ChebyshevFP<T, ET, AC, details::ExactErrorAffineFP<T, ET, AC>, IV>::cheb_powr(ac, d, p, q);
 	}
 	else {
 	  // strikt konvex, konkav
 	  // MinRange
 	  return details::MinRangeFP<T, ET, AC, details::ExactErrorAffineFP<T, ET, AC>, IV>::minr_powr(ac, d, p, q);
 	}
      }
      else {
 	if(iv_traits::my_sup(d) < 0) {
 	  ac->clear();
 	  return aerror_t(0.0, aerror_t::C_D_VIOL);
 	}
 	else if(iv_traits::my_inf(d) < 0) {
 	  d = iv_t(0, iv_traits::my_sup(d));
 	  flags |= aerror_t::P_D_VIOL;
 	}
 	// Q ist gerade
 	// MinRange
 	aerror_t e(details::MinRangeFP<T, ET, AC, details::ExactErrorAffineFP<T, ET, AC>, IV>::minr_powr(ac, d, p, q));
 	e.set_error(e.error() | flags);
 	return e;
      }
    }

    template<typename T, template<typename> class ET,
             template<typename, template<typename> class> class AC, class IV>
    typename ExactErrorFP<T, ET, AC, IV>::aerror_t
    ExactErrorFP<T, ET, AC, IV>::inv(ac_t *ac, const iv_t &d) 
    {
      return details::MinRangeFP<T, ET, AC, details::ExactErrorAffineFP<T, ET, AC>, IV>::minr_inv(ac, d);
    }  
  }
}


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

#define YALAA_AFF_TEMPLATE template<typename T, template<typename> class ET, \
                                    template<typename, template<typename> class> class AC, \
                                    template<typename, template<typename> class, template<typename, template<typename> class> class, class> class AR, \
                                    template<typename, template<typename> class, template<typename, template<typename> class> class> class AP, \
                                    template<typename, typename> class EP, typename IV>
#define YALAA_DECL AffineForm<T, ET, AC, AR, AP, EP, IV>
#define YALAA_DECL_T typename AffineForm<T, ET, AC, AR, AP, EP, IV>
#define YALAA_FRIEND_DEF   template<typename AF>                        \
  typename boost::enable_if<details::has_trait_is_aff_t<AF>,AF>::type
#define YALAA_FRIEND_DECL   template<typename AF>                       \
  friend typename boost::enable_if<details::has_trait_is_aff_t<AF>,AF>::type


namespace yalaa
{
  YALAA_AFF_TEMPLATE
  typename AffineForm<T, ET, AC, AR, AP, EP, IV>::iv_t
  to_iv(const AffineForm<T, ET, AC, AR, AP, EP, IV> &af)
  {
    typedef AffineForm<T, ET, AC, AR, AP, EP, IV> aff_f_t;
    typedef yalaa::details::base_traits<typename aff_f_t::iv_t> iv_traits;
    const typename aff_f_t::ac_t & ac= af.ac();
    typename aff_f_t::iv_t iv(ac.central(), ac.central());
    typename aff_f_t::iv_t eps(-yalaa::details::base_traits<typename aff_f_t::base_t>::my_one(),
                               yalaa::details::base_traits<typename aff_f_t::base_t>::my_one());
    for(typename aff_f_t::ac_t::aff_comb_const_iter it(ac.begin()); it != ac.end(); ++it)
      iv += iv_traits::my_mul(typename aff_f_t::iv_t(it->dev()),eps);
    return iv;
  }

  YALAA_AFF_TEMPLATE
  typename AffineForm<T, ET, AC, AR, AP, EP, IV>::base_t
  rad(const AffineForm<T, ET, AC, AR, AP, EP, IV> &af)
  {
    typedef AffineForm<T, ET, AC, AR, AP, EP, IV> aff_f_t;
    typedef yalaa::details::base_traits<typename aff_f_t::iv_t> trait_t;
    typename aff_f_t::iv_t iv(to_iv(af));
    return trait_t::my_sup(trait_t::my_div(iv, trait_t::my_add(trait_t::my_one(),trait_t::my_one())));
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL::AffineForm(base_ref_t scalar)
  {
    if(ep_t::new_form(this, scalar))
      m_a.set_central(scalar);
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL::AffineForm(const iv_t &iv)
  {
    if(ep_t::new_form(this, iv)) {
      m_a.set_central(iv_traits::my_mid(iv));
      ap_t::new_form(&m_a, iv_traits::my_rad(iv));
    }
  }

  YALAA_AFF_TEMPLATE
  const YALAA_DECL_T::ac_t& YALAA_DECL::ac() const
  {
    return m_a;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::ac_t& YALAA_DECL::ac()
  {
    return m_a;
  }

  // aff °= aff
  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator+=(const self_t &other)
  {
    if(ep_t::pre_op(this, other)) {
      typename ar_t::aerror_t error(ar_t::add(&m_a, other.m_a));
      ap_t::add_errors(&m_a, error);
      ep_t::post_op(this, other, error);
    }
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator-=(const self_t &other)
  {
    if(ep_t::pre_op(this, other)) {
      typename ar_t::aerror_t error(ar_t::sub(&m_a, other.m_a));
      ap_t::add_errors(&m_a, error);
      ep_t::post_op(this, other, error);
    }
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator*=(const self_t &other)
  {
    if(ep_t::pre_op(this, other)) {
      typename ar_t::aerror_t error(ar_t::mul(&m_a, other.m_a, rad(*this), rad(other)));
      ap_t::add_errors(&m_a, error);
      ep_t::post_op(this, other, error);
    }
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator/=(const self_t &other)
  {
    // TODO: Fixme
    // Die Divisionsoperation muesste letztlich elementar im Kernel stattfinden
    // oder zumindest nur ein Errorsymbol hinzufügen
    // Problem: AffineForm hat (abseits von base_traits) keine Ahnung von base_t,
    // d.h. kann insbesondere auch keine passende Rundungsop durchführen. Der derzeitige
    // Workaround stellt damit sicher, dass beide Fehler voll eingehen.
    self_t oinv(other);
    if(ep_t::pre_op(this, oinv)) {
      typename ar_t::aerror_t error1(ar_t::inv(&oinv.m_a, to_iv(oinv)));
      ap_t::add_errors(&oinv.m_a, error1);
      ep_t::post_op(this, oinv, error1);
      if(ep_t::pre_op(this, oinv)) {
	typename ar_t::aerror_t error2(ar_t::mul(&m_a, oinv.m_a, rad(*this), rad(oinv)));
	ap_t::add_errors(&m_a, error2);
	ep_t::post_op(this, other, error2);
      }
    }


    // if(ep_t::pre_op(other)) {
    //   ac_t inv(other.m_a);
    //   typename ar_t::aerror_t error1(ar_t::inv(&inv, to_iv(inv)));
    //   ap_t::add_errors(&m_a, error1);
    //   ep_t::post_op(this, other, error1);
    //   if(ep_t::pre_op(this, other)) {
    //     typename ar_t::aerror_t error2(ar_t::mul(&m_a, other.m_a, rad(*this), rad(other)));
    //     ap_t::add_errors(&m_a, error2);
    //     ep_t::post_op(this, other, error2);
    //   }
    // }
    return *this;
  }

  // aff °= base_t
  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator+=(base_ref_t s)
  {
    if(ep_t::pre_op(this, s)) {
      typename ar_t::aerror_t error(ar_t::add(&m_a, s));
      ap_t::add_errors(&m_a, error);
      ep_t::post_op(this, s, error);
    }
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator-=(base_ref_t s)
  {
    // TODO: Wenn base_t nicht exakt negiert werden kann, ist diese Stelle problematisch
    // Dokumentieren oder in Kernel mit ordentlicher Fehlerpropagation verschieben
    if(ep_t::pre_op(this, s)) {
      typename ar_t::aerror_t error(ar_t::add(&m_a, yalaa::details::base_traits<base_t>::my_neg(s)));
      ap_t::add_errors(&m_a, error);
      ep_t::post_op(this, s, error);
    }
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator*=(base_ref_t s)
  {
    if(ep_t::pre_op(this, s)) {
      typename ar_t::aerror_t error(ar_t::scale(&m_a, s));
      ap_t::add_errors(&m_a, error);
      ep_t::post_op(this, s, error);
    }
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator/=(base_ref_t s)
  {
    if(ep_t::pre_op(this, s)) {
      typename ar_t::aerror_t error(ar_t::inv_scale(&m_a, s));
      ap_t::add_errors(&m_a, error);
      ep_t::post_op(this, s, error);
    }
    return *this;
  }

  // aff °= iv_t
  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator+=(const iv_t &iv)
  {
    if(ep_t::pre_op(this, iv)) {
      ac_t aiv(iv_traits::my_mid(iv));
      ap_t::add_uncert(&aiv, iv_traits::my_rad(iv));
      typename ar_t::aerror_t error(ar_t::add(&m_a, aiv));
      ap_t::add_errors(&m_a, error);
      ep_t::post_op(this, iv, error);
    }
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator-=(const iv_t &iv)
  {
    if(ep_t::pre_op(this, iv)) {
      ac_t aiv(iv_traits::my_mid(iv));
      ap_t::add_uncert(&aiv, iv_traits::my_rad(iv));
      typename ar_t::aerror_t error(ar_t::sub(&m_a, aiv));
      ap_t::add_errors(&m_a, error);
      ep_t::post_op(this, iv, error);
    }
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator*=(const iv_t &iv)
  {
    if(ep_t::pre_op(this, iv)) {
      ac_t aiv(iv_traits::my_mid(iv));
      base_t uc(iv_traits::my_rad(iv));
      ap_t::add_uncert(&aiv, uc);
      typename ar_t::aerror_t error(ar_t::mul(&m_a, aiv, rad(*this), uc));
      ap_t::add_errors(&m_a, error);
      ep_t::post_op(this, iv, error);
    }
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator/=(const iv_t &iv)
  {
    if(ep_t::pre_op(this)) {
      ac_t aiv(iv_traits::my_mid(iv));
      base_t uc(iv_traits::my_rad(iv));
      ap_t::add_uncert(&aiv, uc);
      typename ar_t::aerror_t error1(ar_t::inv(&m_a, to_iv(*this)));
      ap_t::add_errors(&m_a, error1);
      ep_t::post_op(this, error1);
      if(ep_t::pre_op(this, iv)) {
        typename ar_t::aerror_t error2(ar_t::mul(&m_a, aiv, rad(*this), uc));
        ap_t::add_errors(&m_a, error2);
        ep_t::post_op(this, error2);
      }
    }
    return *this;
  }

  // misc
  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator-()
  {
    if(ep_t::pre_op(this)) {
      typename ar_t::aerror_t error(ar_t::neg(&m_a));
      ap_t::add_errors(&m_a, error);
      ep_t::post_op(this, error);
    }
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator+()
  {
    return *this;
  }

  YALAA_AFF_TEMPLATE
  bool YALAA_DECL::operator==(const self_t &other) const
  {
    if(other.m_a.size() == m_a.size() && other.m_a.central() == m_a.central()) {
      typename ac_t::aff_comb_const_iter it2(other.m_a.begin());
      for(typename ac_t::aff_comb_const_iter it1(m_a.begin()); it1 != m_a.end(); ++it1) {
if(!(*it1 == *it2) || it1->dev() != it2->dev())
	  return false;
	++it2;
      }
      return true;
    }
    return false;
  }

  // elementary
  /** 
   * Base e exponential function 
   * 
   * @param af form
   * 
   * @return exp(af)
   */
  YALAA_FRIEND_DEF
  exp(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      typename AF::ar_t::aerror_t error(AF::ar_t::exp(&af.m_a, to_iv(af)));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  /** 
   * Base 2 exponential function 
   * 
   * @param af affine form
   * 
   * @return 2^af
   */
  YALAA_FRIEND_DEF
  exp2(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      typename AF::ar_t::aerror_t error(AF::ar_t::exp2(&af.m_a, to_iv(af)));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

/** 
 * Base 10 exponential function 
 * 
 * @param af affine form
 * 
 * @return 10^af
 */
  YALAA_FRIEND_DEF
  exp10(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      typename AF::ar_t::aerror_t error(AF::ar_t::exp10(&af.m_a, to_iv(af)));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  /** 
   * Base e exponential function minus 1
   * 
   * @param af affine form
   * 
   * @return e^af - 1
   */
  YALAA_FRIEND_DEF
  expm1(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      typename AF::ar_t::aerror_t error(AF::ar_t::expm1(&af.m_a, to_iv(af)));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  /** 
   * Base 2 exponential function minus 1
   * 
   * @param af affine form
   * 
   * @return 2^af - 1
   */
  YALAA_FRIEND_DEF
  exp2m1(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      typename AF::ar_t::aerror_t error(AF::ar_t::exp2m1(&af.m_a, to_iv(af)));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  /** 
   * Base 10 exponential function minus 1
   * 
   * @param af affine form
   * 
   * @return 10^af - 1
   */
  YALAA_FRIEND_DEF
  exp10m1(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      typename AF::ar_t::aerror_t error(AF::ar_t::exp10m1(&af.m_a, to_iv(af)));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }


  /** 
   * Square root
   * 
   * @param af affine form
   * 
   * @return sqrt(af)
   */
  YALAA_FRIEND_DEF
  sqrt(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t& domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::sqrt(&af.m_a,
						       yalaa::details::base_traits<typename AF::iv_t>::my_inf(domain),
						       yalaa::details::base_traits<typename AF::iv_t>::my_sup(domain)));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  /** 
   * Square
   * Note: This function is in general tighter than af*af
   * 
   * @param af affine form
   * 
   * @return af^2 
   */
  YALAA_FRIEND_DEF
  sqr(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      typename AF::ar_t::aerror_t error(AF::ar_t::sqr(&af.m_a, rad(af)));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  /** 
   * Integer power function
   * 
   * @param af base (affine form)
   * @param exp exponent
   * 
   * @return af^exp
   */
  YALAA_FRIEND_DEF
  pown(AF af, int exp)
  {
    if(exp < 0 && AF::ep_t::pre_op(&af)) {
      typename AF::ar_t::aerror_t error1(AF::ar_t::inv(&af.m_a, to_iv(af)));
      AF::ap_t::add_errors(&af.m_a, error1);
      AF::ep_t::post_op(&af, error1);
    }

    if(AF::ep_t::pre_op(&af)) {
      typename AF::ar_t::aerror_t error2(AF::ar_t::pown(&af.m_a, abs(exp), rad(af)));
      AF::ap_t::add_errors(&af.m_a, error2);
      AF::ep_t::post_op(&af, error2);
    }


    return af;
  }

  /** 
   * Power function
   * 
   * @param af base (affine form)
   * @param exp exponent (affine form)
   * 
   * @return exp(ln(af)*exp)
   */
  YALAA_FRIEND_DEF
  pow(AF af, const AF &exp)
  {
    // af^exp = exp(ln(af)*exp)

    //ln(af)
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t & afd = to_iv(af);
      typename AF::ar_t::aerror_t error(0.0, AF::ar_t::aerror_t::I_ERROR);
      if(AF::iv_traits::my_inf(afd) > yalaa::details::base_traits<typename AF::base_t>::my_zero())
	error = AF::ar_t::log(&af.m_a, afd);
       AF::ap_t::add_errors(&af.m_a, error);
       AF::ep_t::post_op(&af, error);
    }

    //ln(af)*exp
    if(AF::ep_t::pre_op(&af)) {
      typename AF::ar_t::aerror_t error(AF::ar_t::mul(&af.m_a, exp.m_a, rad(af), rad(exp)));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }

    //exp(ln(af)*exp)
    if(AF::ep_t::pre_op(&af)) {
      typename AF::ar_t::aerror_t error(AF::ar_t::exp(&af.m_a, to_iv(exp)));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }

    return af;
  }

  YALAA_FRIEND_DEF
  log(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t& domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::log(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  log2(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t& domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::log2(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  log10(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t& domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::log10(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  logp1(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t& domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::logp1(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  log2p1(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t& domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::log2p1(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  log10p1(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t& domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::log10p1(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  sin(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t& domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::sin(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  cos(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t& domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::cos(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  tan(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t&domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::tan(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  asin(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t&domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::asin(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  acos(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t&domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::acos(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  atan(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t&domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::atan(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  sinh(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t&domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::sinh(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  cosh(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t&domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::cosh(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  tanh(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t&domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::tanh(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  asinh(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t&domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::asinh(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  acosh(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t&domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::acosh(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  atanh(AF af)
  {
    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t&domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::atanh(&af.m_a, domain));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  YALAA_FRIEND_DEF
  powr(AF af, int p, unsigned q)
  {
    // if(p < 0 && AF::ep_t::pre_op(&af)) {
    //   typename AF::ar_t::aerror_t error1(AF::ar_t::inv(&af.m_a, to_iv(af)));
    //   AF::ap_t::add_errors(&af.m_a, error1);
    //   AF::ep_t::post_op(&af, error1);
    // }

    // if(AF::ep_t::pre_op(&af)) {
    //   typename AF::ar_t::aerror_t error2(AF::ar_t::pown(&af.m_a, abs(p), rad(af)));
    //   AF::ap_t::add_errors(&af.m_a, error2);
    //   AF::ep_t::post_op(&af, error2);
    // }

    // if(AF::ep_t::pre_op(&af)) {
    //   typename AF::ar_t::aerror_t error3(AF::ar_t::rootn(&af.m_a, to_iv(af), q));
    //   AF::ap_t::add_errors(&af.m_a, error3);
    //   AF::ep_t::post_op(&af, error3);
    // }

    if(AF::ep_t::pre_op(&af)) {
      const typename AF::iv_t&domain = to_iv(af);
      typename AF::ar_t::aerror_t error(AF::ar_t::powr(&af.m_a, domain, p, q));
      AF::ap_t::add_errors(&af.m_a, error);
      AF::ep_t::post_op(&af, error);
    }
    return af;
  }

  
}

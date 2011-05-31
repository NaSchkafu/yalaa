// -*-c++-*-
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
    :m_a(yalaa::details::base_traits<base_t>::my_zero())
  { 
    if(!ep_t::new_form(*this, scalar))
      m_a.set_central(scalar);
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL::AffineForm(const iv_t &iv)
  {
    if(!ep_t::new_form(*this, iv)) {
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
    if(!ep_t::pre_op(*this, other)) {
      typename ar_t::aerror_t error(ar_t::add(&m_a, other.m_a));
      ap_t::add_errors(&m_a, error);
      ep_t::post_op(*this, other, error);
    }
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator-=(const self_t &other)
  {
    if(!ep_t::pre_op(*this, other)) {
      typename ar_t::aerror_t error(ar_t::sub(&m_a, other.m_a));
      ap_t::add_errors(&m_a, error);
      ep_t::post_op(*this, other, error);
    }
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator*=(const self_t &other)
  {
    if(!ep_t::pre_op(*this, other)) {
      typename ar_t::aerror_t error(ar_t::mul(&m_a, other.m_a, rad(*this), rad(other)));
      ap_t::add_errors(&m_a, error);
      ep_t::post_op(*this, other, error);
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
    typename ar_t::aerror_t error1(ar_t::inv(&m_a, to_iv(*this)));
    typename ar_t::aerror_t error2(ar_t::mul(&m_a, other.m_a, rad(*this), rad(other)));
    ap_t::add_errors(&m_a, error1);
    ap_t::add_errors(&m_a, error2);
    return *this;
  }

  // aff °= base_t
  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator+=(base_ref_t s)
  {
    typename ar_t::aerror_t error(ar_t::add(&m_a, s));
    ap_t::add_errors(&m_a, error);
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator-=(base_ref_t s)
  {
    // TODO: Wenn base_t nicht exakt negiert werden kann, ist diese Stelle problematisch
    // Dokumentieren oder in Kernel mit ordentlicher Fehlerpropagation verschieben
    typename ar_t::aerror_t error(ar_t::add(&m_a, yalaa::details::base_traits<base_t>::my_neg(s)));
    ap_t::add_errors(&m_a, error);
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator*=(base_ref_t s)
  {
    typename ar_t::aerror_t error(ar_t::scale(&m_a, s));
    ap_t::add_errors(&m_a, error);
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator/=(base_ref_t s)
  {
    typename ar_t::aerror_t error(ar_t::inv_scale(&m_a, s));
    ap_t::add_errors(&m_a, error);
    return *this;
  }

  // aff °= iv_t
  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator+=(const iv_t &iv)
  {
    ac_t aiv(iv_traits::my_mid(iv));
    ap_t::add_uncert(&aiv, iv_traits::my_rad(iv));
    typename ar_t::aerror_t error(ar_t::add(&m_a, aiv));
    ap_t::add_errors(&m_a, error);
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator-=(const iv_t &iv)
  {
    ac_t aiv(iv_traits::my_mid(iv));
    ap_t::add_uncert(&aiv, iv_traits::my_rad(iv));
    typename ar_t::aerror_t error(ar_t::sub(&m_a, aiv));
    ap_t::add_errors(&m_a, error);
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator*=(const iv_t &iv)
  {
    ac_t aiv(iv_traits::my_mid(iv));
    base_t uc(iv_traits::my_rad(iv));
    ap_t::add_uncert(&aiv, uc);
    typename ar_t::aerror_t error(ar_t::mul(&m_a, aiv, rad(*this), uc));
    ap_t::add_errors(&m_a, error);
    return *this;
  }

  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator/=(const iv_t &iv)
  {
    ac_t aiv(iv_traits::my_mid(iv));
    base_t uc(iv_traits::my_rad(iv));
    ap_t::add_uncert(&aiv, uc);
    typename ar_t::aerror_t error1(ar_t::inv(&m_a, to_iv(*this)));
    typename ar_t::aerror_t error2(ar_t::mul(&m_a, aiv, rad(*this), uc));
    ap_t::add_errors(&m_a, error1);
    ap_t::add_errors(&m_a, error2);
    return *this;
  }
    
  // misc
  YALAA_AFF_TEMPLATE
  YALAA_DECL_T::self_t& YALAA_DECL::operator-()
  {
    typename ar_t::aerror_t error(ar_t::neg(&m_a));
    ap_t::add_errors(&m_a, error);
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
  YALAA_FRIEND_DEF
  exp(AF af)
  {
    typename AF::ar_t::aerror_t error(AF::ar_t::exp(&af.m_a, to_iv(af)));
    AF::ap_t::add_errors(&af.m_a, error);
    return af;
  }

  YALAA_FRIEND_DEF
  sqrt(AF af)
  {
    const typename AF::iv_t& domain = to_iv(af);
    typename AF::ar_t::aerror_t error(AF::ar_t::sqrt(&af.m_a, 
						     yalaa::details::base_traits<typename AF::iv_t>::my_inf(domain), 
						     yalaa::details::base_traits<typename AF::iv_t>::my_sup(domain)));
    AF::ap_t::add_errors(&af.m_a, error);
    return af;
  }

  YALAA_FRIEND_DEF
  sqr(AF af)
  {
    typename AF::ar_t::aerror_t error(AF::ar_t::sqr(&af.m_a, rad(af)));
    AF::ap_t::add_errors(&af.m_a, error);
    return af;
  }

  YALAA_FRIEND_DEF
  pow(AF af, int exp) 
  {
    typename AF::ar_t::aerror_t error(AF::ar_t::pow(&af.m_a, abs(exp), rad(af)));
    AF::ap_t::add_errors(&af.m_a, error);
    // TODO: Neg. Exp
    // return inv(af)
    return af;
  }

  YALAA_FRIEND_DEF
  ln(AF af) 
  {
    const typename AF::iv_t& domain = to_iv(af);
    typename AF::ar_t::aerror_t error(AF::ar_t::ln(&af.m_a, domain));
    AF::ap_t::add_errors(&af.m_a, error);
    return af;
  }

  YALAA_FRIEND_DEF
  sin(AF af)
  {
    const typename AF::iv_t& domain = to_iv(af);
    typename AF::ar_t::aerror_t error(AF::ar_t::sin(&af.m_a, domain));
    AF::ap_t::add_errors(&af.m_a, error);
    return af;
  }

  YALAA_FRIEND_DEF
  cos(AF af)
  {
    const typename AF::iv_t& domain = to_iv(af);
    typename AF::ar_t::aerror_t error(AF::ar_t::cos(&af.m_a, domain));
    AF::ap_t::add_errors(&af.m_a, error);
    return af;
  }
}

// -*-c++-*-

template<typename T, template<typename> class ET, 
	 template<typename, template<typename> class> class AC>
void AF2<T, ET, AC>::add_errors(AC<T, ET> *ac, const yalaa::details::ArithmeticError<T> &err)
{
  add_special(ac, err.gen(), yalaa::details::SpecialErrTerm::GEN_ERR);
  add_special(ac, err.pos(), yalaa::details::SpecialErrTerm::POS_ERR);
  add_special(ac, err.neg(), yalaa::details::SpecialErrTerm::NEG_ERR);
}

template<typename T, template<typename> class ET, 
	 template<typename, template<typename> class> class AC>
void AF2<T, ET, AC>::new_form(AC<T, ET> *ac, base_ref_t uncert) 
{
  assert(!"AF2 is currently not supported. Changes in AffineCombBaseOp are necessary!"); 
  if(uncert != b_traits_t::my_zero())
    ac->insert(typename AC<T,ET>::error_t(uncert));
}

template<typename T, template<typename> class ET, 
	 template<typename, template<typename> class> class AC>
void AF2<T, ET, AC>::add_uncert(AC<T, ET> *ac, base_ref_t uncert)
{
  add_special(ac, uncert, yalaa::details::SpecialErrTerm::GEN_ERR);
}

template<typename T, template<typename> class ET, 
	 template<typename, template<typename> class> class AC>
void AF2<T, ET, AC>::add_special(AC<T, ET> *ac, base_ref_t uncert, 
				 yalaa::details::SpecialErrTerm::special_t type) 
{
  if(uncert != b_traits_t::my_zero()) {
    error_t s;
    s.set_special(type);
    typename ac_t::aff_comb_iter it(ac->find(s));
    if(it != ac->end())
      it->set_dev(b_traits_t::my_add_up(b_traits_t::my_abs(it->dev()), b_traits_t::my_abs(uncert)));
    else {
      typename ac_t::error_t errt(uncert);
      errt.set_special(type);
      ac->insert(errt);
    }
  }
}  


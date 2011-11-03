#ifndef __IA_AA_HPP__
#define __IA_AA_HPP__

namespace yalaa 
{
  namespace fp 
  {

    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC,
	     class AFFOP,
	     class IV, class AERROR>
    AERROR ia_to_ac(AC<T, ET> *ac, const IV &r, yalaa::fp::RndControl &rnd, unsigned flags = 0) 
    {
      typedef IV iv_t;
      typedef yalaa::traits::interval_traits<iv_t> iv_traits;
      typedef AERROR aerror_t;
      T err(0.0);
      if(iv_traits::my_inf(r) > iv_traits::my_sup(r))
	flags |= aerror_t::I_ERROR;
      else {
	iv_t central(iv_traits::my_div(iv_traits::my_add(iv_t(iv_traits::my_inf(r), iv_traits::my_inf(r)), 
							 iv_t(iv_traits::my_sup(r), iv_traits::my_sup(r))), iv_t(2.0, 2.0)));
	flags |= yalaa::fp::get_flags(iv_traits::my_inf(r)) | 
	  yalaa::fp::get_flags(iv_traits::my_sup(r));
	err = AFFOP::scale_add(ac, 0.0, 0.0, 0.0, 0.0, iv_traits::my_inf(central), iv_traits::my_sup(central), rnd);
      }
      rnd.upward();
      return aerror_t(iv_traits::my_w(r) + err, flags);
    }
  }
}

#endif /*__IA_AA_HPP__*/


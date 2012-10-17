namespace yalaa
{
  namespace kernel
  {
    namespace details
    {
      template<typename T, template<typename> class ET,
               template<typename, template<typename> class> class AC, 
	       class AFFOP, class IV>
      typename MiscFP<T, ET, AC, AFFOP, IV>::aerror_t
      MiscFP<T, ET, AC, AFFOP, IV>::abs(ac_t *ac, const iv_t &d)
      {
	// Impl. von abs
	// Linearisierung von abs basiert auf (Beauman, 1998)
	T alpha = 0.0, beta = 0.0, err = 0.0;
	T lb = iv_traits::my_inf(d);
	T ub = iv_traits::my_sup(d);
	yalaa::fp::RndControl rnd;
	rnd.upward();
	if(lb >= 0.0)
	  alpha = 1.0;
	else if(ub <= 0.0)
	  alpha = -1.0;
	else {
	  iv_t hn(yalaa::fp::fast_sub_dd_up<T, IV>(ub, lb));
	  // Obere Grenze für beta
	  beta = (-lb)*ub/iv_traits::my_inf(hn);
	  beta *= 2;
	  // Untere Grenze für alpha
	  rnd.downward();
	  alpha = (lb + ub)/iv_traits::my_sup(hn);
	}
	// Max. Fehler bei abs(0)
	err = beta;
	T err2 = aff_op_t::scale_add(ac, alpha, alpha, beta, rnd);
	return aerror_t(err2, 0.0, err, yalaa::fp::get_flags(err));
      }
    }
  }
}

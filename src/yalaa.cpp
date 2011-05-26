#include "yalaa.hpp"

// Rounding control
#include "helper/fphelper.hpp"
// internal IA operations
#include "helper/fastia.hpp" 

// Affine Operations
#include "comb/affinecombopimpl.inl"
#include "comb/affinecombimpl.inl"

// AffineForm
#include "affineform.inl"
#include "affineform_double.inl"

// Arithmetic Kernels
#include "kernel/aff/exacterroraffinefp.cpp"
#include "kernel/nonaff/mulfp.cpp"
#include "kernel/nonaff/minrangefp.cpp"
#include "kernel/nonaff/chebyshevfp.cpp"


namespace yalaa 
{
#if 0
  // float
  template class details::AffineCombImpl<float, details::ErrorTermImpl>;
  template class AffineForm<float, details::ErrorTermImpl, details::AffineCombImpl, 
			    kernel::ExactErrorFP, pol::AF0, pol::ErrorPolImpl, details::sel_iv_t>;
  template aff_e_f exp(aff_e_f);
  template aff_e_f sqrt(aff_e_f);
  template aff_e_f ln(aff_e_f);
  template aff_e_f sin(aff_e_f);
  template aff_e_f cos(aff_e_f);
  template aff_e_f sqr(aff_e_f);
  template aff_e_f pow(aff_e_f, int);
  template details::sel_iv_t to_iv(const aff_e_f&);
  template float rad(const aff_e_f&);
#endif

  // double
  template class details::AffineCombImpl<double, details::ErrorTermImpl>;
  template class AffineForm<double, details::ErrorTermImpl, details::AffineCombImpl, 
			    kernel::ExactErrorFP, pol::AF0, pol::ErrorPolImpl, details::sel_iv_t>;
  template aff_e_d exp(aff_e_d);
  template aff_e_d sqrt(aff_e_d);
  template aff_e_d ln(aff_e_d);
  template aff_e_d sin(aff_e_d);
  template aff_e_d cos(aff_e_d);
  template aff_e_d sqr(aff_e_d);
  template aff_e_d pow(aff_e_d, int);
  template details::sel_iv_t to_iv(const aff_e_d&);
  template double rad(const aff_e_d&);

#if defined(HAVE_LONG_DOUBLE_WIDER) && 0
  template class details::AffineCombImpl<long double, details::ErrorTermImpl>;
  template class AffineForm<long double, details::ErrorTermImpl, details::AffineCombImpl, 
			    kernel::ExactErrorFP, pol::AF0, pol::ErrorPolImpl, details::sel_iv_t>;
  template aff_e_ld exp(aff_e_ld);
  template aff_e_ld sqrt(aff_e_ld);
  template aff_e_ld ln(aff_e_ld);
  template aff_e_ld sin(aff_e_ld);
  template aff_e_ld cos(aff_e_ld);
  template aff_e_ld sqr(aff_e_ld);
  template aff_e_ld pow(aff_e_ld, int);
  template details::sel_iv_t to_iv(const aff_e_ld&);
  template long double rad(const aff_e_ld&);
#endif
}

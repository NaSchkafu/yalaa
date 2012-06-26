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


#include "yalaa.hpp"

// config
#include "config_sel.h"

// Rounding control
#include "helper/fphelper.hpp"
// internal IA operations
#include "helper/fastia.hpp"

// Affine Comb. // Ops
#include "comb/affinecombimpl.cpp"

// Arithmetic Kernels
#include "kernel/aff/exacterroraffinefp.cpp"
#include "kernel/exacterror.cpp"
#include "kernel/nonaff/mulfp.cpp"
#include "kernel/nonaff/minrangefp.cpp"
#include "kernel/nonaff/chebyshevfp.cpp"

#define INSTANTIATE_YALAA(TNAME, BASE, ERRORTERM, AFFINECOMB, ARKERNEL, AFFPOL, ERRPOL, IV) \
  template class AffineForm<BASE, ERRORTERM, AFFINECOMB, ARKERNEL, AFFPOL, ERRPOL, IV>; \
  template TNAME pow(TNAME, const TNAME&);                              \
  template TNAME pown(TNAME, int);                                      \
  template TNAME sqrt(TNAME);                                           \
  template TNAME exp(TNAME);                                            \
  template TNAME exp2(TNAME);                                           \
  template TNAME exp10(TNAME);                                          \
  template TNAME log(TNAME);                                            \
  template TNAME log2(TNAME);                                           \
  template TNAME log10(TNAME);                                          \
  template TNAME expm1(TNAME);                                          \
  template TNAME exp2m1(TNAME);                                         \
  template TNAME exp10m1(TNAME);                                        \
  template TNAME logp1(TNAME);                                          \
  template TNAME log2p1(TNAME);                                         \
  template TNAME log10p1(TNAME);                                        \
  template TNAME sin(TNAME);                                            \
  template TNAME cos(TNAME);                                            \
  template TNAME tan(TNAME);                                            \
  template TNAME asin(TNAME);                                           \
  template TNAME acos(TNAME);                                           \
  template TNAME atan(TNAME);                                           \
  template TNAME sinh(TNAME);                                           \
  template TNAME cosh(TNAME);                                           \
  template TNAME tanh(TNAME);                                           \
  template TNAME asinh(TNAME);                                          \
  template TNAME acosh(TNAME);                                          \
  template TNAME atanh(TNAME);                                          \
  template TNAME powr(TNAME, int, unsigned);                            \
  template typename ERRPOL<BASE, IV>::special_t get_special(const TNAME &); \
  template bool is_valid(const TNAME &);


namespace yalaa
{
#ifdef YALAA_HAVE_FLOAT_IV
  // aff_e_f
  template class details::AffineCombImpl<float, details::ErrorTermImpl>;
  template class AffineForm<float, details::ErrorTermImpl, details::AffineCombImpl,
                            kernel::ExactErrorFP, pol::AF0, pol::ErrorPolImpl, details::float_iv_t>;
  template aff_e_f exp(aff_e_f);
  template aff_e_f sqrt(aff_e_f);
  template aff_e_f ln(aff_e_f);
  template aff_e_f sin(aff_e_f);
  template aff_e_f cos(aff_e_f);
  template aff_e_f asin(aff_e_f);
  template aff_e_f sqr(aff_e_f);
  template aff_e_f pow(aff_e_f, int);
  template details::float_iv_t to_iv(const aff_e_f&);
  template float rad(const aff_e_f&);

  // aff_e_f_dec
  template class AffineForm<float, details::ErrorTermImpl, details::AffineCombImpl,
                            kernel::ExactErrorFP, pol::AF0, pol::ErrorPolImpl, details::float_iv_t>;
  template aff_e_f_dec exp(aff_e_f_dec);
  template aff_e_f_dec sqrt(aff_e_f_dec);
  template aff_e_f_dec ln(aff_e_f_dec);
  template aff_e_f_dec sin(aff_e_f_dec);
  template aff_e_f_dec cos(aff_e_f_dec);
  template aff_e_f_dec asin(aff_e_f_dec);
  template aff_e_f_dec sqr(aff_e_f_dec);
  template aff_e_f_dec pow(aff_e_f_dec, int);
  template details::float_iv_t to_iv(const aff_e_f_dec&);
  template float rad(const aff_e_f_dec&);
#endif

#ifdef YALAA_HAVE_DOUBLE_IV
  template class details::AffineCombBaseImpl<double, details::ErrorTermImpl>;
  template class details::AffineCombOpImpl<double, details::ErrorTermImpl, 
					   details::AffineCombBaseImpl>;
  template class details::AffineCombImpl<double, details::ErrorTermImpl>;
  template class kernel::details::ExactErrorAffineFP<double, details::ErrorTermImpl, 
						     details::AffineCombImpl>;
  template class kernel::details::MinRangeBuiltInFP<double, details::ErrorTermImpl,details::AffineCombImpl, 
						    kernel::details::ExactErrorAffineFP<double, details::ErrorTermImpl, details::AffineCombImpl> >;
  template class kernel::details::MinRangeFP<double, details::ErrorTermImpl, details::AffineCombImpl,
					     kernel::details::ExactErrorAffineFP<double, details::ErrorTermImpl, details::AffineCombImpl>, 
					     details::double_iv_t>;
  template class kernel::details::MultiplicationFP<double, details::ErrorTermImpl,details::AffineCombImpl,
						   kernel::details::ExactErrorAffineFP<double, details::ErrorTermImpl, details::AffineCombImpl>, 
						   details::double_iv_t>;
  template class kernel::details::ChebyshevFP<double, details::ErrorTermImpl, details::AffineCombImpl, 
					      kernel::details::ExactErrorAffineFP<double, details::ErrorTermImpl, details::AffineCombImpl>, 
					      details::double_iv_t>;
  template class kernel::ExactErrorFP<double, details::ErrorTermImpl, details::AffineCombImpl, 
				      details::double_iv_t>;
  template class yalaa::details::ErrorTermImpl<double>;
  
  INSTANTIATE_YALAA(aff_e_d, double, details::ErrorTermImpl, details::AffineCombImpl,
                    kernel::ExactErrorFP, pol::AF0, pol::ErrorPolStd, details::double_iv_t)
  INSTANTIATE_YALAA(aff_af1_e_d, double, details::ErrorTermImpl, details::AffineCombImpl,
                    kernel::ExactErrorFP, pol::AF1, pol::ErrorPolStd, details::double_iv_t)
  // INSTANTIATE_YALAA(aff_af2_e_d, double, details::ErrorTermImpl, details::AffineCombImpl,
  //                   kernel::ExactErrorFP, pol::AF2, pol::ErrorPolStd, details::double_iv_t)
  INSTANTIATE_YALAA(aff_e_d_dec, double, details::ErrorTermImpl, details::AffineCombImpl,
                    kernel::ExactErrorFP, pol::AF0, pol::ErrorPolDec, details::double_iv_t)
  INSTANTIATE_YALAA(aff_af1_e_d_dec, double, details::ErrorTermImpl, details::AffineCombImpl,
                    kernel::ExactErrorFP, pol::AF1, pol::ErrorPolDec, details::double_iv_t)
  // INSTANTIATE_YALAA(aff_af2_e_dec, double, details::ErrorTermImpl, details::AffineCombImpl,
  //                   kernel::ExactErrorFP, pol::AF2, pol::ErrorPolDec, details::double_iv_t)
#endif

#if YALAA_HAVE_L_DOUBLE_IV
  // aff_e_ld
  template class details::AffineCombImpl<long double, details::ErrorTermImpl>;
  template class AffineForm<long double, details::ErrorTermImpl, details::AffineCombImpl,
                            kernel::ExactErrorFP, pol::AF0, pol::ErrorPolImpl, details::l_double_iv_t>;
  template aff_e_ld exp(aff_e_ld);
  template aff_e_ld sqrt(aff_e_ld);
  template aff_e_ld ln(aff_e_ld);
  template aff_e_ld sin(aff_e_ld);
  template aff_e_ld cos(aff_e_ld);
  template aff_e_ld asin(aff_e_ld);
  template aff_e_ld sqr(aff_e_ld);
  template aff_e_ld pow(aff_e_ld, int);
  template details::l_double_iv_t to_iv(const aff_e_ld&);
  template long double rad(const aff_e_ld&);

  template class AffineForm<long double, details::ErrorTermImpl, details::AffineCombImpl,
                            kernel::ExactErrorFP, pol::AF0, pol::ErrorPolDec, details::l_double_iv_t>;
  template aff_e_ld_dec exp(aff_e_ld_dec);
  template aff_e_ld_dec sqrt(aff_e_ld_dec);
  template aff_e_ld_dec ln(aff_e_ld_dec);
  template aff_e_ld_dec sin(aff_e_ld_dec);
  template aff_e_ld_dec cos(aff_e_ld_dec);
  template aff_e_ld_dec asin(aff_e_ld_dec);
  template aff_e_ld_dec sqr(aff_e_ld_dec);
  template aff_e_ld_dec pow(aff_e_ld_dec, int);
  template details::l_double_iv_t to_iv(const aff_e_ld_dec&);
  template long double rad(const aff_e_ld_dec&);


#endif
}

#undef INSTANTIATE_YALAA

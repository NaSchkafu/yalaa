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
#include "kernel/nonaff/mulfp.cpp"
#include "kernel/nonaff/minrangefp.cpp"
#include "kernel/nonaff/chebyshevfp.cpp"



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
  // aff_e_d
  template class details::AffineCombImpl<double, details::ErrorTermImpl>;
  template class AffineForm<double, details::ErrorTermImpl, details::AffineCombImpl, 
			    kernel::ExactErrorFP, pol::AF0, pol::ErrorPolStd, details::double_iv_t>;
  template aff_e_d exp(aff_e_d);
  template aff_e_d sqrt(aff_e_d);
  template aff_e_d log(aff_e_d);
  template aff_e_d sin(aff_e_d);
  template aff_e_d cos(aff_e_d);
  template aff_e_d asin(aff_e_d);
  template aff_e_d acos(aff_e_d);
  template aff_e_d sqr(aff_e_d);
  template aff_e_d pown(aff_e_d, int);
  template details::double_iv_t to_iv(const aff_e_d&);
  template double rad(const aff_e_d&);

  // aff_e_d_dec
  template class AffineForm<double, details::ErrorTermImpl, details::AffineCombImpl, 
			    kernel::ExactErrorFP, pol::AF0, pol::ErrorPolDec, details::double_iv_t>;
  template aff_e_d_dec sqr(aff_e_d_dec);
  template aff_e_d_dec pown(aff_e_d_dec, int);
  template aff_e_d_dec sqrt(aff_e_d_dec);

  template aff_e_d_dec exp(aff_e_d_dec);
  template aff_e_d_dec exp2(aff_e_d_dec);
  template aff_e_d_dec exp10(aff_e_d_dec);

  template aff_e_d_dec log(aff_e_d_dec);
  template aff_e_d_dec log2(aff_e_d_dec);
  template aff_e_d_dec log10(aff_e_d_dec);

  template aff_e_d_dec expm1(aff_e_d_dec);
  template aff_e_d_dec exp2m1(aff_e_d_dec);
  template aff_e_d_dec exp10m1(aff_e_d_dec);

  template aff_e_d_dec logp1(aff_e_d_dec);
  template aff_e_d_dec log2p1(aff_e_d_dec);
  template aff_e_d_dec log10p1(aff_e_d_dec);

  template aff_e_d_dec sin(aff_e_d_dec);
  template aff_e_d_dec cos(aff_e_d_dec);
  template aff_e_d_dec tan(aff_e_d_dec);

  template aff_e_d_dec asin(aff_e_d_dec);
  template aff_e_d_dec acos(aff_e_d_dec);
  template aff_e_d_dec atan(aff_e_d_dec);

  template aff_e_d_dec sinh(aff_e_d_dec);
  template aff_e_d_dec cosh(aff_e_d_dec);
  template aff_e_d_dec tanh(aff_e_d_dec);

  template aff_e_d_dec asinh(aff_e_d_dec);
  template aff_e_d_dec acosh(aff_e_d_dec);
  template aff_e_d_dec atanh(aff_e_d_dec);

  // template aff_e_d_dec abs(aff_e_d_dec);
  // template aff_e_d_dec rSqrt(aff_e_d_dec);
  // template aff_e_d_dec hypot(aff_e_d_dec);
  // template aff_e_d_dec compundm1(aff_e_d_dec);
  
  template details::double_iv_t to_iv(const aff_e_d_dec&);
  template double rad(const aff_e_d_dec&);
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

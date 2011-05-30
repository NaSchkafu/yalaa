#ifndef __AFFINEFORM_DOUBLE_HPP__
#define __AFFINEFORM_DOUBLE_HPP__
namespace yalaa
{
  template<template<typename> class ET,                                   \
           template<typename, template<typename> class> class AC, \
           template<typename, template<typename> class, template<typename, template<typename> class> class, class> class AR, \
           template<typename, template<typename> class, template<typename, template<typename> class> class> class AP, \
           typename EP, typename IV>
  IV to_iv(const AffineForm<double, ET, AC, AR, AP, EP, IV> & af);

  template<template<typename> class ET,				\
	   template<typename, template<typename> class> class AC,	\
	   template<typename, template<typename> class, template<typename, template<typename> class> class, class> class AR, \
	   template<typename, template<typename> class, template<typename, template<typename> class> class> class AP, \
	   typename EP, typename IV>
  double rad(const AffineForm<double, ET, AC, AR, AP, EP, IV> &af);
}

#include "affineform_double.inl"

#endif /*__AFFINEFORM_DOUBLE_HPP__*/

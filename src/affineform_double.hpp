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


#ifndef __AFFINEFORM_DOUBLE_HPP__
#define __AFFINEFORM_DOUBLE_HPP__
namespace yalaa
{
  template<template<typename> class ET,                                   \
           template<typename, template<typename> class> class AC, \
           template<typename, template<typename> class, template<typename, template<typename> class> class, class> class AR, \
           template<typename, template<typename> class, template<typename, template<typename> class> class> class AP, \
           template<typename, typename> class EP, typename IV>
  IV to_iv(const AffineForm<double, ET, AC, AR, AP, EP, IV> & af);

  template<template<typename> class ET,				\
	   template<typename, template<typename> class> class AC,	\
	   template<typename, template<typename> class, template<typename, template<typename> class> class, class> class AR, \
	   template<typename, template<typename> class, template<typename, template<typename> class> class> class AP, \
	   template<typename, typename> class EP, typename IV>
  double rad(const AffineForm<double, ET, AC, AR, AP, EP, IV> &af);
}

#include "affineform_double.inl"

#endif /*__AFFINEFORM_DOUBLE_HPP__*/

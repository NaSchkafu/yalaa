// -*-c++-*-
// Spezialisierung double
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


#include "helper/fphelper.hpp"

namespace yalaa
{
  namespace details
  {
    template<template<typename> class ET,                         \
             template<typename, template<typename> class> class AC,       \
             template<typename, template<typename> class, template<typename, template<typename> class> class, class> class AR, \
             template<typename, template<typename> class, template<typename, template<typename> class> class> class AP, \
             template<typename, typename> class EP, typename IV>
    double drad(const AffineForm<double, ET, AC, AR, AP, EP, IV> & af)
    {
      typedef AffineForm<double, ET, AC, AR, AP, EP, IV> aff_f_t;
      double r = 0.0;
      for(typename aff_f_t::ac_t::aff_comb_const_iter it(af.ac().begin()); it != af.ac().end(); ++it)
	r += fabs(it->dev());
      return r;
    }
}

  template<template<typename> class ET,                                   \
           template<typename, template<typename> class> class AC, \
           template<typename, template<typename> class, template<typename, template<typename> class> class, class> class AR, \
           template<typename, template<typename> class, template<typename, template<typename> class> class> class AP, \
           template<typename, typename> class EP, typename IV>
  double rad(const AffineForm<double, ET, AC, AR, AP, EP, IV> &af)
  {
    yalaa::fp::RndControl rnd;
    rnd.upward();
    double r = details::drad(af);
    return r;
  }

  template<template<typename> class ET,                                   \
           template<typename, template<typename> class> class AC, \
           template<typename, template<typename> class, template<typename, template<typename> class> class, class> class AR, \
           template<typename, template<typename> class, template<typename, template<typename> class> class> class AP, \
           template<typename, typename> class EP, typename IV>
  IV to_iv(const AffineForm<double, ET, AC, AR, AP, EP, IV> & af)
  {
    yalaa::fp::RndControl rnd;
    rnd.upward();
    double r = details::drad(af);
    double ub = af.ac().central() + r;
    rnd.downward();
    double lb = af.ac().central() - r;
    return typename AffineForm<double, ET, AC, AR, AP, EP, IV>::iv_t(lb, ub);
  }
}


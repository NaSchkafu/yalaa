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


#ifndef __YALAA_IOS_HPP__
#define __YALAA_IOS_HPP__

#include <iosfwd>
#include <type_traits>
#include "details/has_trait.hpp"

namespace yalaa
{
  namespace details
  {
    YALAA_DEFINE_HAS_TRAIT(trait_is_iv_t)
    YALAA_DEFINE_HAS_TRAIT(trait_is_err_t)

    template<typename ET>
    typename std::enable_if<has_trait_is_err_t<ET>::value,std::ostream&>::type
    operator<<(std::ostream &os, const ET& et)
    {
      et.print(os);
      return os;
    }
  }

  namespace iv
  {
    template<typename IV>
    typename std::enable_if<details::has_trait_is_iv_t<IV>::value,std::ostream&>::type
    operator<<(std::ostream &os, const IV& iv)
    {
      // TODO: Eigene Ausgabe mit korrekter Rundung implementieren
      iv.print(os);
      //os << "[" << inf(iv) << ", " << sup(iv) << "]";
      return os;
    }
  }

  template<typename AF>
  typename std::enable_if<details::has_trait_is_aff_t<AF>::value,std::ostream&>::type
  operator<<(std::ostream &os, const AF& af)
  {
    const typename AF::ac_t& ac = af.ac();
    os << ac.central();
    for(typename AF::ac_t::aff_comb_const_iter it(ac.begin()); it != ac.end(); ++it)
      os << " + " << *it;
    os << " <= " << to_iv(af);
    return os;
  }
}

#endif /*__YALAA_IOS_HPP__*/

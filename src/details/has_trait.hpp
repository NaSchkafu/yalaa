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

/**
 * @file   has_trait.hpp
 * @brief  C++11 detection idiom, used as a replacement for
 *         BOOST_MPL_HAS_XXX_TRAIT_DEF to check for a nested typedef marker.
 */

#ifndef __YALAA_DETAILS_HAS_TRAIT_HPP__
#define __YALAA_DETAILS_HAS_TRAIT_HPP__

#include <type_traits>

namespace yalaa
{
  namespace details
  {
    template<typename...>
    struct yalaa_void_impl { typedef void type; };

    template<typename... Ts>
    using yalaa_void_t = typename yalaa_void_impl<Ts...>::type;
  }
}

/// Defines a has_##name<T> trait that is std::true_type iff T has a nested
/// type/typedef called \c name, and std::false_type otherwise.
#define YALAA_DEFINE_HAS_TRAIT(name)                                       \
  template<typename T, typename = void>                                   \
  struct has_##name : std::false_type {};                                 \
  template<typename T>                                                    \
  struct has_##name<T, yalaa::details::yalaa_void_t<typename T::name> > : std::true_type {};

#endif /*__YALAA_DETAILS_HAS_TRAIT_HPP__*/

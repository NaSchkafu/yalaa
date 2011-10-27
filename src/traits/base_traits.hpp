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


#ifndef __BASE_TRAITS_HPP__
#define __BASE_TRAITS_HPP__

#include <math.h>

namespace yalaa 
{
  namespace details 
  {
    /// Traits template for adapting \c YalAA to new types
    /**
     * This template defines properties of arithmetic types used in
     * yalaa::AffineForm as base type. Before using a custom type
     * you have to specialize this template.
     */
    template<typename T>
    struct base_traits 
    { };
  }
}
#endif

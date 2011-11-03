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

#ifndef __INTERVAL_TRAITS_HPP__
#define __INTERVAL_TRAITS_HPP__

namespace yalaa 
{
  /// Namespace containing the traits classes for accessing external libraries
  namespace traits 
  {
    /// Traits used for accessing the interval type
    /**
     * Interval types are accessed through the method in this template.
     * For every interval type to be used in conjunction with \c YalAA
     * a specialization this template is required.
     * 
     */
    template <typename T>
    struct interval_traits 
    {
      
    };
  }
}

#endif /*__INTERVAL_TRAITS_HPP__*/

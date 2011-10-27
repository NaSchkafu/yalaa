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



#ifndef __AFFINECOMBIMPL_HPP__
#define __AFFINECOMBIMPL_HPP__

#include "affinecombbaseimpl.hpp"
#include "affinecombopimpl.hpp"

namespace yalaa 
{
  namespace details 
  {
    /// Default implementation of the AffineCombination concept.
    /**
     * This class implements the AffineCombination concept.
     * It stores affine combinations of ErrorTerm objects and provides the basic affine operations
     * on these. 
     */
    template<typename T, template<typename> class ET>
    struct AffineCombImpl : public AffineCombBaseImpl<T, ET>, 
      AffineCombOpImpl<T, ET, AffineCombBaseImpl>
    {
      typedef T base_t;
      typedef ET<T> error_t;
      typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;
      typedef AffineCombBaseImpl<T, ET> self_t;

      /** 
       * Ctor
       * Creates a new affine combination with the specified central value
       * 
       * @param central central value
       * 
       */
      explicit AffineCombImpl(typename AffineCombBaseImpl<T, ET>::base_ref_t central);

      /** 
       * Ctor
       * 
       * 
       */
      AffineCombImpl();      
    };
  }
}

#endif /*__AFFINECOMBIMPL_HPP__*/

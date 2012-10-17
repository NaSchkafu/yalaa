// -*-c++-*-
/*
  Copyright 2011-2012 Stefan Kiel <kiel@inf.uni-due.de>
  
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
 * @file   miscfp
 * @author Stefan Kiel <kiel@inf.uni-due.de>
 * @date   Wed Oct 17 14:18:27 2012
 * 
 * @brief  Implementation of absolute value function
 * 
 * 
 */

#ifndef __MISCFP_HPP__
#define __MISCFP_HPP__

namespace yalaa 
{
  namespace kernel
  {
    namespace details 
    {
      /// Additional functions
      template<typename T, template<typename> class ET,
	       template<typename, template<typename> class> class AC,
	       class AFFOP,
	       class IV>
      struct MiscFP
      {
	typedef T base_t;
	typedef ET<base_t> error_t;
	typedef AC<base_t, ET> ac_t;
	typedef yalaa::details::ArithmeticError<base_t> aerror_t;
	typedef AFFOP aff_op_t;
	typedef IV iv_t;
	typedef yalaa::traits::interval_traits<iv_t> iv_traits;
	typedef yalaa::traits::base_traits<base_t> b_traits;

	static aerror_t abs(ac_t *ac, const iv_t &d);
      };
    }
  }
}

#endif /*__MISC_HPP__*/

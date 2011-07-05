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
 * @file   special_forms.hpp
 * @author Stefan Kiel <kiel@inf.uni-due.de>
 * @date   Tue Jul  5 13:55:00 2011
 * 
 * @brief  Defines the special error terms (e.g. for AF1, AF2 extended forms)
 * 
 * 
 */


#ifndef __SPECIAL_FORMS_HPP__
#define __SPECIAL_FORMS_HPP__

namespace yalaa 
{
  namespace details
  {
    struct SpecialErrTerm
    {
      enum special_t { GEN_ERR = 1, POS_ERR = 2, NEG_ERR = 3 };
    };
  }
}

#endif /*__SPECIAL_FORMS_HPP__*/

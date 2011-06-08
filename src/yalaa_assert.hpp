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


#ifndef __AFFINEASSERT_HPP__
#define __AFFINEASSERT_HPP__

#include "assert.h"

#ifndef NDEBUG
#include <iostream>
#define YALAA_ASSERT(cond,msg)						\
  do {									\
  if(! (cond) ) {							\
      std::cerr << "YALAA_ASSERT '" #cond " failed at "		\
		<< __FILE__ << ":" << __LINE__ << std::endl		\
		<< msg << std::endl;					\
      std::exit(EXIT_FAILURE);						\
  }                                                                     \
  } while(false)
#else
#define YALAA_ASSERT(cond,msg) do {		\
      } while(false)
#endif

#endif /*__AFFINEASSERT_HPP__*/

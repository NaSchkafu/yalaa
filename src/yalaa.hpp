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


#ifndef __YALAA_HPP__
#define __YALAA_HPP__

// fwds
#include "yalaa_fwd.hpp"

// traits
#include "traits/float_traits.hpp"
#include "traits/double_traits.hpp"
#ifdef HAVE_LONG_DOUBLE_WIDER
#include "traits/l_double_traits.hpp"
#endif

// errterm
#include "errortermimpl.hpp"
// comb
#include "comb/affinecombimpl.hpp"
//kernel
#include "kernel/exacterror.hpp"
// aff pol
#include "pol/af0.hpp"
#include "pol/af1.hpp"
#include "pol/af2.hpp"
// err pol
#include "pol/errorpolstd.hpp"
#include "pol/errorpoldec.hpp"
// aff
#include "affineform.hpp"
#include "affineform_double.hpp"
#include "yalaa_ios.hpp"


#endif /*__YALAA_HPP__*/

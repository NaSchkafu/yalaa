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


#include <yalaa.hpp>

typedef yalaa::details::double_iv_t iv_t;
typedef yalaa::details::base_traits<iv_t> iv_traits;

int main(int argc, char *argv[])
{
  yalaa::aff_e_d x0_af0(iv_t(-1, 1));
  yalaa::aff_af1_e_d x0_af1(iv_t(-1, 1));
 
  // Operation performed with both AF0 and AF1
  // The number of noise symbols increases with AF0 in every step
  // This increased complexity does not deliver a better result in this test case
  std::cout << "AF0: " << sqrt(sqr(x0_af0)) + sqrt(x0_af0) - x0_af0 << std::endl;
  std::cout << "AF1: " << sqrt(sqr(x0_af1)) + sqrt(x0_af1) - x0_af1 << std::endl;

  // However, in this example AF0 results in a better enclosure.
  // As, in contrast to AF1, AF0 tracks even nonlinear dependencies just like 
  yalaa::aff_e_d tmp_x0_af0(sqrt(sqr(x0_af0)));
  yalaa::aff_af1_e_d tmp_x0_af1(sqrt(sqr(x0_af1)));
  std::cout << "AF0: " << 2*tmp_x0_af0 - tmp_x0_af0 << std::endl;
  std::cout << "AF1: " << 2*tmp_x0_af1 - tmp_x0_af1 << std::endl;

  return 0;
}

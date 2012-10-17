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

#include <yalaa.hpp>

typedef yalaa::details::double_iv_t iv_t;
typedef yalaa::traits::interval_traits<iv_t> iv_traits;

/* This example demonstrates the use of the absolute value function
 * and some additional simple arithmetic operations.
 */
int main(int argc, char *argv[])
{
  yalaa::aff_e_d x(iv_t(-1.0, 1.0));
  std::cout << "x: " << x << " abs(x): " << abs(x) << std::endl;

  yalaa::aff_e_d y(iv_t(1.0, 2.0));
  std::cout << "y: " << y << " abs(y): " << abs(y) << std::endl;

  yalaa::aff_e_d z(iv_t(-2.0, -1.0));
  std::cout << "z: " << z << " abs(z): " << abs(z) << std::endl;

  std::cout << "x - y: " << x - y  << std::endl;
  std::cout << "x - y + z: " << x - y + z << std::endl;
  std::cout << "x - y + z - z: " << x - y + z - z << std::endl;

  std::cout << "abs(x - y + z): " << abs(x - y + z) << std::endl;
  std::cout << "abs(x - y + z) + z: " << abs(x - y + z) + z << std::endl;

  return 0;
}

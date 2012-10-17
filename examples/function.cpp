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
typedef yalaa::traits::interval_traits<iv_t> iv_traits;

// Six-Hump-Camel Back Function:
// 1/3*x0^6 - 2.1*x0^4 + 4*x0^2 + x0*x1 + 4*x1^4 + 4*x1^2
// Coefficients like 1/3 or 2.1 are no floating-point numbers.
// However, we can enclose them in intervals and combine these intervals with
// the affine forms provided by YalAA.
template <typename T>
T eval_func(const T& x0, const T& x1)
{
  return iv_traits::my_div(iv_t(1.0), iv_t(3))*pown(x0,6) + 
    iv_traits::my_div(iv_t(21.0), iv_t(10))*pown(x0,4) + 4.0*sqr(x0) + 
    x0*x1 + 4.0*pown(x1,4) - 4.0*sqr(x1);
}

int main(int argc, char *argv[])
 {
   yalaa::aff_e_d x0(iv_t(-1.0, 1.0));
   yalaa::aff_e_d x1(iv_t(-1.0, 1.0));
   std::cout << "SHCB  over [-1,1]^2: "<< eval_func(x0, x1) << std::endl;

  // yalaa::aff_af1_e_d x3(iv_t(1.0,1.0));
  // std::cout << x3 << std::endl;
  // x3 -= iv_t(0.5, 1.0);
  // std::cout << x3 << std::endl;
  // x3 += iv_t(0.5, 1.0);
  // std::cout << x3 << std::endl;
  
  

  // yalaa::aff_e_d y0(iv_t( 0.000000,  1.446429));
  // yalaa::aff_e_d y1(iv_t( -1.468750,  1.062500));
  // std::cout << sqr(y0)-y1 << std::endl;
  return 0;
}

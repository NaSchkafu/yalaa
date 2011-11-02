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


// The decoration mechanism is explained in more detail in our paper
// describing the implementation details of YalAA.

#include <yalaa.hpp>

typedef yalaa::details::double_iv_t iv_t;
typedef yalaa::details::base_traits<iv_t> iv_traits;

int main(int argc, char *argv[])
{
  // A decorated affine form
  yalaa::aff_e_d_dec x0(iv_t(-1.0, 2.0));

  // A new affine form has the best decoration, as long as its original interval
  // is not empty or invalid.
  std::cout << "Decoration of x0: " << get_special(x0) << std::endl;

  // Square x0 is D5 (= 6), the best decoration
  std::cout << x0 << "^2 = " << sqr(x0) << " Deco: " << get_special(sqr(x0)) 
	    << " Valid: " << is_valid(sqr(x0)) << std::endl;

  // The natural domain of sqrt is R+. Thus the resulting decoration of sqrt(x0)
  // is D2 (=3) (possibly defined)
  std::cout <<  "sqrt(" << x0 << ") = " << sqrt(x0) << " Deco: " << get_special(sqrt(x0)) 
	    << " Valid: " << is_valid(sqrt(x0)) << std::endl;

  // The natural domain of log is R+, Thus the decoration is D2, as for lim x->0 log(x) is unbounded
  // the computation overflows for the natural domain resulting in Infinity as central value
  // Note the changed value of valid. Even if the decoration quality is the some as for sqrt(x0),
  // is_valid returns now false, as the form has no numerical meaningful value anymore.
  std::cout << "log(" << x0 << ") = " << log(x0) << " Deco: " << get_special(log(x0))
	    << " Valid: " << is_valid(log(x0)) << std::endl;

  // A form for an empty interval is created. The decoration is D0 (=1).
  yalaa::aff_e_d_dec empty(iv_t(1, -1));
  std::cout << "Decoration of an empty affine form: " << get_special(empty) 
	    << " Valid: " << is_valid(empty) << std::endl;
  // If the empty is used as input argument of an operation, the result is again D0
  std::cout <<  "cos(" << empty << ") = " << cos(empty) << " Deco: " << get_special(cos(empty)) 
	    << " Valid: " << is_valid(cos(empty)) << std::endl;

  // Combination of an affine form with a scalar
  // Normally scalars are treated like affine forms with a D5 decoration. However, if they have a
  // special value like NaN or infinity, the combination results in D-1 (=0) with indicates some
  // error.
  std::cout <<  "3.0*" << x0 << ") = " << 3*x0 << " Deco: " << get_special(3*x0) 
	    << " Valid: " << is_valid(3*x0) << std::endl;
  std::cout <<  "infinity*" << x0 << ") = " << std::numeric_limits<double>::infinity()*x0 
	    << " Deco: " << get_special(std::numeric_limits<double>::infinity()*x0) 
	    << " Valid: " << is_valid(std::numeric_limits<double>::infinity()*x0) << std::endl;

  // Decoations are propagated through inductively defined functions
  // Thus f = sqrt(x0) + x0 
  // has the decoration D2, as sqrt(x0) is D2.
  yalaa::aff_e_d_dec sqrtx0(sqrt(x0));
  std::cout <<  "sqrt(" << x0 << ") + " << x0 << " = " << sqrt(x0) + x0 
	    << " Deco: " << get_special(sqrt(x0) + x0) 
	    << " Valid: " << is_valid(sqrt(x0) + x0) << std::endl;
  
  // The natural domain of exp is not violated, but the computation overflows resulting in D4 
  // (defined and continuous). No statement is made about the boundness!
  // Commented out, as some libraries like C-XSC abort the program in case of an overflow.
  // yalaa::aff_e_d_dec x1(1000.0);
  // std::cout << "exp(" << x1 << ") = " << exp(x1) << " Deco: " << get_special(exp(x1)) << std::endl;
  return 0;
}

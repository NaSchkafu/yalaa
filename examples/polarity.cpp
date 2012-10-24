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

#include <map>
#include <yalaa.hpp>


typedef yalaa::details::double_iv_t iv_t;
typedef yalaa::traits::interval_traits<iv_t> iv_traits;

template <typename AF>
std::map<typename AF::error_t, int> polarity(const AF& af)
{
  std::map<typename AF::error_t, int> errors;
  typename AF::ac_t ac(af.ac());
  for(auto it(ac.begin()); it != ac.end(); ++it) {
    errors[*it] = it->dev() > 0 ? 1 : -1;
  }
  return errors;
}

template <typename POL>
typename POL::key_type::base_t eval(const POL &pol) 
{
  typename POL::key_type::base_t result = 0.0;  
  for(auto it(pol.begin()); it != pol.end(); ++it) {
    result += it->first.dev() * it->second;
  }
  return result;
}

int main(int argc, char *argv[])
{
  yalaa::aff_e_d x(iv_t(0.5, 1.0));
  std::cout << "x: " << x << std::endl;
  yalaa::aff_e_d y(iv_t(-0.5, 0.0));
  std::cout << "y: " << y << std::endl;
  x -= y;
  std::cout << "x-y: " << x << std::endl;

  auto pol_map(polarity(x));
  std::cout << "Eval: " << eval(pol_map) << std::endl;


  return 0;
}

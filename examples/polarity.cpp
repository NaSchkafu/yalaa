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
typename AF::base_t polarity(const AF& af, std::map<typename AF::error_t, int> &pol)
{
  typename AF::base_t res = 0.0; 
  typename AF::ac_t ac(af.ac());
  for(auto it(ac.begin()); it != ac.end(); ++it) {
    pol[*it] = it->dev() > 0 ? 1 : -1;
    res += fabs(it->dev());
  }
  res += ac.central();
  return res;
}

template <typename AF>
typename AF::base_t eval(const AF &af, const std::map<typename AF::error_t, int> &pol)
{
  typename AF::base_t result = 0.0;
  typename AF::ac_t ac(af.ac());
  for(auto it(ac.begin()); it != ac.end(); ++it) {
    auto pit(pol.find(*it));
    if(pit != pol.end())
      result += it->dev() * pit->second;
    else
      std::cerr << "Noise symbol is not in the polarity map!" << std::endl;
  }
  return result;
}

int main(int argc, char *argv[])
{
  typedef yalaa::aff_e_d aaf;

  aaf x(iv_t(0.5, 1.0));
  std::cout << "x: " << x << std::endl;
  aaf y(iv_t(-0.5, 0.0));
  std::cout << "y: " << y << std::endl;
  x -= y;
  std::cout << "x-y: " << x << std::endl;

  std::map<aaf::error_t, int> pol;
  std::cout << "polarity(x-y): " << polarity(x, pol) << std::endl;
  std::cout << "eval(x-y): " << eval(x, pol) << std::endl;

  return 0;
}

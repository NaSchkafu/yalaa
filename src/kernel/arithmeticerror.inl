// -*-c++-*-
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


// template<typename T>
// ArithmeticError<T>::ArithmeticError(base_ref_t rnd, base_ref_t approx, base_ref_t sum, bool valid)
//   :m_rnd(rnd), m_approx(approx), m_sum(sum), m_valid(valid)
// { }

template<typename T>
ArithmeticError<T>::ArithmeticError(base_ref_t gen, unsigned error)
  :m_gen(gen), m_pos(0), m_neg(0),  m_error(error)
{ }

template<typename T>
ArithmeticError<T>::ArithmeticError(base_ref_t gen, base_ref_t pos, base_ref_t neg, 
		unsigned error)
  :m_gen(gen), m_pos(pos), m_neg(neg), m_error(error)
{}

// template<typename T>
// typename ArithmeticError<T>::base_t ArithmeticError<T>::sum() const
// {
//   return m_sum;
// }

template<typename T>
typename ArithmeticError<T>::base_t ArithmeticError<T>::neg() const
{
  return m_neg;
}

template<typename T>
typename ArithmeticError<T>::base_t ArithmeticError<T>::pos() const
{
  return m_pos;
}

template<typename T>
typename ArithmeticError<T>::base_t ArithmeticError<T>::gen() const
{
  return m_gen;
}

template<typename T>
unsigned ArithmeticError<T>::error() const
{
  return m_error;
}

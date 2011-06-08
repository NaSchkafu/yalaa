//-*-c++-*-
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


namespace yalaa
{
  namespace details
  {
    
template<typename T, template<typename> class ET>
typename AffineCombImpl<T,ET>::aff_comb_const_iter AffineCombImpl<T,ET>::begin() const
{
  return m_errors.begin();
}

template<typename T, template<typename> class ET>
typename AffineCombImpl<T,ET>::aff_comb_const_iter AffineCombImpl<T,ET>::end() const
{
  return m_errors.end();
}

template<typename T, template<typename> class ET>
typename AffineCombImpl<T,ET>::aff_comb_iter AffineCombImpl<T,ET>::begin()
{
  return m_errors.begin();
}

template<typename T, template<typename> class ET>
typename AffineCombImpl<T,ET>::aff_comb_iter AffineCombImpl<T,ET>::end()
{
  return m_errors.end();
}

template<typename T, template<typename> class ET>
void AffineCombImpl<T,ET>::remove(const ET<T> &term)
{
  aff_comb_iter it(std::lower_bound(m_errors.begin(), m_errors.end(), term));
  if(*it == term && it != m_errors.end())
    m_errors.erase(it);
}

template<typename T, template<typename> class ET>
void AffineCombImpl<T,ET>::remove(const aff_comb_iter &it)
{
  m_errors.erase(it);
}

// template<typename T, template<typename> class ET>
// void AffineCombImpl<T,ET>::remove(const aff_comb_const_iter &it)
// {
//   m_errors.erase(it);
// }

template<typename T, template<typename> class ET>
typename AffineCombImpl<T,ET>::aff_comb_iter AffineCombImpl<T,ET>::insert(const ET<T> &term)
{
  aff_comb_iter it(std::lower_bound(m_errors.begin(), m_errors.end(), term));
  YALAA_ASSERT(it == m_errors.end() || !(*it == term), "Term is already in affine combination.");
  return m_errors.insert(it == m_errors.end() ? m_errors.begin()+m_errors.size() : it, term);
}

template<typename T, template<typename> class ET>
typename AffineCombImpl<T,ET>::aff_comb_iter AffineCombImpl<T,ET>::insert(const ET<T> &term, 
									  const aff_comb_iter &pos)
{
  return m_errors.insert(pos, term);
  // aff_comb_iter it(std::lower_bound(m_errors.begin(), m_errors.end(), term));
  // YALAA_ASSERT(it == m_errors.end() || !(*it == term), "Term is already in affine combination.");
  // return m_errors.insert(it == m_errors.end() ? m_errors.begin()+m_errors.size() : it, term);
}

template<typename T, template<typename> class ET>
typename AffineCombImpl<T,ET>::size_t AffineCombImpl<T,ET>::size() const
{
  return m_errors.size();
}

template<typename T, template<typename> class ET>
AffineCombImpl<T,ET>::AffineCombImpl(base_ref_t central)
  :m_central(central)
{}

template<typename T, template<typename> class ET>
AffineCombImpl<T,ET>::AffineCombImpl()
{}

template<typename T, template<typename> class ET>
typename AffineCombImpl<T,ET>::base_t AffineCombImpl<T,ET>::central() const 
{
  return m_central;
}

template<typename T, template<typename> class ET>
void AffineCombImpl<T,ET>::set_central(base_ref_t central)
{
  m_central = central;
}

template<typename T, template<typename> class ET>
void AffineCombImpl<T, ET>::clear()
{
  m_errors.clear();
  m_central = yalaa::details::base_traits<T>::my_zero();
}

template<typename T, template<typename> class ET>
void AffineCombImpl<T, ET>::push_back(const ET<T> &term)
{
  m_errors.push_back(term);
}
  }
}

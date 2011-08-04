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


template<typename T, typename IV>
bool ErrorPolDec<T,IV>::special(special_t val)
{
  return val;
}


template<typename T, typename IV>
typename ErrorPolDec<T,IV>::special_t ErrorPolDec<T,IV>::to_deco(const aerror_t &error)
{
  typedef yalaa::details::ArithmeticError<T> aerror_t;
  unsigned err = error.error();
  if(aerror_t::I_ERROR & err)
    return DE;  
  else if(aerror_t::C_D_VIOL & err)
    return D1;
  else if(aerror_t::P_D_VIOL & err)
    return D2;
  else if(aerror_t::DISCONT & err)
    return D3;
  else if((aerror_t::OFLOW | aerror_t::UNBOUND) & err)
    return D4;
  return D5;
}

template<typename T, typename IV>
typename ErrorPolDec<T,IV>::special_t ErrorPolDec<T,IV>::iv_deco(const iv_t& iv) 
{
  if(yalaa::details::base_traits<iv_t>::is_special(iv))
    return DE;
  else if(yalaa::details::base_traits<iv_t>::is_empty(iv))
    return D0;
  return D5;
}

template<typename T, typename IV>
typename ErrorPolDec<T, IV>::special_t ErrorPolDec<T, IV>::scal_deco(const base_t& s)
{
  if(yalaa::details::base_traits<base_t>::is_special(s))
    return DE;
  return D5;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolDec<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T *af1, const YALAA_SPEC_TEMPLATE_T &af2)
{
  af1->m_special = std::min(af1->m_special, af2.m_special);
  if(af1->m_special == D1)
    af1->m_special = D0;
  return af1->m_special > 2;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolDec<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T *af, const iv_t &iv)
{
  af->m_special = std::min(af->m_special, iv_deco(iv));
  if(af->m_special == D1)
    af->m_special= D0;
  return af->m_special > 2;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolDec<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T *af, base_ref_t s)
{
  af->m_special = std::min(af->m_special, scal_deco(s));
  if(af->m_special == D1)
    af->m_special = D0;
  return af->m_special > 2;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolDec<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T *af)
{
  if(af->m_special == D1)
    af->m_special = D0;
  return af->m_special > 2;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolDec<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T *af1, const aerror_t &err)
{
  af1->m_special = std::min(af1->m_special, to_deco(err));
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolDec<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T *af1, const YALAA_SPEC_TEMPLATE_T &,
                                 const aerror_t &err)
{
  post_op(af1, err);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolDec<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T *af, const iv_t &,
                                 const aerror_t &err)
{
  post_op(af, err);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolDec<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T *af, base_ref_t , const aerror_t &err)
{
  post_op(af, err);
}


template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolDec<T, IV>::new_form(YALAA_SPEC_TEMPLATE_T *af, base_ref_t s)
{
  af->m_special = scal_deco(s);
  return af->m_special > 2;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolDec<T, IV>::new_form(YALAA_SPEC_TEMPLATE_T *af, const iv_t& iv)
{
  af->m_special = iv_deco(iv);
  return af->m_special > 2;
}

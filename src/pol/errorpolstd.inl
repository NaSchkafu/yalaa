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

namespace details 
{
  template <typename T>
  inline void adjust_central_R(T &central)
  {
    central = yalaa::details::base_traits<T>::special();
  }
    
  template <typename T>
  inline void adjust_central_EMPTY(T &central)
  {
    central = yalaa::details::base_traits<T>::special();
  }

  inline void adjust_central_R(double &central)
  {
    if(-central != std::numeric_limits<double>::infinity())
      central = std::numeric_limits<double>::infinity();
  }

  inline void adjust_central_EMPTY(double &central)
  {
    central = std::numeric_limits<double>::quiet_NaN();
  }

  
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::adjust_central(YALAA_SPEC_TEMPLATE_T *af)
{
  T central(af->ac().central());
  switch(af->m_special)
  {
  case R:
    details::adjust_central_R(central);
    break;
  case EMPTY:
    details::adjust_central_EMPTY(central);
    break;
  default:
    break;
  }
  af->ac().set_central(central);
  return !af->m_special;
}

template<typename T, typename IV>
typename ErrorPolStd<T, IV>::special_t base_special(const T& s) 
{
  return yalaa::details::base_traits<T>::is_special(s) ? ErrorPolStd<T, IV>::EMPTY : 
    ErrorPolStd<T, IV>::NONE;
}

template<typename T, typename IV>
typename ErrorPolStd<T, IV>::special_t iv_special(const IV& s) 
{
  return yalaa::details::base_traits<IV>::is_special(s) ? ErrorPolStd<T, IV>::EMPTY : 
    ErrorPolStd<T, IV>::NONE;
}

template<typename IV>
typename ErrorPolStd<double, IV>::special_t base_special(double s) 
{
  if(yalaa::details::base_traits<double>::is_nan(s))
    return ErrorPolStd<double, IV>::EMPTY;
  else if(yalaa::details::base_traits<double>::is_infinity(s))
    return ErrorPolStd<double, IV>::R;
  return ErrorPolStd<double, IV>::NONE;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T,IV>::valid(const YALAA_SPEC_TEMPLATE_T& af)
{
  return !af.m_special;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T *af1, const YALAA_SPEC_TEMPLATE_T &af2)
{
  af1->m_special = std::max(af1->m_special, af2.m_special);
  return adjust_central(af1);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T *af, const iv_t &iv)
{
  af->m_special = std::max(af->m_special, iv_special<T, IV>(iv));
  return adjust_central(af);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T *af, base_ref_t s)
{
  af->m_special = std::max(af->m_special, base_special<T, IV>(s));
  return adjust_central(af);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T *af)
{
  return !af->m_special;
}

template<typename T, typename IV>
typename ErrorPolStd<T, IV>::special_t ErrorPolStd<T, IV>::to_special(const aerror_t &err)
{
  unsigned e = err.error();
  if(e & aerror_t::C_D_VIOL)
    return EMPTY;
  else if(e & aerror_t::UNBOUND || e & aerror_t::OFLOW)
    return R;
  return NONE;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolStd<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T *af1, const YALAA_SPEC_TEMPLATE_T &,
                                 const aerror_t &err)
{
  af1->m_special = to_special(err);
  adjust_central(af1);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolStd<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T *af, const iv_t &,
                                 const aerror_t &err)
{
  af->m_special = to_special(err);
  adjust_central(af);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolStd<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T *af, base_ref_t , const aerror_t &err)
{
  af->m_special = to_special(err);
  adjust_central(af);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolStd<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T *af, const aerror_t &err)
{
  af->m_special = to_special(err);
  adjust_central(af);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::new_form(YALAA_SPEC_TEMPLATE_T *af, base_ref_t s)
{
  af->m_special = base_special<T, IV>(s);
  return adjust_central(af);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::new_form(YALAA_SPEC_TEMPLATE_T *af, const iv_t& iv)
{
  af->m_special = iv_special<T, IV>(iv);
  return adjust_central(af);
}


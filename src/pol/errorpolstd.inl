// -*-c++-*-
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
bool ErrorPolStd<T,IV>::special(special_t val)
{
  return val;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T *af1, const YALAA_SPEC_TEMPLATE_T &af2)
{
  return af1->m_special = std::max(af1->m_special, af2.m_special);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T *af, const iv_t &iv)
{
  return af->m_special = std::max(af->m_special, iv_special<T, IV>(iv));
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T *af, base_ref_t s)
{
  return af->m_special = std::max(af->m_special, base_special<T, IV>(s));
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T *af)
{
  return af->m_special;
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
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolStd<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T *af, const iv_t &,
                                 const aerror_t &err)
{
  af->m_special = to_special(err);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolStd<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T *af, base_ref_t , const aerror_t &err)
{
  af->m_special = to_special(err);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolStd<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T *af, const aerror_t &err)
{
  af->m_special = to_special(err);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::new_form(YALAA_SPEC_TEMPLATE_T *af, base_ref_t s)
{
  return af->m_special = base_special<T, IV>(s);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::new_form(YALAA_SPEC_TEMPLATE_T *af, const iv_t& iv)
{
  return af->m_special = iv_special<T, IV>(iv);
}


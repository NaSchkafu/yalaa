// -*-c++-*-
template<typename T, typename IV>
bool ErrorPolStd<T,IV>::special(special_t val)
{
  return val;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T &af1, const YALAA_SPEC_TEMPLATE_T &af2)
{
  af1.m_special = std::max(af1.m_special, af2.m_special);
  return !af1.m_special;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T &af, const iv_t &)
{
  return !af.m_special;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T &af, base_ref_t )
{
  return !af.m_special;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolStd<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T &af)
{
  return !af.m_special;
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
void ErrorPolStd<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T &af1, const YALAA_SPEC_TEMPLATE_T &,
                                 const aerror_t &err)
{
  af1.m_special = to_special(err);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolStd<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T &af, const iv_t &,
                                 const aerror_t &err)
{
  af.m_special = to_special(err);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolStd<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T &af, base_ref_t , const aerror_t &err)
{
  af.m_special = to_special(err);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolStd<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T &af, const aerror_t &err)
{
  af.m_special = to_special(err);
}


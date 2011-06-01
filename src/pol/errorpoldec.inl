// -*-c++-*-
template<typename T, typename IV>
bool ErrorPolDec<T,IV>::special(special_t val)
{
  return val;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
typename ErrorPolDec<T,IV>::special_t ErrorPolDec<T,IV>::empty_undef(const YALAA_SPEC_TEMPLATE_T &af)
{
  return (af.m_special & 0x101) | (af.m_special & 0x100);
}


template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolDec<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T *af1, const YALAA_SPEC_TEMPLATE_T &af2)
{
  unsigned short flags = empty_undef(*af1) | empty_undef(af2) | (af1->m_special & 0x0001) | 
    (af1->m_special & 0x00001) | (af2.m_special & 0x0001) | (af2.m_special & 0x00001);
  if(flags)
    af1->m_special = flags;
  else
    af1->m_special = std::min(af1->m_special & 0x111, af2.m_special & 0x111);
  return flags;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolDec<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T *af, const iv_t &)
{
  // TODO: Dekorierte Intervalle unterstützen
  special_t flags = empty_undef(*af);
  if(flags)
    af->m_special = flags;
  return flags;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolDec<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T *af, base_ref_t )
{
  // TODO: Dekorierte base_ref_t's unterstützen
  special_t flags = empty_undef(*af);
  if(flags)
    af->m_special = flags;
  return flags;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolDec<T, IV>::pre_op(YALAA_SPEC_TEMPLATE_T *af)
{
  special_t flags = empty_undef(*af);
  if(flags)
    af->m_special = flags;
  return flags;
}

template<typename T, typename IV>
typename ErrorPolDec<T, IV>::special_t ErrorPolDec<T, IV>::to_deco(const aerror_t &err)
{
  unsigned e = err.error();
  if(e & aerror_t::C_D_VIOL)
    return 0;
  else if(e & aerror_t::P_D_VIOL)
    return 1;
  else if(e & aerror_t::UNBOUND)
    return 2;
  else if(e & aerror_t::DISCONT)
    return 3;
  return 4;
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolDec<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T *af1, const aerror_t &err)
{
  special_t ierr = err.error() & aerror_t::I_ERROR ? 1 : 0;
  special_t oflow = (err.error() & aerror_t::OFLOW) | ierr ? 1 : 0;
  special_t deco = 0;
  if(!ierr)
    deco = std::min(to_deco(err), af1->m_special);
  af1->m_special = (deco & 0x111) | (oflow >> 4) | (ierr >> 5);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolDec<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T *af1, const YALAA_SPEC_TEMPLATE_T &af2,
                                 const aerror_t &err)
{
  post_op(af1, err);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolDec<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T *af, const iv_t &iv,
                                 const aerror_t &err)
{
  post_op(af, err);
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
void ErrorPolDec<T, IV>::post_op(YALAA_SPEC_TEMPLATE_T *af, base_ref_t s, const aerror_t &err)
{
  post_op(af, err);
}


template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolDec<T, IV>::new_form(YALAA_SPEC_TEMPLATE_T *af, base_ref_t s)
{
  
}

template<typename T, typename IV>
YALAA_SPEC_TEMPLATE_DEF
bool ErrorPolDec<T, IV>::new_form(YALAA_SPEC_TEMPLATE_T *af, const iv_t& iv)
{
  
}

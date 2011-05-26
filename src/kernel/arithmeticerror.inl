// -*-c++-*-
// template<typename T>
// ArithmeticError<T>::ArithmeticError(base_ref_t rnd, base_ref_t approx, base_ref_t sum, bool valid)
//   :m_rnd(rnd), m_approx(approx), m_sum(sum), m_valid(valid)
// { }

template<typename T>
ArithmeticError<T>::ArithmeticError(base_ref_t gen, bool valid)
  :m_gen(gen), m_pos(0), m_neg(0), m_sum(gen), m_valid(valid)
{ }

template<typename T>
typename ArithmeticError<T>::base_ref_t ArithmeticError<T>::sum() const
{
  return m_sum;
}

template<typename T>
typename ArithmeticError<T>::base_ref_t ArithmeticError<T>::get(ERROR_TYPE type) const
{
  switch(type) {
  case GEN_ERR:
    return m_gen;
  case POS_ERR:
    return m_pos;
  case NEG_ERR:
    return m_neg;
  }
  YALAA_ASSERT(false, "Unknown error type requested!");
}


// -*-c++-*-
// template<typename T>
// ArithmeticError<T>::ArithmeticError(base_ref_t rnd, base_ref_t approx, base_ref_t sum, bool valid)
//   :m_rnd(rnd), m_approx(approx), m_sum(sum), m_valid(valid)
// { }

template<typename T>
ArithmeticError<T>::ArithmeticError(base_ref_t gen, unsigned error)
  :m_gen(gen), m_pos(0), m_neg(0), m_sum(gen), m_error(error)
{ }

template<typename T>
ArithmeticError<T>::ArithmeticError(base_ref_t gen, base_ref_t pos, base_ref_t neg, 
		base_ref_t sum, unsigned error)
  :m_gen(gen), m_pos(pos), m_neg(neg), m_sum(sum), m_error(error)
{}

template<typename T>
ArithmeticError<T>::ArithmeticError(base_ref_t gen, base_ref_t pos, base_ref_t neg, unsigned error)
  :m_gen(gen), m_pos(pos), m_neg(neg), m_error(error)
{
  m_sum = base_traits<base_t>::add_up(pos, neg);
  m_sum = base_traits<base_t>::add_up(gen, m_sum);
}

template<typename T>
typename ArithmeticError<T>::base_t ArithmeticError<T>::sum() const
{
  return m_sum;
}

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



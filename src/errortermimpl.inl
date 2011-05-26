// -*-c++-*-

template <typename T>
bool ErrorTermImpl<T>::operator==(const self_t &other) const 
{
  return m_eps == other.m_eps;
}

template <typename T>
bool ErrorTermImpl<T>::operator<(const self_t &other) const
{
  return m_eps < other.m_eps;
}

template <typename T>
typename ErrorTermImpl<T>::base_ref_t ErrorTermImpl<T>::dev() const 
{
  return m_dev;
}

template <typename T>
void ErrorTermImpl<T>::set_dev(base_ref_t new_dev)
{
  m_dev = new_dev;
}

template <typename T>
ErrorTermImpl<T>::ErrorTermImpl()
  :m_eps(new_symbol()), m_dev(0)
{ }

template <typename T>
ErrorTermImpl<T>::ErrorTermImpl(const self_t &other)
  :m_eps(other.m_eps), m_dev(other.m_dev)
{ }

template <typename T>
ErrorTermImpl<T>::ErrorTermImpl(base_ref_t dev)
  :m_eps(new_symbol()), m_dev(dev)
{ }

template<typename T>
unsigned long long ErrorTermImpl<T>::new_symbol()
{
#if defined(__GNUC__) && !defined(__clang__)
  return __sync_add_and_fetch(&CURRENT_EPS,1);
#else
  // TODO: weitere atomare Operationen hinzufügen!
  CURRENT_EPS++;
  return CURRENT_EPS;
#endif
}

template<typename T>
void ErrorTermImpl<T>::print(std::ostream &os) const
{
  os << "eps" << m_eps << "*" << m_dev;
}

template<typename T>
unsigned long long ErrorTermImpl<T>::CURRENT_EPS = 0;

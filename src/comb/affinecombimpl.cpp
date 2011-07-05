// dummy
#include "affinecombbaseimpl.cpp"
#include "affinecombopimpl.cpp"
namespace yalaa 
{
  namespace details 
  {
    template<typename T, template<typename> class ET>
    AffineCombImpl<T, ET>::AffineCombImpl(typename AffineCombBaseImpl<T,ET>::base_ref_t central)
      :AffineCombBaseImpl<T, ET>(central)
    { }

    template<typename T, template<typename> class ET>
    AffineCombImpl<T,ET>::AffineCombImpl()
    {
    }
  }
}

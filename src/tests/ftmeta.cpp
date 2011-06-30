#include "ftmeta.hpp"

#include <limits>

namespace yalaa 
{
  namespace tests 
  {
    FTMeta::FTMeta(const std::string &a_name, const iv_t &a_d, const d_t a_dt, 
		   aff_f_t a_afff, iv_f_t a_ivf, base_t a_l_lim, base_t a_r_lim )
      :name(a_name), d(a_d), dt(a_dt), afff(a_afff), ivf(a_ivf), l_lim(a_l_lim), r_lim(a_r_lim)
    {
    }

    FTMeta::map_t FTMeta::get()
    {
      FTMeta m("Sine", iv_t(-100, 100),
      	       CLOSED, &yalaa::sin, &iv_traits::my_sin);
      map_t metas;
      metas.insert(m);
      
      return metas;
    }
  }
}

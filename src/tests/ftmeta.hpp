#ifndef __FTMETA_HPP__
#define __FTMETA_HPP__

#include <set>
#include <string>

#include "traits/base_traits.hpp"
#include "yalaa.hpp"

namespace yalaa 
{
  namespace tests 
  {
    enum d_t { OPEN = 3, RIGHTOPEN = 2, CLOSED = 0, LEFTOPEN = 1 };

    struct FTMeta 
    {
      typedef double base_t;
      typedef yalaa::details::double_iv_t iv_t;
      typedef iv_t (*iv_f_t)(const iv_t&);
      typedef yalaa::aff_e_d (*aff_f_t)(yalaa::aff_e_d);
      typedef yalaa::details::base_traits<iv_t> iv_traits;
      typedef std::set<FTMeta> map_t;


      std::string name;
      iv_t d;
      d_t dt;
      aff_f_t afff;
      iv_f_t ivf;
      base_t l_lim;
      base_t r_lim;

      FTMeta(const std::string &a_name, const iv_t &a_d, const d_t a_dt, 
	     aff_f_t a_afff, iv_f_t ivf, base_t a_l_lim = 0.0, base_t a_r_lim = 0.0);

      FTMeta()
	{
	}

      static map_t get();
    };

    inline bool operator<(const FTMeta &f1, const FTMeta &f2)
    {
      return f1.name < f2.name;
    }

    inline std::ostream& operator<<(std::ostream &os, const FTMeta &meta)
    {
      os << "FTMeta for " << meta.name << " Natural Domain: " << meta.d << " of type " << meta.dt;
      os << " limit l: " << meta.l_lim << " limit r: " << meta.r_lim << std::endl;
    }

  }
}

#endif /*__FTMETA_HPP__*/

#include "ftmeta.hpp"

#include <limits>

// Legt die Domainbereiche für die Tests fest
#define MIN_INFINITY -100
#define MAX_INFINITY 100


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
      struct FTMeta sqr = {
	"sqr", iv_t(MIN_INFINITY, MAX_INFINITY),
	CLOSED, &yalaa::sqr, &iv_traits::my_sqr
      };

      struct FTMeta sqrt = {
	"sqrt", iv_t(0, MAX_INFINITY),
	CLOSED, &yalaa::sqrt, &iv_traits::my_sqrt
      };

      struct FTMeta exp = {
	"exp", iv_t(MIN_INFINITY, MAX_INFINITY),
	CLOSED, &yalaa::exp, &iv_traits::my_exp
      };

      struct FTMeta exp2 = {
	"exp2", iv_t(MIN_INFINITY, MAX_INFINITY),
	CLOSED, &yalaa::exp2, &iv_traits::my_exp2
      };

      struct FTMeta exp10 = {
	"exp10", iv_t(MIN_INFINITY, MAX_INFINITY),
	CLOSED, &yalaa::exp10, &iv_traits::my_exp10
      };

      struct FTMeta expm1 = {
	"expm1", iv_t(MIN_INFINITY, MAX_INFINITY),
	CLOSED, &yalaa::expm1, &iv_traits::my_expm1
      };

      struct FTMeta exp2m1 = {
	"exp2m1", iv_t(MIN_INFINITY, MAX_INFINITY),
	CLOSED, &yalaa::exp2m1, &iv_traits::my_exp2m1
      };

      struct FTMeta exp10m1 = {
	"exp10m1", iv_t(MIN_INFINITY, MAX_INFINITY),
	CLOSED, &yalaa::exp10m1, &iv_traits::my_exp10m1
      };

      struct FTMeta log = {
	"log", iv_t(0, MAX_INFINITY),
	OPEN, &yalaa::log, &iv_traits::my_log
      };

      struct FTMeta log2 = {
	"log2", iv_t(0, MAX_INFINITY),
	OPEN, &yalaa::log2, &iv_traits::my_log2
      };

      struct FTMeta log10 = {
	"log10", iv_t(0, MAX_INFINITY),
	OPEN, &yalaa::log10, &iv_traits::my_log10
      };

      struct FTMeta logp1 = {
	"logp1", iv_t(-1, MAX_INFINITY),
	OPEN, &yalaa::logp1, &iv_traits::my_logp1
      };

      struct FTMeta log2p1 = {
	"log2p1", iv_t(-1, MAX_INFINITY),
	OPEN, &yalaa::log2p1, &iv_traits::my_log2p1
      };

      struct FTMeta log10p1 = {
	"log10p1", iv_t(-1, MAX_INFINITY),
	OPEN, &yalaa::log10p1, &iv_traits::my_log10p1
      };

      struct FTMeta sin = {
	"sin", iv_t(MIN_INFINITY, MAX_INFINITY),
	CLOSED, &yalaa::sin, &iv_traits::my_sin
      };

      struct FTMeta cos = {
	"cos", iv_t(MIN_INFINITY, MAX_INFINITY),
	CLOSED, &yalaa::cos, &iv_traits::my_cos
      };

      // Testet nur einen tan Branch derzeit
      struct FTMeta tan = {
	"tan", iv_t(-0.49*iv_traits::my_sup(iv_traits::my_pi()), 0.49*iv_traits::my_inf(iv_traits::my_pi())),
	OPEN, &yalaa::tan, &iv_traits::my_tan
      };
      
      struct FTMeta asin = {
	"asin", iv_t(-1, 1),
	CLOSED, &yalaa::asin, &iv_traits::my_asin
      };

      struct FTMeta acos = {
	"acos", iv_t(-1, 1),
	CLOSED, &yalaa::acos, &iv_traits::my_acos
      };

      struct FTMeta atan = {
	"atan", iv_t(MIN_INFINITY, MAX_INFINITY),
	CLOSED, &yalaa::atan, &iv_traits::my_atan
      };

      struct FTMeta sinh = {
	"sinh", iv_t(MIN_INFINITY, MAX_INFINITY),
	CLOSED, &yalaa::sinh, &iv_traits::my_sinh
      };

      struct FTMeta cosh = {
	"cosh", iv_t(MIN_INFINITY, MAX_INFINITY),
	CLOSED, &yalaa::cosh, &iv_traits::my_cosh
      };

      struct FTMeta tanh = {
	"atanh", iv_t(MIN_INFINITY, MAX_INFINITY),
	OPEN, &yalaa::tanh, &iv_traits::my_tanh
      };

      struct FTMeta asinh = {
	"asinh", iv_t(MIN_INFINITY, MAX_INFINITY),
	CLOSED, &yalaa::asinh, &iv_traits::my_asinh
      };

      struct FTMeta acosh = {
	"acosh", iv_t(1, MAX_INFINITY),
	CLOSED, &yalaa::acosh, &iv_traits::my_acosh
      };

      struct FTMeta atanh = {
	"atanh", iv_t(-1, 1),
	OPEN, &yalaa::atanh, &iv_traits::my_atanh
      };
      
      
      map_t metas;
      metas.insert(sqr);
      metas.insert(sqrt);
      metas.insert(exp);
      metas.insert(exp2);
      metas.insert(exp10);
      metas.insert(expm1);
      metas.insert(exp2m1);
      metas.insert(exp10m1);
      metas.insert(log);
      metas.insert(log2);
      metas.insert(log10);
      metas.insert(logp1);
      metas.insert(log2p1);
      metas.insert(log10p1);
      metas.insert(sin);
      metas.insert(cos);
      metas.insert(tan);
      metas.insert(asin);
      metas.insert(acos);
      metas.insert(atan);
      metas.insert(sinh);
      metas.insert(cosh);
      metas.insert(tanh);
      metas.insert(asinh);
      metas.insert(acosh);
      metas.insert(atanh);

      
      return metas;
    }
  }
}

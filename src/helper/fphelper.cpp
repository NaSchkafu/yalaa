#include "fphelper.hpp"

#include <fenv.h>
#include <math.h>

namespace yalaa
{
  namespace fp
  {

    RndControl::RndControl(bool reset)
      :m_old_mode(fegetround()), m_reset(reset), m_mode(m_old_mode)
    { }

    RndControl::~RndControl()
    {
      if(m_old_mode != m_mode && m_reset)
        fesetround(m_old_mode);
    }

    void RndControl::downward()
    {
      if(m_mode != FE_DOWNWARD) {
	fesetround(FE_DOWNWARD);
	m_mode = FE_DOWNWARD;
      }
    }

    void RndControl::upward()
    {
      if(m_mode != FE_UPWARD) {
	fesetround(FE_UPWARD);
	m_mode = FE_UPWARD;
      }
    }

    void RndControl::to_zero()
    {
      if(m_mode != FE_TOWARDZERO) {
	fesetround(FE_TOWARDZERO);
	m_mode = FE_TOWARDZERO;
      }
    }

    void RndControl::to_nearest()
    {
      if(m_mode != FE_TONEAREST) {
	fesetround(FE_TONEAREST);
	m_mode = FE_TONEAREST;
      }
    }

    inline bool is_infinity(double r)
    {
#ifdef _WIN32
		return _finite(r);
#else
      return isinf(r);
#endif
    }

    // TODO: unterscheiden!
    inline bool is_quiet_NaN(double r)
    {
#ifdef _WIN32
		return _isnan(r);
#else
      return isnan(r);
#endif
    }

    inline bool is_signaling_NaN(double r)
    {
 #ifdef _WIN32
		return _isnan(r);
#else
      return isnan(r);
#endif
    }

    inline bool is_nan(double r)
    {
#ifdef _WIN32
		return _isnan(r);
#else
      return isnan(r);
#endif
    }

    bool is_special(double d)
    {
      return is_nan(d) || is_infinity(d);
    }
  }
}


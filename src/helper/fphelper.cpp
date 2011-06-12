/*
  Copyright 2011 Stefan Kiel <kiel@inf.uni-due.de>
  
  This file is part of yalaa.
  
  yalaa is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, version 3 of the License.
  
  yalaa is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public License
  along with yalaa.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "fphelper.hpp"

#include <math.h>

#ifdef _MSC_VER
#include <float.h>

#define FE_DOWNWARD RC_DOWN
#define FE_UPWARD RC_UP
#define FE_TONEAREST RC_NEAR
#define FE_TOWARDZERO RC_CHOP

void fesetround(unsigned m) 
{
	_controlfp(MCW_RC, m);
}

unsigned fegetround() 
{
	return _controlfp(0,0) & (RC_DOWN | RC_UP | RC_NEAR | RC_CHOP);
}

#else
#include <fenv.h>
#endif

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
#ifdef _MSC_VER
      return !_finite(r);
#else
      return isinf(r);
#endif
    }

    // TODO: unterscheiden!
    inline bool is_quiet_NaN(double r)
    {
#ifdef _MSC_VER
      return _isnan(r);
#else
      return isnan(r);
#endif
    }

    inline bool is_signaling_NaN(double r)
    {
 #ifdef _MSC_VER
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

    unsigned get_flags(double val)
    {
      if(is_nan(val))
		return 32;
      else if(is_infinity(val))
		return 16;
      return 0;
    }

    // bool is_special(double d)
    // {
    //   return is_nan(d) || is_infinity(d);
    // }
  }
}


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


#ifndef __FPHELPER_HPP__
#define __FPHELPER_HPP__

namespace yalaa
{
  namespace fp
  {
    /// Helper class for rounding mode control
    class RndControl
    {
    public:
      /**
       * Ctor
       * Creates a new RndControl object and stores the current rounding mode
       *
       */
      explicit RndControl(bool reset = true);

      /**
       * Dtor
       * The old rounding mode (at construction of the object) is restored
       *
       */
      ~RndControl();

      /**
       * Sets the rounding mode towards -infinity
       */
      void downward();


      /**
       * Sets the rounding mode towards +infinity
       */
      void upward();

      /**
       * Sets the rounding mode to nearest
       */
      void to_nearest();

      /**
       * Sets the rounding mode towards zero
       */
      void to_zero();

    private:
      bool m_reset;
      int m_old_mode;
      int m_mode;
    };

    /** 
     * Returns approbiate flags for a double value
    * 
    * @param val double value
    * 
    * @return flags for ArithmeticError<double> class
    */
    unsigned get_flags(double val);
  }
}

#endif /*__FPHELPER_HPP__*/

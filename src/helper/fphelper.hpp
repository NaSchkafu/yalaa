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

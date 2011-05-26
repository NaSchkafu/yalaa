#include "exacterroraffinefp.hpp"

// -*-c++-*-
namespace yalaa
{
  namespace kernel
  {
    namespace details
    {
      // ****************************************************************
      // HELPER FUNCTION
      /**
       * Sums the rounding error of an operation
       * For getting an upper bound on the error,
       * set the rounding mode upward prior to calling this function.
       *
       * @param ac affine combination in round nearest mode
       * @param ac_down affine combination in round downard mode
       * @param ac_up affine combination in round upward mode
       *
       * @return Summation of error
       */
      template<typename AC>
      typename AC::base_t sum_error(const AC &ac, const AC &ac_down, const AC &ac_up)
      {
        typename AC::base_t err = 0.0;
        for(typename AC::aff_comb_const_iter it(ac.begin()), itdown(ac_down.begin()), itup(ac_up.begin());
            it != ac.end();++it)
          err += std::max(itup++->dev() - it->dev(), it->dev() - itdown++->dev());
        err += std::max(ac_up.central() - ac.central(), ac.central() - ac_down.central());
        return err;
      }
      // ****************************************************************

      template<typename T, template<typename> class ET, 
	       template<typename, template<typename> class> class AC>
      typename ExactErrorAffineFP<T, ET, AC>::aerror_t ExactErrorAffineFP<T, ET,AC>::neg(ac_t *ac)
      {
	neg_ac(ac);
        return yalaa::details::ArithmeticError<T>(0.0, true);
      }

      template<typename T, template<typename> class ET, 
	       template<typename, template<typename> class> class AC>
      T ExactErrorAffineFP<T, ET,AC>::scale_add(ac_t *ac, T scalec_down, T scalec_up,
					       T scalen_down, T scalen_up, T add_down, T add_up,
					       yalaa::fp::RndControl &rnd)
      {
        ac_t down(*ac);
        ac_t up(*ac);

        rnd.to_nearest();
	T scalec = (scalec_up + scalec_down)/2;
	T scalen = (scalen_up + scalen_down)/2;
	T add = (add_up + add_down)/2;
        mul_ac_s(ac, scalec, scalen);
        add_ac_s(ac, add);

        rnd.downward();
        mul_ac_s(&down, scalec_down, scalen_down);
        add_ac_s(&down, add_down);

        rnd.upward();
        mul_ac_s(&up, scalec_up, scalen_up);
        add_ac_s(&up, add_up);

        return sum_error(*ac, down, up);
      }

      template<typename T, template<typename> class ET, 
	       template<typename, template<typename> class> class AC>
      T ExactErrorAffineFP<T, ET,AC>::scale_add(ac_t *ac, T scalec, T scalen,
					       T add, yalaa::fp::RndControl &rnd)
      {
	return scale_add(ac, scalec, scalec, scalen, scalen, add, add, rnd);
      }	

      template<typename T, template<typename> class ET, 
	       template<typename, template<typename> class> class AC>
      template<bool CENTRAL>
      T ExactErrorAffineFP<T, ET,AC>::affine(ac_t *ac1, ac_t ac2, T scale1, T scale2,
					    T add, T central, yalaa::fp::RndControl &rnd)
      {
        ac_t down1(*ac1);
        ac_t up1(*ac1);
        ac_t down2(ac2);
        ac_t up2(ac2);

        rnd.to_nearest();
        mul_ac_s(ac1, scale1, scale1);
        mul_ac_s(&ac2, scale2, scale2);
        yalaa::details::add_ac_ac<ac_t, CENTRAL>(ac1, ac2);
        if(CENTRAL)
          add_ac_s(ac1, add);

        rnd.downward();
        mul_ac_s(&down1, scale1, scale1);
        mul_ac_s(&down2, scale2, scale2);
        yalaa::details::add_ac_ac<ac_t, CENTRAL>(&down1, down2);
        if(CENTRAL)
          add_ac_s(&down1, add);

        rnd.upward();
        mul_ac_s(&up1, scale1, scale1);
        mul_ac_s(&up2, scale2, scale2);
        yalaa::details::add_ac_ac<ac_t, CENTRAL>(&up1, up2);
        if(CENTRAL)
          add_ac_s(&up1, add);

        if(!CENTRAL) {
          ac1->set_central(central);
          up1.set_central(central);
          down1.set_central(central);
        }

        return sum_error(*ac1, down1, up1);
      }

      template<typename T, template<typename> class ET, 
	       template<typename, template<typename> class> class AC>
      T ExactErrorAffineFP<T, ET,AC>::affine(ac_t *ac1, ac_t ac2, T scale1, T scale2,
					    T add, yalaa::fp::RndControl &rnd)
      {
        return affine<true>(ac1, ac2, scale1, scale2, add, 0.0, rnd);
      }

      template<typename T, template<typename> class ET, 
	       template<typename, template<typename> class> class AC>
      T ExactErrorAffineFP<T, ET,AC>::affine(ac_t *ac1, ac_t ac2, T scale1, T scale2,
					    T add, T central, yalaa::fp::RndControl &rnd)
      {
        return affine<false>(ac1, ac2, scale1, scale2, add, central, rnd);
      }

/*
      template<template<typename> class ET, template<typename, template<typename> class> class AC>
      T ExactErrorAffineFP<ET,AC>::scale_noise_add(ac_t *ac, T scale, T add,
                                                       yalaa::fp::RndControl &rnd)
      {
        ac_t down(*ac);
        ac_t up(*ac);
        T ac0(ac->central());

        rnd.to_nearest();
        mul_ac_s(ac, scale);
        ac->set_central(ac0);
        add_ac_s(ac, add);

        rnd.downward();
        mul_ac_s(&down, scale);
        down.set_central(ac0);
        add_ac_s(&down, add);

        rnd.upward();
        mul_ac_s(&up, scale);
        up.set_central(ac0);
        add_ac_s(&up, add);

        return sum_error(*ac, down, up);
      }
*/


      template<typename T, template<typename> class ET, 
	       template<typename, template<typename> class> class AC>
      typename ExactErrorAffineFP<T, ET, AC>::aerror_t ExactErrorAffineFP<T, ET, AC>::add(ac_t *ac1, const ac_t &ac2)
      {
        if(ac1 == &ac2)
          return scale(ac1, yalaa::details::base_traits<T>::my_two());

        // TODO:
        // Unnötige Kopieroperation bei langen Affinen Formen
        // Die Verwendung der Trennung ArithmeticKernel und AffineCombination ist ineffektiv an dieser Stelle
        ac_t down(*ac1);
        ac_t up(*ac1);

        yalaa::fp::RndControl rnd;
        // Approx
        rnd.to_nearest();
        add_ac_ac(ac1, ac2);

        // Untere Schranke
        rnd.downward();
        add_ac_ac(&down, ac2);

        // Obere Schranke
        rnd.upward();
        add_ac_ac(&up,ac2);

        // Fehler zurückgeben
        T err = sum_error(*ac1, down, up);
        return yalaa::details::ArithmeticError<T>(err, yalaa::fp::get_flags(err));
      }

      template<typename T, template<typename> class ET, 
	       template<typename, template<typename> class> class AC>
      typename ExactErrorAffineFP<T, ET, AC>::aerror_t ExactErrorAffineFP<T, ET, AC>::sub(ac_t *ac1, const ac_t &ac2)
      {
        T err = 0.0;
        if(ac1 == &ac2)
          ac1->clear();
        else {
          // TODO:
          // s.o. fuer Kopierop
          ac_t down(*ac1);
          ac_t up(*ac1);

          yalaa::fp::RndControl rnd;
          // Approx
          rnd.to_nearest();
          sub_ac_ac(ac1, ac2);

          // Untere Schranke
          rnd.downward();
          sub_ac_ac(&down, ac2);

          // Obere Schranke
          rnd.upward();
          sub_ac_ac(&up,ac2);

          // Fehler zurückgeben
          err = sum_error(*ac1, down, up);
        }

        return yalaa::details::ArithmeticError<T>(err, yalaa::fp::get_flags(err));
      }

      template<typename T, template<typename> class ET, 
	       template<typename, template<typename> class> class AC>
      typename ExactErrorAffineFP<T, ET, AC>::aerror_t ExactErrorAffineFP<T, ET, AC>::add(ac_t *ac, T s)
      {
        T ac0, ac0_down, ac0_up;
        yalaa::fp::RndControl rnd;
        rnd.to_nearest();
        ac0 = ac->central()+s;
        rnd.downward();
        ac0_down = ac->central()+s;
        rnd.upward();
        ac0_up = ac->central()+s;
        T err = std::max(ac0_up - ac0, ac0 -ac0_down);
        ac->set_central(ac0);
        return yalaa::details::ArithmeticError<T>(err, yalaa::fp::get_flags(err));
      }

      template<typename T, template<typename> class ET, 
	       template<typename, template<typename> class> class AC>
      typename ExactErrorAffineFP<T, ET, AC>::aerror_t ExactErrorAffineFP<T, ET, AC>::scale(ac_t *ac, 
										       T s, bool inv)
      {
        // s.o. fuer Kopierop
        ac_t down(*ac);
        ac_t up(*ac);

        yalaa::fp::RndControl rnd;
        // Approx
        rnd.to_nearest();
        mul_ac_s(ac, inv ? 1/s : s, inv ? 1/s : s);

        // Untere Schranke
        rnd.downward();
        mul_ac_s(&down, inv ? 1/s : s, inv ? 1/s : s);

        // Obere Schranke
        rnd.upward();
        mul_ac_s(&up, inv ? 1/s : s, inv ? 1/s : s);

        // Fehler zurückgeben
        T err = sum_error(*ac, down, up);
        return yalaa::details::ArithmeticError<T>(err, yalaa::fp::get_flags(err));
      }


      template<typename T, template<typename> class ET, 
	       template<typename, template<typename> class> class AC>
      typename ExactErrorAffineFP<T, ET, AC>::aerror_t ExactErrorAffineFP<T, ET, AC>::scale(ac_t *ac, T s)
      {
	return scale(ac, s, false);
      }

      template<typename T, template<typename> class ET, 
	       template<typename, template<typename> class> class AC>
      typename ExactErrorAffineFP<T, ET, AC>::aerror_t ExactErrorAffineFP<T, ET, AC>::inv_scale(ac_t *ac, T s)
      {
	return scale(ac, s, true);
      }
    }
  }
}

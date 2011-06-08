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


// Implementierung der affinen Operationen von ExactError<float, double, long double>
#ifndef __EXACTERRORAFFINED_HPP__
#define __EXACTERRORAFFINED_HPP__

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_floating_point.hpp>

namespace yalaa
{
  namespace fp 
  {
    class RndControl;
  }

  namespace kernel
  {
    namespace details
    {
      template<typename T, template<typename> class ET, 
	       template<typename, template<typename> class> class AC>
      struct ExactErrorAffineFP
      {
	// This operations are only verified for floating-point numbers
	// according to IEEE 754, please check the implementation carefully
	// if you are using other types
	BOOST_STATIC_ASSERT(boost::is_floating_point<T>::value);

	typedef ET<T> error_t;
        typedef AC<T, ET> ac_t;
        typedef yalaa::details::ArithmeticError<T> aerror_t;
        typedef ExactErrorAffineFP<T, ET, AC> self_t;
  
        static aerror_t add(ac_t *ac1, const ac_t& ac2);
        static aerror_t sub(ac_t *ac1, const ac_t& ac2);
        static aerror_t add(ac_t *ac, T s);
        static aerror_t scale(ac_t *ac, T s);
	static aerror_t inv_scale(ac_t *ac, T s);
	static aerror_t neg(ac_t *ac);

        // /**
        //  * Calculates an affine transformation for ac (ac = scale*ac + add)
        //  * The result is stored in ac
        //  * (only for internal use, floating-point env is not restored after function call!)
        //  *
        //  * @param ac affine form
        //  * @param scale scaling factor
        //  * @param add addition term
        //  * @param rnd rounding control
        //  *
        //  * @return error bounds
        //  */
        // static T scale_add(ac_t *ac, T scale, T add, yalaa::fp::RndControl &rnd);

        /**
         * Calculates an affine transformation for ac (ac1 = scale1*ac1 + scale2*ac2 + add)
         * The result is stored in ac
         * (only for internal use, floating-point env is not restored after function call!)
         *
         * @param ac1 affine form 1
         * @param ac2 affine form 2
         * @param scale1 scaling 1
         * @param scale2 scaling 2
         * @param add addition
         * @param rnd rounding control
         *
         * @return error bounds
         */
        static T affine(ac_t *ac1, ac_t ac2, T scale1, T scale2,
                             T add, yalaa::fp::RndControl &rnd);

        /**
         * Calculates an affine transformation for ac1 (ac1 = scale1*ac1 + scale2*ac2 + add)
         * and sets the central value to central
         * The result is stored in ac1
         * (only for internal use, floating-point env is not restored after function call!)
         *
         * @param ac1 affine form 1
         * @param ac2 affine form 2
         * @param scale1 scaling 1
         * @param scale2 scaling 2
         * @param add addition
         * @param central central value
         * @param rnd rounding control
         *
         * @return error bounds
         */
        static T affine(ac_t *ac1, ac_t ac2, T scale1, T scale2,
                             T add, T central, yalaa::fp::RndControl &rnd);

	/** 
	 * Scales an affine form calculating ac = (ac0*scalec + add) + (ac1*scalen) + ...
	 * The result is stored in ac
	 * (only for internal use, floating-point env is not restored after function call!)
	 * 
	 * @param ac  affine form
	 * @param scalec_down scaling factor for central (lower bound)
	 * @param scalec_up scaling factor for central (upper bound)
	 * @param scalen_down scaling factor for noise (lower bound)
	 * @param scalen_up scaling factor for noise (upper bound)
	 * @param add_down addition (lower bound)
	 * @param add_up addition (upper bound)
	 * @param rnd rounding control
	 * 
	 * @return error bounds
	 */
	static T scale_add(ac_t *ac, T scalec_down, T scalec_up,  T scalen_down, 
				T scalen_up, T add_down, T add_up, yalaa::fp::RndControl &rnd);


	/** 
	 * Convience function for scaling, calls scale_add with scale_up == scale_down
	 * 
	 * @param ac affine form
	 * @param scalen scaling factor for central
	 * @param add addition
	 * @param rnd rounding control
	 * 
	 * @return error bounds
	 */
	static T scale_add(ac_t *ac, T scalec, T scalen,
				T add, yalaa::fp::RndControl &rnd);

        // /**
        //  * Scales the noise symbols of the affine form and translates the form
        //  * (ac = (ac_0 + add) + scale*ac_i i > 0)
        //  * (only for internal use, floating-point env is not restored after function call!)
        //  *
        //  * @param ac affine form
        //  * @param scale scaling factor
        //  * @param add addition
        //  * @param rnd rounding control
        //  *
        //  * @return error bounds
        //  */
        // static T scale_noise_add(ac_t *ac, T scale, T add, yalaa::fp::RndControl &rnd);


      private:
        template<bool CENTRAL>
        static T affine(ac_t *ac1, ac_t ac2, T scale1, T scale2,
                             T add, T central, yalaa::fp::RndControl &rnd);

        static aerror_t scale(ac_t *ac, T s, bool inv);
      };
    }
  }
}

#endif /*__EXACTERRORAFFINED_HPP__*/

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


#ifndef __AFFINECOMBOPIMPL_HPP__
#define __AFFINECOMBOPIMPL_HPP__

namespace yalaa
{
  namespace details
  {
    /// Standard implementation of the bassic affine operations
    /**
     * This structures provides an implementation of the most basic building blocks of YalAA.
     * All operations of YalAA are finally mapped into the operations declared here.
     * No rounding control is done here.
     * However, this concrete implementation supports handling of special symbols according to the
     * AF1 and AF2 policies.
     */
    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC>
    struct AffineCombOpImpl
    {
      typedef T base_t;
      typedef ET<base_t> error_t;
      typedef AC<base_t, ET> ac_t;

      /**
       * Adds two affine combinations
       * The result is stored inside the first combination
       * Ignores the central value
       * 
       * @param ac1 First combination
       * @param ac2 Second combination
       *
       * @return Number of performed additions
       */
      static unsigned add_ac_ac_noc(ac_t* ac1, const ac_t &ac2);

      /**
       * Adds two affine combinations
       * The result is stored inside the first combination
       * 
       * @param ac1 First combination
       * @param ac2 Second combination
       *
       * @return Number of performed additions
       */
      static unsigned add_ac_ac(ac_t* ac1, const ac_t &ac2);

      /**
       * Substracts two affine combinations
       * The result is stored inside the first combination
       *
       * @param ac1 First combination
       * @param ac2 Second combination
       *
       * @return Number of performed substractions
       */
      static unsigned sub_ac_ac(ac_t* ac1, const ac_t &ac2);

      /**
       * Substracts two affine combinations
       * The result is stored inside the first combination
       * Ignores the central value
       * 
       * @param ac1 First combination
       * @param ac2 Second combination
       *
       * @return Number of performed substractions
       */
      static unsigned sub_ac_ac_noc(ac_t* ac1, const ac_t &ac2);

      /**
       * Scales an affine combination
       *
       * @param ac1 Affine combination to scale
       * @param sc Scaling factor central
       * @param sn Scaling factor noise
       *
       * @return Number of operations
       */
      static unsigned mul_ac_s(ac_t *ac, typename ac_t::base_ref_t sc, typename ac_t::base_ref_t sn);

      /**
       * Adds an scalar to an affine combination
       *
       * @param ac1 Affine combination for addition
       * @param s Scalar to add
       *
       * @return Number of operations
       */
      static unsigned add_ac_s(ac_t *ac, typename ac_t::base_ref_t s);

      /**
       * Negates an affine combination
       *
       * @param ac Affine combination to negate
       *
       * @return number of operations
       */
      static unsigned neg_ac(ac_t *ac);

    private:
      template<bool ADD, bool CENTRAL>
      static unsigned add_ac_ac_gen(ac_t *ac1, const ac_t &ac2);
    };
  }
}


#endif /*__AFFINECOMBOP_HPP__*/

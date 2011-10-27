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

namespace yalaa 
{
  namespace concepts 
  {
  
    /// Concept defining an affine combination
    /**
     * This concept defines an affine combination.
     * 
     * Affine combinations are the most basic building blocks of YalAA.
     * An affine combination consists of a central value \f$x_0\f$ and ErrorTerms \f$x_i\epsilon_i\f$.
     * Furthermore, this structures defines the basic affine operations addition, scaling and 
     * translation.
     * All operations of YalAA are finally mapped into the operations declared here.
     * No rounding control is done at this level.
     * 
     * @param T Type for partial deviations
     * @param ET Implementation of the ErrorTerm concept to use
     */
    template<typename T, template<typename> class ET>
    struct AffineCombination
    {
      /// Type for partial deviations
      typedef T base_t;
      /// Type for error terms
      typedef ET<base_t> error_t;
      /// Const reference or base_t depending whether base_t is a fundamental type. 
      typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;
      /// Type of *this
      typedef AffineCombination<T, ET> self_t;
      /// Type for size of the combination
      typedef typename std::vector<ET<T> >::size_type size_t;
      /// const iterator type for affine combination
      typedef typename std::vector<ET<T> >::const_iterator aff_comb_const_iter;
      /// iterator type for affine combination
      typedef typename std::vector<ET<T> >::iterator aff_comb_iter;

      /**
       * Adds two affine combinations.
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
       * Adds two affine combinations.
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

      
      /** 
       * Ctor<br>
       * Creates a new affine combination with the specified central value
       * 
       * @param central central value
       * 
       */
      explicit AffineCombBaseImpl(base_ref_t central);

      /** 
       * Ctor
       * 
       * 
       */
      AffineCombBaseImpl();

      /** 
       * Gets an iterator pointing to the combination's first element
       * 
       * 
       * @return Iterator pointing to first element
       */
      aff_comb_const_iter begin() const;

      /** 
       * Gets an iterator pointing behin the combination's last element
       * 
       * 
       * @return Iterator pointing behind last element
       */
      aff_comb_const_iter end() const;

      /** 
       * Gets an iterator pointing to the combination's first element
       * 
       * 
       * @return Iterator pointing to first element
       */
      aff_comb_iter begin();

      /** 
       * Gets an iterator pointing behind the combination's last element
       * 
       * 
       * @return Iterator pointing behind last element
       */
      aff_comb_iter end();

      /** 
       * Removes an error term from the combination
       * 
       * @param term Term to remove
       */
      void remove(const error_t &term);
      
      /** 
       * Removes an error term from the combination
       * 
       * @param it Iterator pointing on term to remove
       */
      void remove(const aff_comb_iter &it);

      /** 
       * Inserts a new term into the combination
       * NOTE: The term must not part of the current combination!
       * 
       * @param term Term to insert
       * 
       * @return Iterator pointing to inserted element
       */
      aff_comb_iter insert(const ET<T> &term);

      /** 
       * Inserts a new term into the combination before position pos
       * 
       * @param term term to insert
       * @param pos position to add
       * 
       * @return Iterator pointing to inserted element
       */
      aff_comb_iter insert(const ET<T> &term, const aff_comb_iter &pos);

      /** 
       * Gets the central value
       * 
       * 
       * @return Central value
       */
      base_t central() const;

      /** 
       * Sets a new central value
       * 
       * @param central New central value
       */
      void set_central(base_ref_t central);

      /** 
       * Gets the number of affine terms in the combination
       * 
       * 
       * @return number of terms
       */
      size_t size() const;

      /** 
       * Resets the affine combination
       * 
       */
      void clear();

      /** 
       * Inserts a new error term at the end of the combination
       * No checks are performed for this operation. The caller has to
       * make sure, that the affine combination is still valid after insertation!
       * 
       * @param term term
       */
      void push_back(const ET<T> &term);

      /** 
       * Finds an element inside the combination
       * 
       * @param term error term
       * 
       * @return element
       */
      aff_comb_iter find(const ET<T> &term);
    };
  }
}


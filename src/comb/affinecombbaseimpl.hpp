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


#ifndef __AFFINECOMBBASEIMPL_HPP__
#define __AFFINECOMBBASEIMPL_HPP__

#include <algorithm>
#include <vector>
#include "yalaa_assert.hpp"


namespace yalaa 
{
  namespace details 
  {
    /// default implementation of an affine combination
    /**
     * The class provides an implementation for the AffineCombination concept
     * The first template parameter T is the type for the partial deviations
     * The seconnd template parameter ET is the type for error terms which is automatically
     * specialized as ET<T>.
     *  
     * The class uses internally an sorted vector for storing the affine combination.
     */
    template<typename T, template<typename> class ET>
    class AffineCombBaseImpl
    {
    public:
      typedef T base_t;
      typedef ET<T> error_t;
      typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;
      typedef AffineCombBaseImpl<T, ET> self_t;

      typedef typename std::vector<ET<T> >::size_type size_t;
      // TODO: Bessere Adapter mit Boost.Iterator statt vector-It nach außen geben
      /// const iterator type for affine combination
      typedef typename std::vector<ET<T> >::const_iterator aff_comb_const_iter;
      /// iterator type for affine combination
      typedef typename std::vector<ET<T> >::iterator aff_comb_iter;

      
      /** 
       * Ctor
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
       * Removes an error term from the combination
       * 
       * @param it Iterator pointing on term to remove
       */
//      void remove(const aff_comb_const_iter &it);

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

    private:
      std::vector<ET<T> > m_errors;
      T m_central;
//      short m_special;
    };
  }
}

#endif /*__AFFINECOMBBASEIMPL_HPP__*/

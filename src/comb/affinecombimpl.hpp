#ifndef __AFFINECOMBIMPL_HPP__
#define __AFFINECOMBIMPL_HPP__

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
    class AffineCombImpl
    {
    public:
      typedef T base_t;
      typedef ET<T> error_t;
      typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;
      typedef AffineCombImpl<T, ET> self_t;

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
      explicit AffineCombImpl(base_ref_t central);

      /** 
       * Ctor
       * 
       * 
       */
      AffineCombImpl();

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

#endif /*__AFFINECOMBIMPL_HPP__*/

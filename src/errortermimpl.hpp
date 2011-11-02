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


#ifndef __ERRORTERMIMPL_HPP__
#define __ERRORTERMIMPL_HPP__

#include <boost/type_traits.hpp>
#include <boost/mpl/if.hpp>
#include <iosfwd>

namespace yalaa
{
  namespace details
  {
    /// Default implementation of the \c ErrorTerm concept
    /**
     * This class provides an implementation for the \c ErrorTerm concept
     * An unsigned 64 - Bit integer is used for the symbolic noise variable
     * Partial deviation is stored as the provided template type.
     *
     * \todo Rework handling of special values for AF1, AF2...
     */
    template <typename T>
    class ErrorTermImpl
    {
    public:
      typedef ErrorTermImpl<T> self_t;
      typedef T base_t;
      typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;
      typedef void trait_is_err_t;

      ErrorTermImpl();
      ErrorTermImpl(const self_t &other);
      ErrorTermImpl(base_ref_t dev);

      inline bool operator==(const self_t &other) const;

      inline bool operator<(const self_t &other) const;

      inline base_ref_t dev() const;

      inline void set_dev(base_ref_t new_dev);

      inline void print(std::ostream &os) const;

      inline unsigned special() const;
      
      inline void set_special(unsigned type);

    private:
      inline static unsigned long long new_symbol();

    private:
      unsigned long long m_eps;

      T m_dev;

      static unsigned long long CURRENT_EPS;

      static unsigned long long MIN_SPECIAL;
    };
    
    #include "errortermimpl.inl"
  }
}

#endif /*__ERRORTERMIMPL_HPP__*/

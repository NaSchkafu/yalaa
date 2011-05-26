#ifndef __ERRORTERMIMPL_HPP__
#define __ERRORTERMIMPL_HPP__

#include <boost/type_traits.hpp>
#include <boost/mpl/if.hpp>
#include <iosfwd>

namespace yalaa
{
  namespace details
  {
    /// default implementation of an error term
    /**
     * This class provides an implementation for the ErrorTerm concept
     * An unsigned 64 - Bit integer is used for the symbolic noise variable
     * Partial deviation is stored as the provided template type.
     */
    // TODO: Handling Multithread via memory Barriere
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

      /**
       * Checks whether two error terms have the same symbolic noise variable
       *
       * @param other Other error term to check
       *
       * @return true if both terms have the same symbolic noise variable
       */
      inline bool operator==(const self_t &other) const;

      /**
       * Defines an ordering on the symbolic noise variable
       *
       * @param other Other error term
       *
       * @return true if this error term is less than the other in the ordering
       */
      inline bool operator<(const self_t &other) const;

      /** 
       * Gets the current deviation of the error term
       * 
       * @return Current deviation of this error term
       */
      inline base_ref_t dev() const;

      /** 
       * Sets deviation of this error term
       * 
       * @param new_dev new deviation
       */
      inline void set_dev(base_ref_t new_dev);

      /** 
       * Prints this error term to a stream
       * 
       * @param os output stream
       */
      inline void print(std::ostream &os) const;

    private:
      inline static unsigned long long new_symbol();

    private:
      unsigned long long m_eps;
      T m_dev;

      static unsigned long long CURRENT_EPS;
    };
    
    #include "errortermimpl.inl"
  }
}

#endif /*__ERRORTERMIMPL_HPP__*/

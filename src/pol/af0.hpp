#ifndef __AF0_HPP__
#define __AF0_HPP__

#include "kernel/arithmeticerror.hpp"

namespace yalaa
{
  namespace pol
  {
    // T Basis
    // ET<T> ErrorTerm
    // AC<T, ET<T> > AffComb
    template<typename T, template<typename> class ET, 
	     template<typename, template<typename> class> class AC>
    class AF0
    {
    public:
      typedef T base_t;
      typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;

      /// Called for adding errors (approximation, rounding errors, ...)
      /** 
       * In AF0 this adds a new independet error symbol for the error's sum
       * 
       * @param ac affine combination
       * @param err error
       */
      static void add_errors(AC<T, ET> *ac, const yalaa::details::ArithmeticError<T> &err)
        {
	  if(err.sum() != yalaa::details::base_traits<base_t>::my_zero())
	    ac->insert(typename AC<T, ET>::error_t(err.sum()));
        }

      /// Called for creating by creating a new affine form
      /** 
       * In AF0 this adds a new independet error symbol with the specified uncertainty
       * 
       * @param ac affine combination
       * @param uncert uncertainty
       */
      static void new_form(AC<T, ET> *ac, base_ref_t uncert) 
	{
	  ac->insert(typename AC<T,ET>::error_t(uncert));
	}

      /// Called for introducing uncertainty into an existing form
      /** 
       * In AF0 this acts as new_form, i.e. introducing a new independet error symbol with the
       * specified uncertainty
       * 
       * @param ac affine combination
       * @param uncert uncertainty
       */
      static void add_uncert(AC<T, ET> *ac, base_ref_t uncert)
	{
	  ac->insert(typename AC<T,ET>::error_t(uncert));
	}

    };
  }
}


#endif /*__AF0_HPP__*/

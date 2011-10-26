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

/**
 * @file   affineform.hpp
 * @author Stefan Kiel <kiel@inf.uni-due.de>
 * @date   Wed Oct 26 16:53:13 2011
 * 
 * @brief  Contains definition of the AffineForm class template and associated functions
 * 
 * 
 */


#ifndef __AFFINEFORM_HPP__
#define __AFFINEFORM_HPP__

//#include "base_traits.hpp"
#include <boost/mpl/has_xxx.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/mpl/if.hpp>
#include <boost/operators.hpp>

namespace yalaa
{

  // T Basistyp
  // ET ErrorTyp -> ET<T>
  // AC AffComb -> AC<T, ET<T> >
  // AR Arith Kernel -> AR<T, ET<T>, AC<T, ET<T> >, IV >
  // AP AffinePolicy -> AP<T, ET<T>, AC<T, ET<T> > >
  // EP ErrorPolicy
  // IV Interval Type
#define YALAA_AFF_TEMPLATE template<typename T, template<typename> class ET, \
                                    template<typename, template<typename> class> class AC, \
                                    template<typename, template<typename> class, template<typename, template<typename> class> class, class> class AR, \
                                    template<typename, template<typename> class, template<typename, template<typename> class> class> class AP, \
                                    template<typename, typename> class EP, typename IV>
#define YALAA_DECL AffineForm<T, ET, AC, AR, AP, EP, IV>
#define YALAA_DECL_T typename AffineForm<T, ET, AC, AR, AP, EP, IV>
#define YALAA_FRIEND_DECL   template<typename AF>			\
  friend typename boost::enable_if<details::has_trait_is_aff_t<AF>,AF>::type

  namespace details 
  {
    BOOST_MPL_HAS_XXX_TRAIT_DEF(trait_is_aff_t)
  }

  /// Class template for all affine forms
  /**
   * This templates combines all policy classes and helper classes of \c YalAA to provide 
   * the final type for affine arithmetic.
   * It supports the usual arithmetic operations through operator overloading. Elementary
   * functions are providied as \c friend's.
   * 
   */
  YALAA_AFF_TEMPLATE
  class AffineForm : boost::arithmetic<AffineForm<T, ET, AC, AR, AP, EP, IV>,
                     boost::arithmetic<AffineForm<T, ET, AC, AR, AP, EP, IV>, IV,
	             boost::subtractable2_left<AffineForm<T, ET, AC, AR, AP, EP, IV>, IV,
		     boost::dividable2_left<AffineForm<T, ET, AC, AR, AP, EP, IV>, IV,
                     boost::arithmetic<AffineForm<T, ET, AC, AR, AP, EP, IV>, T,
	             boost::subtractable2_left<AffineForm<T, ET, AC, AR, AP, EP, IV>, T,
                     boost::dividable2_left<AffineForm<T, ET, AC, AR, AP, EP, IV>, T > > > > > > >
  {
  public:
    // ****************************************************************
    // typedefs
    // ****************************************************************
    typedef AffineForm<T, ET, AC, AR, AP, EP, IV> self_t;
    typedef T base_t;
    typedef ET<T> error_t;
    typedef AC<T, ET> ac_t;
    typedef AR<T, ET, AC, IV> ar_t;
    typedef AP<T, ET, AC> ap_t;
    typedef IV iv_t;
    typedef EP<T, iv_t> ep_t;
    typedef typename boost::mpl::if_<boost::is_fundamental<base_t>, base_t, typename boost::add_const<typename boost::add_reference<base_t>::type>::type>::type base_ref_t;
    typedef void trait_is_aff_t;
    typedef yalaa::details::base_traits<iv_t> iv_traits;

  public:
    /**
     * Ctor
     *
     * @param value scalar value
     */
    explicit AffineForm(base_ref_t value);

    /**
     * Ctor
     *
     * @param iv interval value
     */
    explicit AffineForm(const iv_t &iv);

    /**
     * Ctor
     *
     * @param svalue special value
     */
    explicit AffineForm(typename ep_t::special_t svalue);

    /**
     * Copy ctor
     *
     * @param other
     */
    //AffineForm(const self_t &other);
    
    // ****************************************************************
    // Helper
    // ****************************************************************
    /** 
     * Gets a reference to the underlying affine combination
     * 
     * 
     * @return reference to underlying affine combination
     */
    const ac_t& ac() const;

    /** 
     * Gets a reference to the underlying affine combination
     * 
     * 
     * @return reference to underlying affine combination
     */
    ac_t& ac();    
    // ****************************************************************
    
    

    // ****************************************************************
    // Affine <op>= affine
    // ****************************************************************
    /**
     * Assign add operator
     *
     * @param other summand
     *
     * @return reference to altered *this
     */
    self_t& operator+=(const self_t &other);

    /**
     * Assign subtract operator
     *
     * @param other subtrahend
     *
     * @return reference to altered *this
     */
    self_t& operator-=(const self_t &other);

    /**
     * Assign multiply operator
     *
     * @param other factor
     *
     * @return reference to altered *this
     */
    self_t& operator*=(const self_t &other);

    /**
     * Assign divide operator
     *
     * @param other divisor
     *
     * @return reference to altered *this
     */
    self_t& operator/=(const self_t &other);

    // ****************************************************************
    // affine <op>= base_t
    // ****************************************************************
    /**
     * Assign add operator
     *
     * @param other summand
     *
     * @return reference to altered *this
     */
    self_t& operator+=(base_ref_t other);

    /**
     * Assign subtract operator
     *
     * @param other subtrahend
     *
     * @return reference to altered *this
     */
    self_t& operator-=(base_ref_t other);

    /**
     * Assign multiply operator
     *
     * @param other factor
     *
     * @return reference to altered *this
     */
    self_t& operator*=(base_ref_t other);

    /**
     * Assign divide operator
     *
     * @param other divisor
     *
     * @return reference to altered *this
     */
    self_t& operator/=(base_ref_t other);


    // ****************************************************************
    // affine <op>= interval
    // ****************************************************************
    /**
     * Assign add operator
     *
     * @param other summand
     *
     * @return reference to altered *this
     */
    self_t& operator+=(const iv_t& other);

    /**
     * Assign subtract operator
     *
     * @param other subtrahend
     *
     * @return reference to altered *this
     */
    self_t& operator-=(const iv_t& other);

    /**
     * Assign multiply operator
     *
     * @param other factor
     *
     * @return reference to altered *this
     */
    self_t& operator*=(const iv_t& other);

    /**
     * Assign divide operator
     *
     * @param other divisor
     *
     * @return reference to altered *this
     */
    self_t& operator/=(const iv_t& other);

    // ****************************************************************
    // Misc Operators
    // ****************************************************************
    /** 
     * Self negation
     * 
     * 
     * @return reference to altered *this
     */
    self_t& operator-();

    /** 
     * Unary addition
     * (has no effect)
     * 
     * @return reference to *this
     */
    self_t& operator+();

    /** 
     * Compares two affine forms
     * 
     * @param other other form
     * 
     * @return true if both forms are equal
     */
    bool operator==(const self_t &other) const;

    // ****************************************************************
    // Elementary functions
    // (friends)
    // ****************************************************************

    /** 
     * Squares an affine form
     * 
     * @param AF affine form
     * 
     * @return square of AF
     */
    YALAA_FRIEND_DECL sqr(AF);

    /** 
     * Square root of an affine form
     * 
     * @param AF affine form
     * 
     * @return square root
     */
    YALAA_FRIEND_DECL sqrt(AF);

    /** 
     * Integer power function for affine forms
     * 
     * @param AF affine form
     * @param int integer
     * 
     * @return 
     */
    YALAA_FRIEND_DECL pown(AF, int);
    YALAA_FRIEND_DECL exp(AF);
    YALAA_FRIEND_DECL exp2(AF);
    YALAA_FRIEND_DECL exp10(AF);
    YALAA_FRIEND_DECL expm1(AF);
    YALAA_FRIEND_DECL exp2m1(AF);
    YALAA_FRIEND_DECL exp10m1(AF);
    YALAA_FRIEND_DECL log(AF);
    YALAA_FRIEND_DECL log2(AF);
    YALAA_FRIEND_DECL log10(AF);
    YALAA_FRIEND_DECL logp1(AF);
    YALAA_FRIEND_DECL log2p1(AF);
    YALAA_FRIEND_DECL log10p1(AF);
    YALAA_FRIEND_DECL sin(AF);
    YALAA_FRIEND_DECL cos(AF);
    YALAA_FRIEND_DECL tan(AF);
    YALAA_FRIEND_DECL asin(AF);
    YALAA_FRIEND_DECL acos(AF);
    YALAA_FRIEND_DECL atan(AF);
    YALAA_FRIEND_DECL sinh(AF);
    YALAA_FRIEND_DECL cosh(AF);
    YALAA_FRIEND_DECL tanh(AF);
    YALAA_FRIEND_DECL asinh(AF);
    YALAA_FRIEND_DECL acosh(AF);
    YALAA_FRIEND_DECL atanh(AF);
    YALAA_FRIEND_DECL powr(AF, int, unsigned);
    YALAA_FRIEND_DECL pow(AF, const AF&);

  private:
    /// affine combination
    ac_t m_a;
    /// flag for special forms
    typename ep_t::special_t m_special;
// NOTE: befriending templates is disallowed in C++ 03
#ifdef _MSC_VER
	// MSVC accepts the new C++ 0x syntax
	friend EP<T, IV>;
#else
	// g++ and clang++ accept this
    friend class EP<T, IV>;
#endif
  };
  
  /** 
   * Gets an interval enclosure for an affine form
   * 
   * @param af affine form
   * 
   * @return interval enclosure
   */
  YALAA_AFF_TEMPLATE
  typename AffineForm<T, ET, AC, AR, AP, EP, IV>::iv_t
  to_iv(const AffineForm<T, ET, AC, AR, AP, EP, IV> & af);

  /** 
   * Gets the radius for an affine form
   * 
   * @param af affine form
   * 
   * @return radius
   */
  YALAA_AFF_TEMPLATE
  typename AffineForm<T, ET, AC, AR, AP, EP, IV>::base_t
  rad(const AffineForm<T, ET, AC, AR, AP, EP, IV> & af);
}

#undef YALAA_AFF_TEMPLATE
#undef YALAA_DECL
#undef YALAA_DECL_T
#undef YALAA_FRIEND_DEF
#undef YALAA_FRIEND_DECL

#include "affineform.inl"

#endif /*__AFFINEFORM_HPP__*/

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


#ifndef __FASTIA_HPP__
#define __FASTIA_HPP__

namespace yalaa 
{
  namespace fp 
  {
    /** 
     * Adds an scalar to an interval
     * Note: This operation is only valid for IEEE754.
     * Rounding towards infinity is required, otherwise the result is not verified!
     * 
     * @param iv interval
     * @param s scalar s 
     * 
     * @return enclosure of addition
     */
    template<typename T, typename IV>
    inline IV fast_add_id_up(const IV& iv, T s);
    
    template<typename IV>
    inline IV fast_add_ii_up(const IV& iv1, const IV& iv2);

    template<typename T, typename IV>
    inline IV fast_sub_dd_up(T s1, T s2);

    /** 
     * Substracts an scalar from an interval
     * Note: This operation is only valid for IEEE754.
     * Rounding towards infinity is required, otherwise the result is not verified!
     * 
     * @param iv interval
     * @param s scalar s 
     * 
     * @return enclosure of addition
     */
    template<typename T, typename IV>
    inline IV fast_sub_id_up(const IV& iv, T s);

    // template<typename T, typename IV>
    // inline IV fast_sub_ii_up(const IV& iv, T s);

    /** 
     * Adds two scalars
     * Note: This operation is only valid for IEEE754.
     * Rounding towards infinity is required, otherwise the result is not verified!
     * 
     * @param s1 scalar 1
     * @param s2 scalar 2
     * 
     * @return enclosure of addition
     */
    template<typename T, typename IV>
    inline IV fast_add_dd_up(T s1, T s2);

    template<typename T, typename IV>
    inline IV fast_mul_dd_up(T s1, T s2);

    template<typename T, typename IV>
    inline IV fast_div_id_up(IV iv, T s);

    template<typename T, typename IV>
    inline IV fast_div_dd_up(T s1, T s2);

// ************************************************************************************************ 


    template<typename IV>
    IV fast_sub_ii_up(const IV& iv1, const IV& iv2)
    {
      return fast_add_ii_up(iv1, yalaa::traits::interval_traits<IV>::my_neg(iv2));
    }

    template<typename T, typename IV>
    IV fast_div_id_up(IV iv, T s)
    {
      typedef yalaa::traits::interval_traits<IV> iv_traits;
      if(s < 0) {
	iv = iv_traits::my_neg(iv);
	s = fabs(s);
      }
      T lb = (-iv_traits::my_inf(iv)*s);
      return IV(-lb, iv_traits::my_sup(iv)*s);
    }

    template<typename IV>
    IV fast_add_ii_up(const IV& iv1, const IV& iv2)
    {
      typedef yalaa::traits::interval_traits<IV> iv_traits;
      typename iv_traits::iv_base_t lb(-iv_traits::my_inf(iv1)-iv_traits::my_inf(iv2));
      return IV(-lb, iv_traits::my_sup(iv1)+iv_traits::my_sup(iv2));
    }

    template<typename T, typename IV>
    IV fast_mul_dd_up(T s1, T s2)
    {
      T lb = -s1*s2;
      return IV(-lb, s1*s2);
    }

    template<typename T, typename IV>
    IV fast_sub_dd_up(T s1, T s2)
    {
      T lb = s2 - s1;
      return IV(-lb, s1-s2);
    }

    template<typename T, typename IV>
    IV fast_add_id_up(const IV& iv, T s)
    {
      typedef yalaa::traits::interval_traits<IV> iv_traits;
      T a = -iv_traits::my_inf(iv)-s;
      T b = iv_traits::my_sup(iv)+s;
      return iv_t(-a, b);
    }

    template<typename T, typename IV>
    IV fast_add_dd_up(T s1, T s2)
    {
      typedef yalaa::traits::interval_traits<IV> iv_traits;
      T a = -s1-s2;
      T b = s1+s2;
      return IV(-a, b);
    }

    template<typename T, typename IV>
    IV fast_sub_id_up(const IV& iv, T s)
    {
      typedef yalaa::traits::interval_traits<IV> iv_traits;
      T a = s-iv_traits::my_inf(iv);
      T b = iv_traits::my_sup(iv)-s;
      return IV(-a, b);
    }
  }
}

#endif /*__FASTIA_HPP__*/

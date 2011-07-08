// -*-c++-*-

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

template<typename T, template<typename> class ET, 
	 template<typename, template<typename> class> class AC>
void AF0<T, ET, AC>::add_errors(AC<T, ET> *ac, const yalaa::details::ArithmeticError<T> &err)
{
  T errn(err.gen());
  // Scaling Pos Fehler
  if(err.pos() != b_traits_t::my_zero()) {
    base_t errn_p(b_traits_t::my_half_up(err.pos()));
    base_t nc(b_traits_t::my_add_up(ac->central(), errn_p));
    errn = b_traits_t::my_add_up(errn, b_traits_t::my_sub_up(nc,b_traits_t::my_add_down(ac->central(), b_traits_t::my_half_down(err.pos()))));
	    errn = b_traits_t::my_add_up(errn, errn_p);
	    ac->set_central(nc);
  }
  if(err.neg() != b_traits_t::my_zero()) {
    base_t errn_n(b_traits_t::my_half_up(err.neg()));
    base_t nc(b_traits_t::my_sub_up(ac->central(), errn_n));
    errn = b_traits_t::my_add_up(errn, b_traits_t::my_sub_up(nc, b_traits_t::my_sub_down(ac->central(), b_traits_t::my_half_down(err.neg()))));
    errn = b_traits_t::my_add_up(errn, errn_n);
    ac->set_central(nc);
  }

  
  add_uncert(ac, errn);
}

template<typename T, template<typename> class ET, 
	 template<typename, template<typename> class> class AC>
void AF0<T, ET, AC>::new_form(AC<T, ET> *ac, base_ref_t uncert) 
{
  add_uncert(ac, uncert);
}

template<typename T, template<typename> class ET, 
	 template<typename, template<typename> class> class AC>
void AF0<T, ET, AC>::add_uncert(AC<T, ET> *ac, base_ref_t uncert)
{ 
  if(uncert != b_traits_t::my_zero()) 
    ac->insert(typename AC<T,ET>::error_t(uncert));
}


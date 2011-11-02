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


namespace yalaa 
{
  namespace details {
    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC>
    template<bool ADD, bool CENTRAL>
    unsigned AffineCombOpImpl<T, ET, AC>::add_ac_ac_gen(ac_t* ac1, const ac_t &ac2)
    {
      unsigned ops = 0;
      if(CENTRAL) {
	ac1->set_central(ac1->central() + (ADD ? ac2.central() : -ac2.central()));
	ops++;
      }
      
      typename ac_t::aff_comb_const_iter it2(ac2.begin());
      typename ac_t::aff_comb_iter it(ac1->begin());
      while(it != ac1->end() && it2 != ac2.end()) {
	if(*it < *it2)
	  ++it;
	else if(*it2 < *it) {
	  it = ac1->insert(*it2, it);
	  ++it2;
	}
	else if(*it == *it2) {
	  // std::cout << "special: " << it->special() << std::endl;
	  // std::cout << it->dev() << std::endl;
	  it->set_dev(it->dev( ) + ((ADD || it->special()) ? it2->dev() : -it2->dev()));
	  //std::cout << it->dev() << std::endl;
	  ++it; ++it2; ++ops;
	}
      }
      while(it2 != ac2.end())
	ac1->push_back(*it2++);
      //std::copy(it2, ac2.end(), std::back_inserter(*ac1));
      return ops;
    }
    

    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC>
    unsigned AffineCombOpImpl<T, ET, AC>::add_ac_ac(ac_t* ac1, const ac_t &ac2)
    {
      return add_ac_ac_gen<true, true>(ac1, ac2);
    }

    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC>
    unsigned AffineCombOpImpl<T, ET, AC>::sub_ac_ac(ac_t* ac1, const ac_t &ac2)
    {
      return add_ac_ac_gen<false, true>(ac1, ac2);
    }

    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC>
    unsigned AffineCombOpImpl<T, ET, AC>::add_ac_ac_noc(ac_t* ac1, const ac_t &ac2)
    {
      return add_ac_ac_gen<true, false>(ac1, ac2);
    }

    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC>
    unsigned AffineCombOpImpl<T, ET, AC>::sub_ac_ac_noc(ac_t* ac1, const ac_t &ac2)
    {
      return add_ac_ac_gen<false, false>(ac1, ac2);
    }


    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC>
    unsigned AffineCombOpImpl<T, ET, AC>::mul_ac_s(ac_t* ac, typename ac_t::base_ref_t sc, typename ac_t::base_ref_t sn)
    {
      //std::cout << sc << " " << sn << std::endl;
      ac->set_central(sc*ac->central());
      for(typename ac_t::aff_comb_iter it(ac->begin()); it != ac->end();++it)
	it->set_dev((it->special() ? fabs(sn) : sn) *it->dev());
      return ac->size()+1;
    }
    
    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC>
    unsigned AffineCombOpImpl<T, ET, AC>::add_ac_s(ac_t *ac, typename ac_t::base_ref_t s)
    {
      ac->set_central(ac->central()+s);
      return 1;
    }

    template<typename T, template<typename> class ET,
	     template<typename, template<typename> class> class AC>
    unsigned AffineCombOpImpl<T, ET, AC>::neg_ac(ac_t *ac)
    {
      ac->set_central(-ac->central());
      for(typename ac_t::aff_comb_iter it(ac->begin()); it != ac->end();++it)
	if(!it->special())
	  it->set_dev(-it->dev());
      return ac->size()+1;
      }
  }
}

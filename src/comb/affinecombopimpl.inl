// -*-c++-*-
namespace yalaa 
{
  namespace details {
template<class AC, bool ADD, bool CENTRAL>
unsigned add_ac_ac(AC* ac1, const AC &ac2)
{
  unsigned ops = 0;
  if(CENTRAL) {
    ac1->set_central(ac1->central() + (ADD ? ac2.central() : -ac2.central()));
    ops++;
  }

  typename AC::aff_comb_const_iter it2(ac2.begin());
  typename AC::aff_comb_iter it(ac1->begin());
  while(it != ac1->end() && it2 != ac2.end()) {
    if(*it < *it2)
      ++it;
    else if(*it2 < *it)
      it = ac1->insert(*it2, it);
    else if(*it == *it2) {
      it->set_dev(it->dev( )+ (ADD ? it2->dev() : -it2->dev()));
      ++it; ++it2; ++ops;
    }
  }
  while(it2 != ac2.end())
    ac1->push_back(*it2++);
    //std::copy(it2, ac2.end(), std::back_inserter(*ac1));
  return ops;
}

template<class AC, bool CENTRAL>
unsigned add_ac_ac(AC* ac1, const AC &ac2)
{
  return add_ac_ac<AC, true, CENTRAL>(ac1, ac2);
}

template<class AC, bool CENTRAL>
unsigned sub_ac_ac(AC* ac1, const AC &ac2)
{
  return add_ac_ac<AC, false, CENTRAL>(ac1, ac2);
}

template<class AC>
unsigned add_ac_ac(AC* ac1, const AC &ac2)
{
  return add_ac_ac<AC, true, true>(ac1, ac2);
}

template<class AC>
unsigned sub_ac_ac(AC* ac1, const AC &ac2)
{
  return add_ac_ac<AC, false, true>(ac1, ac2);
}


template<class AC>
unsigned mul_ac_s(AC* ac, typename AC::base_ref_t sc, typename AC::base_ref_t sn)
{
  //std::cout << sc << " " << sn << std::endl;
  ac->set_central(sc*ac->central());
  for(typename AC::aff_comb_iter it(ac->begin()); it != ac->end();++it)
    it->set_dev(sn*it->dev());
  return ac->size()+1;
}

template<class AC>
unsigned add_ac_s(AC *ac, typename AC::base_ref_t s)
{
  ac->set_central(ac->central()+s);
  return 1;
}

template<class AC>
unsigned neg_ac(AC *ac)
{
  ac->set_central(-ac->central());
  for(typename AC::aff_comb_iter it(ac->begin()); it != ac->end();++it)
    it->set_dev(-it->dev());
  return ac->size()+1;
}
}}

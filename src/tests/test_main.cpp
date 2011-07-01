#include <gtest/gtest.h>

#include <deque>
#include <boost/foreach.hpp>

// yalaa
#include "yalaa.hpp"

// Funktionsmeta
#include "ftmeta.hpp"

namespace yalaa 
{
  namespace tests 
  {
    yalaa::details::double_iv_t intersect(const yalaa::details::double_iv_t &iv1, 
					  const yalaa::details::double_iv_t &iv2)
    {
#ifdef HAVE_CXSC
      return iv1 & iv2;
#elif HAVE_FILIB
      return iv1.intersect(iv2);
#endif
    }

    class YalaaFunctionTest : public ::testing::TestWithParam<FTMeta> 
    {
    public:
      typedef double base_t;
      typedef yalaa::details::double_iv_t iv_t;
      typedef iv_t (*iv_f_t)(const iv_t&);
      typedef yalaa::details::base_traits<iv_t> iv_traits;

    protected:
      void SetUp() 
	{
	  m_meta = GetParam();
	  iv_t d(m_meta.d);
	  if(m_meta.dt & LEFTOPEN)
	    //d = iv_t(nextafter(iv_traits::my_inf(d),iv_traits::my_sup(d)) , iv_traits::my_sup(d));
	    d = iv_t(iv_traits::my_inf(d) + S_OPEN_EPS , iv_traits::my_sup(d));
	  if(m_meta.dt & RIGHTOPEN)
//	    d = iv_t(iv_traits::my_inf(d), nextafter(iv_traits::my_sup(d), iv_traits::my_inf(d)));
	    d = iv_t(iv_traits::my_inf(d), iv_traits::my_sup(d) - S_OPEN_EPS);
	  m_x.push_back(d);
	}

    protected:
      std::deque<iv_t> m_x;
      FTMeta m_meta;
      
      // max. Unterteilung
      static const base_t S_EPS = 10e-4;
      static const base_t S_OPEN_EPS = 10e-10;
    };

    TEST_P(YalaaFunctionTest, DomainTest) 
    {
      while(!m_x.empty()) {
	iv_t x(m_x.front());
	iv_t fiv((*m_meta.ivf)(x));
	aff_e_d faff((*m_meta.afff)(aff_e_d(x)));
	iv_t faffiv (to_iv(faff));
	iv_t isect(intersect(faffiv, fiv));
	ASSERT_LE(iv_traits::my_inf(isect), iv_traits::my_sup(isect)) 
	  << "Interval and affine evaluation do not intersect!" << std::endl
	  << "Input was " << x << " fiv: " << fiv << " faff " << faff << std::endl;
        // ASSERT_LE(iv_traits::my_inf(faffiv), iv_traits::my_inf(fiv))
	//    << "Affine evaluation was tigher than IV for a single elementary function."
	//    << "Input was " << x << " fiv: " << fiv << " faff " << faff << std::endl;
	// ASSERT_GE(iv_traits::my_sup(faffiv), iv_traits::my_sup(fiv))
	//   << "Affine evaluation was tigher than IV for a single elementary function."
	//   << "Input was " << x << " fiv: " << fiv << " faff " << faff << std::endl;
	if(iv_traits::my_sup(x) - iv_traits::my_inf(x) > S_EPS) {
	  base_t mid = (iv_traits::my_inf(x) + iv_traits::my_sup(x))/2;
	  m_x.push_back(iv_t(iv_traits::my_inf(x), mid));
	  m_x.push_back(iv_t(mid, iv_traits::my_sup(x)));
	}
	m_x.pop_front();
      }
    }

    TEST(POWN, HandlesZeroExp) 
    {
      using namespace yalaa::details;
      double_iv_t x1(-200, -200);
      double_iv_t x2(0, 0);
      double_iv_t x3(1, 1);
      double_iv_t x4(1899, 239239);
      ASSERT_EQ(to_iv(pown(aff_e_d(x1),0)), double_iv_t(1.0));
      ASSERT_EQ(to_iv(pown(aff_e_d(x2),0)), double_iv_t(1.0));
      ASSERT_EQ(to_iv(pown(aff_e_d(x3),0)), double_iv_t(1.0));
      ASSERT_EQ(to_iv(pown(aff_e_d(x4),0)), double_iv_t(1.0));
    }

    TEST(POWN, HandlesOneExp) 
    {
      using namespace yalaa::details;
      double_iv_t x1(-200, -150);
      double_iv_t x2(0, 1);
      double_iv_t x3(-2, 3);
      double_iv_t x4(1899, 239239);
      ASSERT_EQ(to_iv(pown(aff_e_d(x1),1)), x1);

      ASSERT_EQ(to_iv(pown(aff_e_d(x2),1)), x2);
      ASSERT_EQ(to_iv(pown(aff_e_d(x3),1)), x3);
      ASSERT_EQ(to_iv(pown(aff_e_d(x4),1)), x4);
    }

    TEST(POWN, HandlesEvenExp) 
    {
      using namespace yalaa::details;
      std::vector<double_iv_t> bs = { double_iv_t(-200, -150), double_iv_t(0, 1), double_iv_t(-2, 3),
				     double_iv_t(1899, 239239) };
      std::vector<int> es = {-10, -2, -4, -6, -10, 2, 4, 6, 8, 10 };

      BOOST_FOREACH(double_iv_t b, bs) {
	BOOST_FOREACH(int e, es) {
	  double_iv_t fiv(base_traits<double_iv_t>::my_pow(b, e));
	  aff_e_d faff(pown(aff_e_d(b), e));
	  double_iv_t faffiv (to_iv(faff));
	  double_iv_t isect(intersect(faffiv, fiv));
	  ASSERT_LE(base_traits<double_iv_t>::my_inf(isect), base_traits<double_iv_t>::my_sup(isect))
	    << "Interval and affine evaluation do not intersect!" << std::endl
	    << "Input was " << b << "^" << e << " fiv: " << fiv << " faff " << faff << std::endl;
	}
      }

      // iv_t faffiv (to_iv(faff));
      // iv_t isect(intersect(faffiv, fiv));

      // ASSERT_EQ(to_iv(pown(aff_e_d(x1),2)), pow(x1, 4));
      // ASSERT_EQ(to_iv(pown(aff_e_d(x2),4)), x2);
      // ASSERT_EQ(to_iv(pown(aff_e_d(x3),6)), x3);
      // ASSERT_EQ(to_iv(pown(aff_e_d(x4),8)), x4);
    }

    //INSTANTIATE_TEST_CASE_P(AutoDomainTest, YalaaFunctionTest,::testing::ValuesIn(FTMeta::get()));
  }
}


int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

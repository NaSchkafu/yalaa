#include <gtest/gtest.h>

#include <deque>

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
	  m_x.push_back(m_meta.d);
	}

    protected:
      std::deque<iv_t> m_x;
      FTMeta m_meta;

      static const base_t S_EPS = 0.0001;
    };

    TEST_P(YalaaFunctionTest, DomainTest) 
    {
      while(!m_x.empty()) {
	iv_t x(m_x.front());
	iv_t fiv((*m_meta.ivf)(x));
	aff_e_d faff((*m_meta.afff)(aff_e_d(x)));
	iv_t faffiv (to_iv(faff));
	iv_t isect(intersect(faffiv, fiv));
	ASSERT_GE(iv_traits::my_inf(isect), iv_traits::my_sup(isect)) 
	  << "Interval and affine evaluation do not intersect!" << std::endl
	  << "Input was " << x << std::endl;
	EXPECT_LE(iv_traits::my_inf(faffiv), iv_traits::my_inf(fiv))
	  << "Affine evaluation was tigher than IV for a single elementary function.";
	EXPECT_GE(iv_traits::my_sup(faffiv), iv_traits::my_sup(fiv))
	  << "Affine evaluation was tigher than IV for a single elementary function.";
	if(iv_traits::my_sup(x) - iv_traits::my_inf(x) > S_EPS) {
	  base_t mid = (iv_traits::my_inf(x) + iv_traits::my_sup(x))/2;
	  m_x.push_back(iv_t(iv_traits::my_inf(x), mid));
	  m_x.push_back(iv_t(mid, iv_traits::my_sup(x)));
	}
	m_x.pop_front();
      }
    }

    INSTANTIATE_TEST_CASE_P(AutoDomainTest, YalaaFunctionTest,::testing::ValuesIn(FTMeta::get()));
    

  }
}


int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

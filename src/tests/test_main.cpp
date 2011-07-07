#include <gtest/gtest.h>

#include <deque>
#include <boost/foreach.hpp>


// yalaa
#include "yalaa.hpp"

//#define AFF_TYPE yalaa::aff_af1_e_d_dec
#define AFF_TYPE yalaa::aff_e_d_dec

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


    class YalaaEleFunctionTest : public ::testing::TestWithParam<FTMeta>
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
	    d = iv_t(iv_traits::my_inf(d) + S_OPEN_EPS , iv_traits::my_sup(d));
	  if(m_meta.dt & RIGHTOPEN)
	    d = iv_t(iv_traits::my_inf(d), iv_traits::my_sup(d) - S_OPEN_EPS);
	  m_x.push_back(d);
	}
      
    protected:
      std::deque<iv_t> m_x;
      FTMeta m_meta;
      static const base_t S_EPS = 10e-4;
      static const base_t S_OPEN_EPS = 10e-10;
    };
    

    // Range Test
    TEST_P(YalaaEleFunctionTest, RangeTest)
    {
      while(!m_x.empty()) {
        iv_t x(m_x.front());
        iv_t fiv((*m_meta.ivf)(x));
        AFF_TYPE faff((*m_meta.afff)(AFF_TYPE(x)));
        iv_t faffiv (to_iv(faff));
        ASSERT_TRUE(iv_traits::my_inf(faffiv) <= iv_traits::my_sup(fiv) &&
                    iv_traits::my_sup(faffiv) >= iv_traits::my_inf(fiv))
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

    // Range Test fuer degenerierte Formen ohne Abhängigkeiten
    TEST_P(YalaaEleFunctionTest , RangeTestPoin)
    {
      while(!m_x.empty()) {
        iv_t x(mid(m_x.front()));
        iv_t fiv((*m_meta.ivf)(x));
        AFF_TYPE faff((*m_meta.afff)(AFF_TYPE(x)));
        iv_t faffiv (to_iv(faff));
        ASSERT_TRUE(iv_traits::my_inf(faffiv) <= iv_traits::my_sup(fiv) &&
                    iv_traits::my_sup(faffiv) >= iv_traits::my_inf(fiv))
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

    // Pown Range Test
    TEST(POWN, RangeTest)
    {
      typedef yalaa::details::double_iv_t iv_t;
      typedef yalaa::details::base_traits<iv_t> iv_traits;
      typedef double base_t;
      std::deque<iv_t> m_x;
      for(int exp = -10; exp <= 10; exp++) {
        m_x.clear();
        if(exp < 0)
          m_x.push_back(iv_t(0.1, 10));
        else
          m_x.push_back(iv_t(-10, 10));
        while(!m_x.empty()) {
          iv_t x(m_x.front());
          iv_t fiv(iv_traits::my_pow(x, exp));
          AFF_TYPE aarg(x);
          AFF_TYPE faff(pown(aarg, exp));
          iv_t faffiv (to_iv(faff));
          iv_t isect(intersect(faffiv, fiv));
          if(!exp)
            ASSERT_EQ(faffiv, iv_traits::my_one())
              << "pown(x,0) does not yield iv_traits::my_one()"
              << "Input was " << x << "^" << exp << " fiv: " << fiv << " faff " << faff << std::endl;
          else if(exp == 1)
            ASSERT_EQ(faff, aarg)
              << "pown(x,1) does not preserve identity of x!"
              << "Input was " << x << "^" << exp << " fiv: " << fiv << " faff " << faff << std::endl;
          ASSERT_LE(iv_traits::my_inf(isect), iv_traits::my_sup(isect))
            << "Interval and affine evaluation do not intersect!" << std::endl
            << "Input was " << x << "^" << exp << " fiv: " << fiv << " faff " << faff << std::endl;
          // ASSERT_LE(iv_traits::my_inf(faffiv), iv_traits::my_inf(fiv))
          //    << "Affine evaluation was tigher than IV for a single elementary function."
          //    << "Input was " << x << " fiv: " << fiv << " faff " << faff << std::endl;
          // ASSERT_GE(iv_traits::my_sup(faffiv), iv_traits::my_sup(fiv))
          //   << "Affine evaluation was tigher than IV for a single elementary function."
          //   << "Input was " << x << " fiv: " << fiv << " faff " << faff << std::endl;
          if(iv_traits::my_sup(x) - iv_traits::my_inf(x) > 0.0001) {
            base_t mid = (iv_traits::my_inf(x) + iv_traits::my_sup(x))/2;
            m_x.push_back(iv_t(iv_traits::my_inf(x), mid));
            m_x.push_back(iv_t(mid, iv_traits::my_sup(x)));
          }
          m_x.pop_front();
        }
      }
    }

    INSTANTIATE_TEST_CASE_P(AutoRangeTest, YalaaEleFunctionTest,::testing::ValuesIn(FTMeta::get()));

    // iv_t faffiv (to_iv(faff));
    // iv_t isect(intersect(faffiv, fiv));

    // ASSERT_EQ(to_iv(pown(AFF_TYPE(x1),2)), pow(x1, 4));
    // ASSERT_EQ(to_iv(pown(AFF_TYPE(x2),4)), x2);
    // ASSERT_EQ(to_iv(pown(AFF_TYPE(x3),6)), x3);
    // ASSERT_EQ(to_iv(pown(AFF_TYPE(x4),8)), x4);
  }
}



int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

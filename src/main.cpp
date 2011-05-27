#include <iostream>
#include <stdlib.h>

#include "yalaa.hpp"


int n = 0;
int it = 0;

typedef yalaa::aff_e_d aff;
typedef yalaa::details::base_traits<yalaa::details::double_iv_t> iv_traits;

yalaa::details::double_iv_t intersect(const yalaa::details::double_iv_t &iv1, const yalaa::details::double_iv_t &iv2) 
{
#ifdef HAVE_CXSC
  return iv1 & iv2;
#elif HAVE_FILIB
  return iv1.intersect(iv2);
#endif
}

void test(const yalaa::details::double_iv_t &iv, const aff &af, const yalaa::details::double_iv_t &input) 
{
  using namespace yalaa::details;
  double_iv_t ieaff(to_iv(af));
  double_iv_t isect(intersect(ieaff,iv));
  if(base_traits<double_iv_t>::my_inf(isect) > base_traits<double_iv_t>::my_sup(isect)) {
    std::cout << "FEHLER!" << std::endl;
    std::cout << "Eingabe: " << input << std::endl;
    std::cout << "AF: " << af << std::endl;
    std::cout << "IV: " << iv << std::endl;
    exit(-1);
  }
  if(base_traits<double_iv_t>::my_sup(ieaff) - base_traits<double_iv_t>::my_inf(ieaff) < base_traits<double_iv_t>::my_sup(iv) - base_traits<double_iv_t>::my_inf(iv))
    n++;
  it++;
  std::cout << input << std::endl;
  std::cout << af << std::endl;
  std::cout << "w: " << base_traits<double_iv_t>::my_sup(input) - base_traits<double_iv_t>::my_inf(input)  << " AFF: " << base_traits<double_iv_t>::my_sup(ieaff) - base_traits<double_iv_t>::my_inf(ieaff) << " IV: " << 
    base_traits<double_iv_t>::my_sup(iv) - base_traits<double_iv_t>::my_inf(iv) << std::endl;
}

void test_exp(const yalaa::details::double_iv_t &i)
{
  using namespace yalaa::details;
  yalaa::details::double_iv_t eiv(exp(i));
  aff eaff(exp(aff(i)));
  test(eiv, eaff, i);
}

void test_sqrt(const yalaa::details::double_iv_t &i) 
{
  using namespace yalaa::details;
  double_iv_t eiv(sqrt(i));
  aff eaff(sqrt(aff(i)));
  test(eiv, eaff, i);
}

void test_sqr(const yalaa::details::double_iv_t &i) 
{
  using namespace yalaa::details;
  double_iv_t eiv(sqr(i));
  aff eaff(sqr(aff(i)));
  test(eiv, eaff, i);
}

void test_pow(const yalaa::details::double_iv_t &i) 
{
  using namespace yalaa::details;
  int n = rand() % 10;
  double_iv_t eiv(power(i, n));
  aff eaff(pow(aff(i), n));
  test(eiv, eaff, i);
}

void test_ln(const yalaa::details::double_iv_t &i) 
{
  using namespace yalaa::details;
  double_iv_t eiv(iv_traits::my_ln(i));
  aff eaff(ln(aff(i)));
  test(eiv, eaff, i);
}

void test_sin(const yalaa::details::double_iv_t &i) 
{
  using namespace yalaa::details;
  double_iv_t eiv(sin(i));
  aff eaff(sin(aff(i)));
  test(eiv, eaff, i);
}

void test_cos(const yalaa::details::double_iv_t &i) 
{
  using namespace yalaa::details;
  double_iv_t eiv(cos(i));
  aff eaff(cos(aff(i)));
  test(eiv, eaff, i);
}

void test_mul(const yalaa::details::double_iv_t &i)
{
  using namespace yalaa::details;
  double_iv_t eiv(i*i);
  aff eaff(aff(i)*aff(i));
  test(eiv, eaff, i);
}

void rec_split(const yalaa::details::double_iv_t &i, double eps, void (*f)(const yalaa::details::double_iv_t&))
{
  using namespace yalaa::details;
  double w = base_traits<double_iv_t>::my_sup(i) - base_traits<double_iv_t>::my_inf(i);
  if(w < eps)
    return;
  f(i);
  double_iv_t i1(base_traits<double_iv_t>::my_inf(i), base_traits<double_iv_t>::my_inf(i) + w/2);
  double_iv_t i2(base_traits<double_iv_t>::my_sup(i) - w/2, base_traits<double_iv_t>::my_sup(i));
  rec_split(i1, eps, f);
  rec_split(i2, eps, f);
}

//#endif

#include <stdio.h>
#include <float.h>

// #ifdef GREATER
// #define MULTIPLIER (0.5 + FLT_EPSILON)
// #else
// #define MULTIPLIER 0.5
// #endif

int main(int argc, char *argv[])
{
#ifdef HAVE_FILIB
  filib::fp_traits<double>::setup();
#endif
  //filib::fp_traits<float>::setup();
  // std::cout << sin(-97.412110) << std::endl;
  // std::cout << sin(-3.16433) << std::endl;
  // return 0;
  

  // yalaa::fp::RndControl rnd;
  // rnd.upward();
  // double xx = 1.0;
  // unsigned int count = 0;
  // while (xx > 0.0f && count < 6000)
  // {
  //   xx *= 0.5;
  //   printf("%g %a\n", xx, xx);
  //   count++;
  // }
  // return 0;



  
  // aff x(double_iv_t(1,3));
  // aff y(double_iv_t(-1,-3));

  // aff ex(exp(x));

  // std::cout << x << std::endl;
  // std::cout << y << std::endl;
  // x += y;
  // std::cout << x << std::endl;
  // std::cout << ex << std::endl;

  // using namespace yalaa::details;
  // double_iv_t x(0.0);
  // aff ax(x);
  // //cout << sin(ax)  << " " << sin(x) << endl;

  // //double_iv_t sx(-77.378846,-77.377319);
  // double_iv_t sx(-20.2, -20.1);
  // aff asx(sx);
  // std::cout << "asx " << asx << std::endl;
  // std::cout << "sin sx " << sin(sx) << std::endl;
  // std::cout << "sin asx " << sin(asx) << std::endl;
  // std::cout << base_traits<double_iv_t>::my_w(sin(sx)) <<"   " << base_traits<double_iv_t>::my_w(to_iv(sin(asx))) << std::endl;
  // double_iv_t ssx(-100,100);
  // rec_split(ssx, 0.0001, &test_cos);


  // aff x(double_iv_t(1.9,2));
  // aff y(0.0);
  // // y = pow(x, 0);
  // // std::cout << y << std::endl;
  // // y = pow(x, 1);
  // // std::cout << y << std::endl;
  // y = sin(x);
  // y = ln(x);
  // std::cout << y << std::endl;
  // // y = pow(x, 3);
  // // std::cout << y << std::endl;
  // // y = pow(x, 4);
  // // std::cout << y << std::endl;

  // std::cout << ln(double_iv_t(1.9, 2)) << std::endl;

//  aff y(double_iv_t(10,10));
  // x = sqr(x);
  // cout << x << endl;
  // y = sqr(y);
  // x -= y;
  // x = sqr(x);
  // cout << y << endl;
  // cout << x << endl;
  // x += y;
  
  // aff x(double_iv_t(1,3));
  // std::cout << x << std::endl;
  // x = sqrt(x);
  // std::cout << x << std::endl;
  // aff y(x);
  // std::cout << "y: " << y << std::endl;
  // x -= x;
  // std::cout << x << std::endl;
  // x = y;
  // std::cout << x << std::endl;
  // x -= y;
  // std::cout << x << std::endl;
  // x = y;
  // std::cout << x << std::endl;
  // x += x;
  // std::cout << x << std::endl;
  // x += y;
  // std::cout << x << std::endl;
  // x -= x;
  // std::cout << x << std::endl;
  // std::cout << "y: " << y << std::endl;
  // x -= y;
  // std::cout << x << std::endl;
  // std::cout << "it: " << it << " n: " << n << std::endl;
  // return 0;
}


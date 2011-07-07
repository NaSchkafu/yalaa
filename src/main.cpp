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

void test2(const yalaa::details::double_iv_t &iv, const aff &af, const yalaa::details::double_iv_t &input)
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
  if(iv_traits::my_w(ieaff) < iv_traits::my_w(iv)) {
    n++;
    std::cout << "INP: " << input << std::endl;
    // std::cout << af << std::endl;
    // std::cout << "w: " << base_traits<double_iv_t>::my_sup(input) - base_traits<double_iv_t>::my_inf(input)  << " AFF: " << base_traits<double_iv_t>::my_sup(ieaff) - base_traits<double_iv_t>::my_inf(ieaff) << " IV: " <<
    //   base_traits<double_iv_t>::my_sup(iv) - base_traits<double_iv_t>::my_inf(iv) << std::endl;
    std::cout << "AFF: "<< to_iv(af) << std::endl;
    std::cout << "IV:  "<<iv << std::endl;
    std::cout << "AFF: " << af << std::endl;
    exit(-1);
  }

  std::cout << iv_traits::my_w(input) - iv_traits::my_w(ieaff) << std::endl;

  it++;

}

void test_exp(const yalaa::details::double_iv_t &i)
{
  using namespace yalaa::details;
  yalaa::details::double_iv_t eiv(exp(i));
  aff eaff(exp(aff(i)));
  test2(eiv, eaff, i);
}

void test_sqrt(const yalaa::details::double_iv_t &i)
{
  using namespace yalaa::details;
  double_iv_t eiv(sqrt(i));
  aff eaff(sqrt(aff(i)));
  test2(eiv, eaff, i);
}

void test_sqr(const yalaa::details::double_iv_t &i)
{
  using namespace yalaa::details;
  double_iv_t eiv(sqr(i));
  aff eaff(sqr(aff(i)));
  test2(eiv, eaff, i);
}

void test_pow(const yalaa::details::double_iv_t &i)
{
  using namespace yalaa::details;
  int n = rand() % 10;
  double_iv_t eiv(power(i, n));
  aff eaff(pown(aff(i), n));
  test2(eiv, eaff, i);
}

void test_ln(const yalaa::details::double_iv_t &i)
{
  using namespace yalaa::details;
  double_iv_t eiv(iv_traits::my_log(i));
  aff eaff(log(aff(i)));
  test2(eiv, eaff, i);
}

void test_sin(const yalaa::details::double_iv_t &i)
{
  using namespace yalaa::details;
  double_iv_t eiv(sin(i));
  aff eaff(sin(aff(i)));
  test2(eiv, eaff, i);
}

void test_cos(const yalaa::details::double_iv_t &i)
{
  using namespace yalaa::details;
  double_iv_t eiv(cos(i));
  aff eaff(cos(aff(i)));
  test2(eiv, eaff, i);
}

void test_mul(const yalaa::details::double_iv_t &i)
{
  using namespace yalaa::details;
  double_iv_t eiv(i*i);
  aff eaff(aff(i)*aff(i));
  test2(eiv, eaff, i);
}

void test_asin(const yalaa::details::double_iv_t &i)
{
  using namespace yalaa::details;
  double_iv_t eiv(asin(i));
  aff eaff(asin(aff(i)));
  test2(eiv, eaff, i);
}

void test_acos(const yalaa::details::double_iv_t &i)
{
  using namespace yalaa::details;
  double_iv_t eiv(acos(i));
  aff eaff(acos(aff(i)));
  test2(eiv, eaff, i);
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

#include "helper/fastia.hpp"

void test(const yalaa::details::double_iv_t &d)
{
  using namespace yalaa::details;
  typedef double_iv_t iv_t;
  typedef base_traits<double_iv_t> iv_traits;
  typedef double T;
  
  // TODO: thread safe
  static const iv_t S_X[2][2] = {
    { iv_traits::my_div(iv_t(1.0),iv_traits::my_sqrt(iv_t(2.0))), iv_traits::my_div(iv_t(-1.0),iv_traits::my_sqrt(iv_t(2.0)))},
    { iv_traits::my_div(iv_traits::my_sqrt(iv_t(3)),iv_t(2.0)), iv_t(0.0) }
  };
  static const T S_HALF(0.5);
  static const T S_RMND1(192);
  static const T S_RMND2(16);

  using namespace yalaa::fp;

  unsigned short order = 0;
  
  // TODO: cleanup, nur eine Modi Änderung
  T a = iv_traits::my_inf(d);
  T b = iv_traits::my_sup(d);

  // 1 Wechsel + 3 IV Mult + 2 IV Auswertungen von f
  //rnd.upward();
  iv_t ibsia(fast_sub_dd_up<T, iv_t>(b,a));
  iv_t iapib(fast_add_dd_up<T, iv_t>(a,b));
  iv_t x0(S_HALF*fast_add_ii_up(iv_traits::my_mul(ibsia,S_X[order][0]), iapib));
  iv_t x1(S_HALF*fast_add_ii_up(iv_traits::my_mul(ibsia,S_X[order][1]), iapib));
  iv_t fx0(iv_traits::my_sinh(x0));
  iv_t fx1(iv_traits::my_sinh(x1));
  std::cout << "fx0 " << fx0 << std::endl;
  std::cout << "fx1 " << fx1 << std::endl;
  iv_t c0(fast_add_ii_up<iv_t>(fx0, fx1));
  iv_t c1(fast_add_ii_up<iv_t>(iv_traits::my_mul(fx0,S_X[order][0]), iv_traits::my_mul(fx1,S_X[order][1])));
  c0 *= S_HALF;
  T w(iv_traits::my_w(d));

  T err = 0.0;
  iv_t c12(iv_traits::my_inf(c1)*2, iv_traits::my_sup(c1)*2);
  c12 /=ibsia;
  std::cout << "Lineare Funktion: " << mid(c0 - iapib*c1/ibsia) << "+" << mid(c12)<<"*x" << std::endl;
  std::cout << "w: " << w << " c0: " << c0 << " c12: " << c12 << "c1 " << c1 << std::endl;



  iv_t remainder((order ? w*w : w)*(-iv_traits::my_cos(d))/(order ? S_RMND1 : S_RMND2));
  iv_t bound(c0 + c1*double_iv_t(-1,1));
  std::cout << "Bound P(x): " << bound << " w (+Rem): " << iv_traits::my_w(bound+remainder) << std::endl;
  //std::cout << "sin(d): " << iv_traits::my_sin(d) << " w: " << iv_traits::my_w(iv_traits::my_sin(d)) << std::endl;
  

  // if(w <= 1.0)
  //   err = aff_op_t::scale_add(ac, 0.0, 0.0,
  //                             iv_traits::my_inf(c1), iv_traits::my_sup(c1),
  //                             iv_traits::my_inf(c0), iv_traits::my_sup(c0), rnd);
  // else {
  //   iv_t c12(iv_traits::my_inf(c1)*2, iv_traits::my_sup(c1)*2);
  //   c12 = fast_div_id_up(fast_sub_ii_up(c12, iapib), w);
  //   err = aff_op_t::scale_add(ac, 0.0, 0.0, iv_traits::my_inf(c12), iv_traits::my_sup(c12),
  //                             iv_traits::my_inf(c0), iv_traits::my_sup(c0), rnd);
  // }

  // w *= w;
  // iv_t remainder((order ? w*w : w)*(*ddf)(d)/(order ? S_RMND1 : S_RMND2));
  // err += iv_traits::my_w(remainder);
  // err *= 0.5;
  // return aerror_t(err, yalaa::fp::get_flags(err));
}

void ltest(int (*f)(int, int))
{
  
}

int main(int argc, char *argv[])
{
  // sqr(1-sqrt(sqr(x0)+sqr(x1)))+pow(sin(x2),3)-0.125

  using namespace yalaa;
  yalaa::details::double_iv_t ssx1(-10,0);
  aff_e_d_dec x0(ssx1);
  aff_e_d_dec x1(ssx1);
  aff_e_d_dec x2(ssx1);
  aff_e_d_dec erg(sqr(x0));//+pown(sin(x2),3));
  std::cout << erg << std::endl;
  1.0-erg-1.0;
  
  //return sqr(1-sqrt(sqr(x0)+sqr(x1)))+pow(sin(x2),3)-0.125;
  // std::cout << acosh(a) << std::endl;
  // std::cout << iv_traits::my_acosh(ssx1) << std::endl;
  // aff_e_d a(ssx1);
  // std::cout << sinh(a) << std::endl;
  // test(ssx1);
  // std::cout << iv_traits::my_sinh(ssx1) << std::endl;
  return 0;

  ltest([](int x, int y)->int{ return x + y; });
  

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
  using namespace yalaa::details;
  // test(double_iv_t(0.4, 0.5));
  // test(double_iv_t(0.49, 0.5));
  // test(double_iv_t(0.499, 0.5));
  // test(double_iv_t(0.4999, 0.5));
  // test(double_iv_t(0.49999, 0.5));



  yalaa::details::double_iv_t ssx(-1.0, 1.0);
  rec_split(ssx, 0.000001, &test_asin);


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
  std::cout << "it: " << it << " n: " << n << std::endl;
  return 0;
}


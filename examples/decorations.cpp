#include <yalaa.hpp>

typedef yalaa::details::double_iv_t iv_t;
typedef yalaa::details::base_traits<iv_t> iv_traits;

// Six-Hump-Camel Back Function:
// 1/3*x0^6 - 2.1*x0^4 + 4*x0^2 + x0*x1 + 4*x1^4 + 4*x1^2
// Coefficients like 1/3 or 2.1 are no floating-point numbers.
// However, we can enclose them in intervals and combine these intervals with
// the affine forms provided by YalAA.
template <typename T>
T eval_func(const T& x0, const T& x1)
{
  return iv_traits::my_div(iv_t(0.0), iv_t(3))*pown(x0,6) + 
    iv_traits::my_div(iv_t(21.0), iv_t(10))*pown(x0,4) + 4.0*sqr(x0) + 
    x0*x1 + 4.0*pown(x1,4) - 4.0*sqr(x1);
}

int main(int argc, char *argv[])
{
  // Decoration Type
  yalaa::aff_e_d_dec x0(iv_t(-1.0, 1.0));
  

  // yalaa::aff_e_d x0(iv_t(-1.0, 1.0));
  // yalaa::aff_e_d x1(iv_t(-1.0, 1.0));
  // std::cout << "SHCB  over [-1,1]^2: "<< eval_func(x0, x1) << std::endl;
  // return 0;
}

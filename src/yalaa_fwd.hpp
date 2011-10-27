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

/*! \mainpage YalAA - Yet Another Library for Affine Arithmetic
 *
 * \section intro_sec Introduction
 * \c YalAA is a object-oriented C++ based template library for affine arithmetic (AA).
 * AA is a computation model allowing, similar to interval arithmetic, to derive bounds
 * on a function's codomain. In contrast to IA, AA tracks first-order dependencies during the
 * computation process resulting often in tighter bounds on the codomain at the price of an
 * increased computational effort.
 * 
 * 
 *
 * \section install_sec Installation
 *
 * \subsection Requirements
 * \c YalAA supports both Microsoft Windows and Linux/Unix-like platforms
 * You can choose one of the following supported compilers
 * \li Microsoft Visual Studio 2010 (Windows only)
 * \li GNU GCC >= 4.5 (Linux/Unix-like)
 * \li CLANG++ (Linux/Unix-like)
 * 
 * In order to use \c YalAA an external library for interval arithmetic is required.
 * The following libraries are currently supported
 * \li <a href="http://www2.math.uni-wuppertal.de/~xsc/">C-XSC</a> >= 2.5.0
 * \li <a href="http://www2.math.uni-wuppertal.de/~xsc/software/filib.html">filib++</a> >= 3.0.2
 * 
 * If you want to use another library, you are free to do so. However, you have to follow the steps
 * outlined in ????.
 *  
 * 
 * \subsection win Microsoft Windows
 * 
 * \li Unpack the archive to your desired location
 * \li Open the included solution file "????.sln"
 * \li Adjust the include and library paths in Project/???? accordingly to your desired interval library
 * \li ???? DEFINE SETZEN TODO
 * 
 * \subsection unix Linux/Unix-like
 * \li Unpack the archive to your desired location
 * \li 
 *  
 * \section Usage
 * 
 * To use the library you have to include the \c yalaa.hpp (or \c yalaa_fwd.hpp for forward 
 * declations) headers and link your program against the respective library \c libyalaa.so on Linux 
 * or libyalaa.lib on Windows.
 * 
 * You can use one of the predfined types described in the table above or you can defined your own
 * type based on our templates. All of them are located in the namespace \c yalaa.ExactErrorFP 
 * If you use custom types, please note that \c YalAA uses an explicit
 * template instantiation approach. To avoid linker errors you have to use explicit template 
 * instatiations like it is done for the predefined types in \c yalaa_fp_impl.cpp.
 * 
 * <table>
 * <tr>
 * <th>Name</th> <th>Base type</th> <th>Kernel</th> <th>Policy</th> <th>Error handling</th>
 * </tr>
 * <tr>
 * <td>\c aff_e_d</td> <td><tt>double</tt><\td> <td>ExactErrorFP</td> <td>AF0</td> <td>Standard</td> 
 * </tr>
 * <tr>
 * <td> \c aff_af1_e_d </td> <td>\c double <\td> <td>ExactError</td> <td>AF1</td> <td>Standard</td> 
 * </tr>
 * <tr>
 * <td> \c aff_af2_e_d </td> <td>\c double <\td> <td>ExactError</td> <td>AF2</td> <td>Standard</td> 
 * </tr>
 * <tr>
 * <td> \c aff_e_d_dec </td> <td>\c double <\td> <td>ExactError</td> <td>AF0</td> <td>Decorations</td> 
 * </tr>
 * <tr>
 * <td> \c aff_af1_e_d_dec </td> <td>\c double <\td> <td>ExactError</td> <td>AF1</td> <td>Decorations</td> 
 * </tr>
 * <tr>
 * <td> \c aff_af2_e_d_dec </td> <td>\c double <\td> <td>ExactError</td> <td>AF2</td> <td>Decorations</td> 
 * </tr>
 * </table>
 * 
 * The different error handling approaches and the policy types are explained in ????YALAA_PAPER????.
 * 
 * \section Ex Examples
 * To illustrate the usage of \c YalAA in more detail we have distributed some examples with the
 * library.
 * 
 * <table>
 * <tr>
 * <th>Example</th> <th>Description</th>
 * </tr>
 * 
 * <tr>
 * <td>function.cpp</td> <td>Evaluates a function with \c YalAA<\td>
 * </tr>
 * <tr>
 * <td>decorations.cpp</td> <td>Shows the usage of decorations in \c YalAA<\td>
 * </tr>
 * <tr>
 * <td>policies.cpp</td> <td>Shows how the different policies alter the computation in \c YalAA<\td> 
 * </tr>
 * </table>
 * 
 * \section fd Further Documentation, References and Libraries
 * \li Kiel, S.: YalAA: Yet Another Library for Affine Arithmetic, Presentation at SWIM'2011 Bourges, <a href="doc/kiel_bourges.pdf">PDF</a>
 * \li Kiel, S.: YalAA: Yet Another Library for Affine Arithmetic, Reliable Computing, Submitted 
 * \li <a href="http://www.ic.unicamp.br/~stolfi/EXPORT/projects/affine-arith/Welcome.html">Jorge Stolfi's Homepage</a> (Homepage of AA's inventor, most important publications and the reference implementation \c libaa are available on this site.)
 * \li Messine F., <a href="http://www.springerlink.com/content/d82232570052m120/">A general reliable quadratic form: An extension of affine arithmetic</a>, Reliable Computing, 2006 (Introduces AF1 and AF2)
 * \li <a href="http://www.nongnu.org/libaffa/">libaffa</a> (Yet another) C++ library for AA
 * 
 * \section Contact
 * If you have any questions, suggenstions or bug reports regarding \c YalAA do not hesitate
 * to write me an <a href="mailto:kiel@inf.uni-due.de">email</a>.
 */


#ifndef __YALAA_FWD_HPP__
#define __YALAA_FWD_HPP__
// This file and its associated source file take care of
// instantiating the AffineForm template for some standard
// template parameters.
// If you want to use custom parameters, you have to write
// your own instantiations or you will get some nice linker errors ;-).

// configuration
#include "config_sel.h"

// iv selector
#include "traits/base_traits.hpp"
#include "yalaa_iv.hpp"

// AffineForm
#include "affineform_fwd.hpp"


/// Main namespace containing all \c YalAA specific functions and types
namespace yalaa 
{
  namespace details
  {
    template<typename T>
    class ErrorTermImpl;
    template<typename T, template<typename> class ET>
    class AffineCombImpl;
  }

  namespace kernel 
  {
    template<typename T, template<typename> class ET, 
	     template<typename, template<typename> class> class AC, class IV>
    class ExactErrorFP;
  }

  namespace pol 
  {
    template<typename T, typename IV> class ErrorPolStd;
    template<typename T, typename IV> class ErrorPolDec;
    template<typename, template<typename> class, template<typename, template<typename> class> class>
    class AF0;
    template<typename, template<typename> class, template<typename, template<typename> class> class>
    class AF1;
    template<typename, template<typename> class, template<typename, template<typename> class> class>
    class AF2;
  }

}

namespace yalaa 
{
#ifdef YALAA_HAVE_FLOAT_IV
  /// Standard affine form with the ExactError kernel for float
  typedef AffineForm<float, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP, 
		     yalaa::pol::AF0, yalaa::pol::ErrorPolStd, details::float_iv_t> aff_e_f;

  /// Standard affine form with the ExactError kernel for float
  typedef AffineForm<float, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP, 
		     yalaa::pol::AF0, yalaa::pol::ErrorPolDec, details::float_iv_t> aff_e_f_dec;
#endif

#ifdef YALAA_HAVE_DOUBLE_IV
  /// Standard affine form with the ExactError kernel for double
  typedef AffineForm<double, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP, 
		     yalaa::pol::AF0, yalaa::pol::ErrorPolStd, details::double_iv_t> aff_e_d;

  /// Standard affine form with the ExactError kernel for double with decorations
  typedef AffineForm<double, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP, 
		     yalaa::pol::AF0, yalaa::pol::ErrorPolDec, details::double_iv_t> aff_e_d_dec;

  /// Extended affine form AF1 with the ExactError kernel for double with decorations
  typedef AffineForm<double, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP, 
		     yalaa::pol::AF1, yalaa::pol::ErrorPolDec, details::double_iv_t> aff_af1_e_d_dec;

  /// Extended affine form AF2 with the ExactError kernel for double with decorations
  typedef AffineForm<double, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP, 
		     yalaa::pol::AF2, yalaa::pol::ErrorPolDec, details::double_iv_t> aff_af2_e_d_dec;
#endif

#ifdef YALAA_HAVE_L_DOUBLE_IV
  /// Standard affine form with the ExactError kernel for long double
  typedef AffineForm<long double, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP,
		     yalaa::pol::AF0, yalaa::pol::ErrorPolStd, details::l_double_iv_t> aff_e_ld;

  /// Standard affine form with the ExactError kernel for long double with decorations
  typedef AffineForm<long double, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP,
		     yalaa::pol::AF0, yalaa::pol::ErrorPolDec, details::l_double_iv_t> aff_e_ld_dec;
#endif

}

#endif /*__YALAA_FWD_HPP__*/

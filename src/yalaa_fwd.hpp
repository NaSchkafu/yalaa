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
 * Furthermore, \c YalAA requires the <a href="http://www.boost.org">Boost libaries</a> >= 1.4.7
 * 
 * In order to use \c YalAA an external library for interval arithmetic is required.
 * The following libraries are currently supported
 * \li <a href="http://www2.math.uni-wuppertal.de/~xsc/">C-XSC</a> >= 2.5.0
 * \li <a href="http://www2.math.uni-wuppertal.de/~xsc/software/filib.html">filib++</a> >= 3.0.2
 * \li <a href="http://www.ti3.tu-harburg.de/Software/PROFILEnglisch.html">Profile/Bias</a> >= 2.0.8
 * 
 * 
 * If you want to use another library, you have to provide a specialization of the interval_traits 
 * template class. Please refer to \ref custom_ivlib.
 * 
 * 
 * \subsection win Microsoft Windows
 * 
 * \li TODO
 *
 * 
 * \subsection unix Linux/Unix-like
 * \li Unpack the archive to your desired location (<tt>tar xfj yalaa.tar.bz2</tt>)
 * \li Check the configure parameters (<tt>./configure --help</tt>)
 * \li Run configure with desired parameters for your system <br> 
 * (Example: <tt>./configure --with-cxsc=<CXSC-PATH> --with-boost==<BOOST-PATH></tt>)
 * \li Build the library (<tt>make</tt>)
 * \li Install the library (<tt>make install</tt>) <br>
 * <i>If desired, use the \c prefix option of \c configure if to install \c YalAA in your \c $HOME directory</i>
 * 
 * \subsection Documentation
 * For creating the documentation you need <a href="http://www.stack.nl/~dimitri/doxygen/">Doxygen</a>.
 * \li Select the output format by using the \c configure script 
 * \li Start the creation process (\c make doxygen-doc)
 * \li The documentation is generated in the directory \c doc
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
 * <td>\c aff_e_d</td> <td><tt>double</tt></td> <td>ExactErrorFP</td> <td>AF0</td> <td>Standard</td> 
 * </tr>
 * <tr>
 * <td> \c aff_af1_e_d </td> <td>\c double </td> <td>ExactErrorFP</td> <td>AF1</td> <td>Standard</td> 
 * </tr>
 * <tr>
 * <td> \c aff_af2_e_d </td> <td>\c double </td> <td>ExactErrorFP</td> <td>AF2</td> <td>Standard</td> 
 * </tr>
 * <tr>
 * <td> \c aff_e_d_dec </td> <td>\c double </td> <td>ExactErrorFP</td> <td>AF0</td> <td>Decorations</td> 
 * </tr>
 * <tr>
 * <td> \c aff_af1_e_d_dec </td> <td>\c double </td> <td>ExactErrorFP</td> <td>AF1</td> <td>Decorations</td> 
 * </tr>
 * <tr>
 * <td> \c aff_af2_e_d_dec </td> <td>\c double </td> <td>ExactErrorFP</td> <td>AF2</td> <td>Decorations</td> 
 * </tr>
 * </table>
 * 
 * The different error handling approaches and the policy types are explained in \c YalAA's
 * implementation paper. Furthermore, the namespace yalaa::concepts contains templates for
 * creating your own policies.
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
 * <td>\link function.cpp \endlink</td> <td>Evaluates a function with \c YalAA</td>
 * </tr>
 * <tr>
 * <td>\link decorations.cpp \endlink</td> <td>Shows the usage of decorations in \c YalAA</td>
 * </tr>
 * <tr>
 * <td>\link policies.cpp \endlink</td> <td>Shows how the different policies alter the computation in \c YalAA</td> 
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
 * \section License
 * \c YalAA is free software and available under the terms of the GNU Lesser General Public License
 * Version 3. For more details refer to the files COPYING and COPYING.LESSER, which are included
 * in the distribution.
 * 
 * \section Download
 * Current version <br>
 * \li <a href="download/yalaa-0.9.tar.gz">YalAA Version 0.9</a> (Preview version)
 * 
 * 
 * \section Contact
 * If you have any questions, suggenstions or bug reports regarding \c YalAA do not hesitate
 * to write me an <a href="mailto:kiel@inf.uni-due.de">email</a>.
 */

/**
 * \example function.cpp
 * Example that illustrates how to evaluate a function with \c YalAA.
 */


/**
 * \example decorations.cpp
 * Example that illustrates how the decoration mechanism in \c YalAA 
 * works in different situations.
 */

/**
 * \example policies.cpp
 * Example that illustrates how the different policies in \c YalAA alter
 * the computation process.
 */


/**
 * \todo Documentation for the Windows Version is missing
 * \todo Documentation for using custom interval libraries is missing
 * \todo Add missing function of P1788 required elementary functions
 * \todo Add posteriori error handling approach
 * 
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
#include "traits/double_traits.hpp"
#ifdef YALAA_HAVE_FLOAT
#include "traits/float_traits.hpp"
#endif
#ifdef YALAA_HAVE_LONG_DOUBLE_WIDER
#include "traits/l_double_traits.hpp"
#endif
#include "traits/interval_traits.hpp"
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

  /// Extended affine form AF1 with the ExactError kernel for double
  typedef AffineForm<double, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP, 
		     yalaa::pol::AF1, yalaa::pol::ErrorPolStd, details::double_iv_t> aff_af1_e_d;

  /// Standard affine form with the ExactError kernel for double with decorations
  typedef AffineForm<double, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP, 
		     yalaa::pol::AF0, yalaa::pol::ErrorPolDec, details::double_iv_t> aff_e_d_dec;

  /// Extended affine form AF1 with the ExactError kernel for double with decorations
  typedef AffineForm<double, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP, 
		     yalaa::pol::AF1, yalaa::pol::ErrorPolDec, details::double_iv_t> aff_af1_e_d_dec;

  /// Extended affine form AF2 with the ExactError kernel for double with decorations
  // typedef AffineForm<double, details::ErrorTermImpl, details::AffineCombImpl, kernel::ExactErrorFP, 
  // 		     yalaa::pol::AF2, yalaa::pol::ErrorPolDec, details::double_iv_t> aff_af2_e_d_dec;
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

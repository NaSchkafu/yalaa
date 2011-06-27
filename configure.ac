AC_INIT([yalaa],[0.1],[kiel@inf.uni-due.de])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
	Makefile])
AC_CONFIG_MACRO_DIR([m4])

dnl Compiler
AC_PROG_CXX

dnl System Header
AC_CHECK_HEADERS([fenv.h float.h])
AC_CHECK_FUNCS([fesetround])
AX_CXX_HEADER_STDCXX_98
AC_TYPE_LONG_DOUBLE_WIDER

dnl BOOST
BOOST_REQUIRE([1.40])
BOOST_TYPETRAITS
BOOST_UTILITY
BOOST_OPERATORS

dnl Interval Libs
dnl AC_ARG_WITH([interval], [AS_HELP_STRING([--with-interval=<cxsc|filib>], [Interval library to use])])dnl
m4_define([ivlibs],[[filib], [cxsc]])
m4_foreach([var], [ivlibs],[AS_IF([test x"$with_[]var" != x -o x"$m4_translit(var, [a-z], [A-Z])[]_ROOT" != x],[use_iv_lib=var])
])
AS_CASE([$use_iv_lib],[filib],[
dnl filib++
SEARCH_HEADER([filib],[interval/interval.hpp], [], [filib])
SEARCH_LIBRARY([filib],[filib::fp_traits<double>::setup();],[],[],[#include <interval/interval.hpp>
],[prim])
],[
dnl cxsc
AS_IF([test x"$use_iv_lib" = x],[AC_MSG_NOTICE([No interval library specified. Assuming --with-cxsc=yes])
	    with_cxsc=yes; use_iv_lib=cxsc
])
CXSC_REQUIRE([2],[2],[4])
CXSC_FIND_LIB])
m4_foreach([var],[ivlibs],[
	AM_CONDITIONAL(m4_translit(var, [a-z], [A-Z]),[test x"$use_iv_lib" = x"var"])
])


dnl DEBUG
AC_ARG_ENABLE([debug],AS_HELP_STRING([--disable-debug],[disables debugging built]), [AS_IF([test x"$withval" = x],[enable_debug=])],[enable_debug=debug])
CFLAGS=
CXXFLAGS=
AS_IF([test x"$enable_debug" = "xdebug"],[CXXFLAGS="-g"],[CXXFLAGS=-O2])

dnl Compiler specific settings
AS_CASE([$CXX],[clang++],[
CXXFLAGS+=" -msse2 -Wno-logical-op-parentheses"
],[g++],[
CXXFLAGS+=" -frounding-math -mfpmath=sse -msse2 -std=c++0x"],[
AC_MSG_NOTICE([Unknown compiler. Please set flags for rounding math if necessary!])])

dnl Libtool
LT_INIT
 

dnl Ausgeben
AC_OUTPUT

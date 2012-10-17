AC_INIT([yalaa],[0.92],[kiel@inf.uni-due.de])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
#AM_PROG_AR
AC_CONFIG_HEADERS([config.h])
AX_PREFIX_CONFIG_H([src/yalaa-config.h])
AC_CONFIG_FILES([Makefile
	src/Makefile
	examples/Makefile])
AC_CONFIG_MACRO_DIR([m4])

dnl Compiler
USER_CXXFLAGS=$CXXFLAGS
AC_PROG_CXX
AC_CXX_COMPILE_STDCXX_0X
CXXFLAGS="$USER_CXXFLAGS $CXX0X_FLAGS"

dnl System Header
AC_CHECK_HEADERS([fenv.h float.h])
AC_CHECK_FUNCS([fesetround])
AX_CXX_HEADER_STDCXX_98
AC_TYPE_LONG_DOUBLE_WIDER

dnl BOOST
BOOST_REQUIRE([1.47])
BOOST_TYPETRAITS
BOOST_UTILITY
BOOST_OPERATORS

dnl Interval Libs
dnl AC_ARG_WITH([interval], [AS_HELP_STRING([--with-interval=<cxsc|filib>], [Interval library to use])])dnl
AC_ARG_WITH([custom_ivlib], [AS_HELP_STRING([--with-custom_ivlib=<yes>], [Use a custom interval library])])dnl
m4_define([ivlibs],[[filib], [profil_bias], [custom_ivlib], [cxsc]])
m4_foreach([var], [ivlibs],[
AC_MSG_CHECKING([whether to use ] m4_translit(var, [a-z], [A-Z]))
AS_IF([test x"$with_[]var" != x -o x"$m4_translit(var, [a-z], [A-Z])[]_ROOT" != x],
[AS_IF([test x"$use_iv_lib" = x],[use_iv_lib=var
AC_MSG_RESULT([yes])], [
AC_MSG_ERROR([More than one interval library specified!])])],
[AC_MSG_RESULT([no])])])
AS_CASE([$use_iv_lib],[filib],[
dnl filib++
SEARCH_HEADER([filib],[interval/interval.hpp], [], [filib])
SEARCH_LIBRARY([filib],[filib::fp_traits<double>::setup();],[],[],[#include <interval/interval.hpp>
],[prim])
],[profil_bias],[
dnl PROFILE/BIAS
SEARCH_HEADER([profil_bias],[Interval.h], [], [])
SEARCH_LIBRARY([profil_bias],[Sin(INTERVAL(2.0));], [-lProfil -lBias -lm], [], [#include <Interval.h>
#include <Functions.h>],[lr])
PROFIL_BIAS_LIBS="-lProfil -lBias $PROFIL_BIAS_LIBS"
],[custom_ivlib], [
dnl Custom LIB
AC_DEFINE([HAVE_CUSTOM_IV_LIB], [1], [Use a custom IV library])
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
AC_MSG_CHECKING([whether to build with debug information])
AC_ARG_ENABLE([debug],AS_HELP_STRING([--enable-debug],[enables debugging built]), [enable_debug="$enableval"], [enable_debug=no])
AC_MSG_RESULT([$enable_debug])
AS_IF([test x"$enable_debug" = "xyes"], [AC_DEFINE([DEBUG], [], [Debugging built])
	    DEBUG_FLAGS="-g -O0"],[AC_DEFINE([NDEBUG], [], [No debugging built])
	    DEBUG_FLAGS=-O3])
AC_SUBST([DEBUG_FLAGS])

dnl Compiler specific settings
AS_CASE([$CXX],[clang++],[
CXXFLAGS+=" -msse2 -Wno-logical-op-parentheses"
],[g++],[
CXXFLAGS+=" -frounding-math -mfpmath=sse -msse2"],[
AC_MSG_NOTICE([Unknown compiler. Please set flags for rounding math if necessary!])])
CXXFLAGS+=" $CXX0X_FLAGS"

dnl TESTS
AC_ARG_ENABLE([tests], AS_HELP_STRING([--enable-tests],[Enable unit tests, requires Google Test (GTEST)]), dnl
[AS_IF([test x"$withval" != x], [enable_tests=yes],[enable_tests=])])
AS_IF([test x"$with_gtest" != x], [AC_MSG_NOTICE([--with-gtest is set. Assuming --enable-tests flag!]) 
enable_tests=yes])
AS_IF([test x"$enable_tests" != x], [SEARCH_HEADER([gtest],[gtest.h],[], [include/gtest])
SEARCH_LIBRARY([gtest],[], [-lpthread], [lib/.libs], [], [])
])
AM_CONDITIONAL([GTEST], [test x"$enable_tests" = xyes])

dnl Libtool
LT_INIT
 
dnl DOXYGEN
DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(OFF)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(OFF)
DX_PS_FEATURE(OFF)
DX_INIT_DOXYGEN([$PACKAGE_NAME],[Doxyfile])

dnl Ausgeben
AC_OUTPUT

dnl -*-autoconf-*-
# ===========================================================================
#    http://www.gnu.org/software/autoconf-archive/ax_ext_check_header.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_EXT_CHECK_HEADER(<header>, <paths>).
#
# DESCRIPTION
#
#   Check for <header> with -I<path> for each path in <paths> if need be.
#   The first sucecssful path is chosen (eg if you say
#   AX_EXT_CHECK_HEADER(foo.h, bar baz qux) and -Ibaz works then -Iqux will
#   not be tested.
#
#   Any -I flags that locate a header are added to CFLAGS and CPPFLAGS. AS
#   with AC_CHECK_HEADERS it causes HAVE_<header>_H to be defined as 1.
#
#   Example:
#
#    AX_EXT_HAVE_HEADER(openssl/rsa.h, /usr/local/include /usr/local/ssl/include /usr/local/openssl/include)
#
# LICENSE
#
#   Copyright (c) 2008 Duncan Simpson <dps@simpson.demon.co.uk>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved. This file is offered as-is, without any
#   warranty.

#serial 7

dnl Gefixt und angepasst für eigene Benutzung
dnl Es wird nun die Variable $3_CPPFLAGS statt CPPFLAGS modifiziert
dnl CFLAGS bleibt unmodifiziert, Sprache ist nun C++
dnl Ferner wird HAVE_$3 definiert
dnl Optional kann $4 angegeben um CPPFLAGS zu erweitern
dnl TODO: Es sollten zuerst die angegebenen Verzeichnisse überprüft und erst
dnl danach der Standardsuchpfad beachtet werden...
AC_DEFUN([AX_EXT_HAVE_HEADER_SK],
[old_cppflags=$CPPFLAGS
 AC_LANG_PUSH([C++])
 hdr=`echo $1 | $as_tr_sh`
 AC_CHECK_HEADER($1, [got="yes"], [got="no"])
 AS_IF([test "x$got" = "xyes"],[$3[_CPPFLAGS]=default],[
 for dir in $2; do
  if test "x${got}" = "xno"; then
   ext_hashdr_cvdir=`echo $dir | $as_tr_sh`
   AC_CACHE_CHECK([for $1 header with -I$dir],
    [ext_cv${ext_hashdr_cvdir}_hashdr_${hdr}],
    [ext_have_hdr_save_cflags=${CFLAGS}
     CPPFLAGS="${CPPFLAGS} -I${dir} $4"
     AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM([#include <$1>])],
       [got="yes"; eval "ext_cv${ext_hashdr_cvdir}_hashdr_${hdr}"="yes"],
       [got="no"; eval "ext_cv${ext_hashdr_cvdir}_hashdr_${hdr}"="no"])
      CFLAGS=$ext_have_hdr_save_cflags])
     if eval `echo 'test x${'ext_cv${ext_hashdr_cvdir}_hashdr_${hdr}'}' = "xyes"`; then
      $3[_CPPFLAGS]="-I${dir}"
      got="yes";
      hdr=`echo $1 | $as_tr_cpp`
      AC_DEFINE_UNQUOTED(HAVE_$3, 1,
       [Define this if you have the $1 header])
     fi;
   fi; 
done
])
AC_LANG_POP])

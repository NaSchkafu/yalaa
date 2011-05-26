dnl -*-autoconf-*-
# Sucht das cut Programm
AC_DEFUN([CUT_REQUIRE],
[AC_ARG_VAR([CUT_PROGRAM],[path to the cut program])dnl
AC_PATH_PROG([CUT_PROGRAM],[cut],[])dnl
if test x"$CUT_PROGRAM" = x; then
AC_MSG_ERROR([cannot find the cut program])
fi
])

AC_DEFUN([CXSC_REQUIRE],
[AC_REQUIRE([AC_PROG_CXX])dnl
AC_REQUIRE([AC_PROG_GREP])dnl
AC_REQUIRE([CUT_REQUIRE])dnl
AC_REQUIRE([AC_PROG_SED])dnl
cxsc_req_version=$1.$2.$3
shift
AC_ARG_WITH([cxsc],
	[AS_HELP_STRING([--with-cxsc=DIR], [prefix of C-XSC $1])])dnl
AC_ARG_VAR([CXSC_ROOT],[Location of C-XSC installation])dnl
if test x"$CXSC_ROOT" != x; then
   if test x"$with_cxsc" = x; then
      AC_MSG_NOTICE([Using --with-cxsc=$CXSC_ROOT])
      with_cxsc=$CXSC_ROOT
   else
      AC_MSG_NOTICE([CXSC_ROOT overriden by --with-cxsc=$with_cxsc])
   fi
fi
AC_SUBST([DISTCHECK_CONFIGURE_FLAGS],
         ["$DISTCHECK_CONFIGURE_FLAGS '--with-cxsc=$with_cxsc'"])
dnl AC_SUBST ausgelassen
cxsc_save_CPPFLAGS=$CPPFLAGS
AC_CACHE_CHECK([for C-XSC headers version >= $cxsc_req_version],
		    [cxsc_cv_inc_path],
		    [cxsc_cv_inc_path=no
case $with_cxsc in
     ''|yes) set x /usr/local/cxsc/include $HOME/cxsc/include;;
     *)	     set x "$with_cxsc/include" "$with_cxsc";;
esac
shift
for cxsc_dir
do
test -e "$cxsc_dir/interval.hpp" || continue
found_cxsc_ver=`${GREP} -o -m 1 ["(V [0-9]\+\.[0-9]\+[\.[0-9]\+]\?)$"] \
	"$cxsc_dir"/interval.hpp | ${GREP} -o -m 1 \ 
	["[0-9]\+\.[0-9]\+[\.[0-9]\+]\?"]`
dnl m4_for([i],[1],[$#],[1],
dnl echo "test $found_cxsc_ver | cut -d . -f i -gt $i";)
dnl TODO: $i wird nicht expandiert Warum?
test `echo "$found_cxsc_ver" | ${SED} "s/\.//g"` -ge $1$2$3 || continue
cxsc_cv_inc_path=$cxsc_dir
done])
if test x"$cxsc_cv_inc_path" = xno; then
AC_MSG_ERROR([could not find C-XSC headers >= $cxsc_req_version])
fi
AC_SUBST([CXSC_CPPFLAGS], ["-I$cxsc_cv_inc_path"])
AC_DEFINE_UNQUOTED(HAVE_CXSC, 1, [Define this if you have the CXSC header])
])

AC_DEFUN([CXSC_FIND_LIB],
[AC_ARG_WITH([cxsc-ldpath], [AS_HELP_STRING([--with-cxsc-ldpath], 
	[path of the C-XSC library])])
if test x"$cxsc_cv_inc_path" = xno; then
   AC_MSG_ERROR([could not find the C-XSC library])
fi
AC_LANG_PUSH([C++])
dnl AC_CACHE_CHECK([for the C-XSC library], [cxsc_cv_ldpath],
cxsc_cv_ldpath=no
dnl FIXME: CXSC_ROOT beachten
if test x"$with_cxsc_ldpath" != x; then
   set x "$with_cxsc_ldpath"
else
   set x `echo $cxsc_cv_inc_path | ${SED} "s/include\/\?$/lib/"` \ 
       	 /usr/local/lib /usr/local/cxsc/lib
fi
shift
old_ldflags=$LDFLAGS
for cxsc_dir
do
LDFLAGS="$old_ldflags -L$cxsc_dir"
AC_CHECK_LIB([cxsc],[r_cnsu],
	[cxsc_cv_ldpath="-L$cxsc_dir -lcxsc"; break],[],[])
done
LDFLAGS=$old_ldflags
AC_LANG_POP([C++])
if test x"$cxsc_cv_ldpath" = xno; then
   AC_MSG_ERROR([could not find cxsc library])
fi
AC_SUBST([CXSC_LIBS],["$cxsc_cv_ldpath"])
dnl AS_VAR_POPDEV([CXSC_LDPATH])
])


dnl -*-autoconf-*-
dnl Autor: Stefan Kiel, stefan.kiel@gmx.net
dnl Diese Datei stellt zwei Makros zur Verfügung um Header und Bibliotheken zu suchen
dnl und automatisch passende Variablen für automake zu generieren. Beide Funktionen
dnl sind flexibel generisch konfigurierbar.

dnl Sucht Header
dnl Parameter $1: Name
dnl Parameter $2: Name(n) der Datei
dnl Parameter $3: CPPFLAGS für Suchen der Header
dnl Parameter $4: Zusätzliches Suffix für Headersuche
dnl Es wird automatisch eine Option --with-$1 erzeugt
dnl außerdem wird die Umgebungsvariable $1_ROOT akzeptiert
dnl Definiert HAVE_$1 falls der Header gefunden wird
dnl Ferner wird eine Substitutionsregel für $1_CPPFLAGS erzeugt
AC_DEFUN([SEARCH_HEADER],
[AS_VAR_PUSHDEF([with_n], [with_$1])
AS_VAR_PUSHDEF([upcase_n], m4_translit([$1], [a-z], [A-Z]))dnl
AS_VAR_PUSHDEF([n_root], upcase_n[_ROOT])dnl
AS_VAR_PUSHDEF([n_inc], [$1_cv_inc_path])
AC_ARG_WITH([$1], 
	[AS_HELP_STRING([--with-$1=DIR], [prefix of ]upcase_n)])dnl
AC_ARG_VAR(upcase_n[_ROOT],[Location of ]upcase_n[ installation])dnl
AS_IF([test x"$n_root" != "x"], 
[AS_IF([test x"$with_n" = "x"],
      [AC_MSG_NOTICE([Detected \$]n_root[; assuming --with-$1=$]n_root)
      with_n=$[]n_root],
      [AC_MSG_NOTICE(n_root[ overriden by --with-$1=]$with_n)])
])
AC_CACHE_VAL(n_inc,
[n_inc=no
	case $with_n in
	     ''|yes) incdirs="/usr/local/include /usr/local/$1 /opt/$1 /usr/local/$1/include /opt/$1/include \
	     	     m4_if($4[]x,[x],[],[/usr/local/include/$4 /usr/local/$1/$4 /opt/$1/$4 /usr/local/$1/$4/include /opt/$1/$4/include])";;		 
	     *)      incdirs="$with_n $with_n/include m4_if($4[]x,[x],[],[$with_n/$4 $with_n/$4/include])";;		 
	esac
AX_EXT_HAVE_HEADER_SK([$2],[$incdirs], upcase_n, [$3])
dnl echo "Myflags $upcase_n[_CPPFLAGS]"
AS_IF([test x"$upcase_n[]_CPPFLAGS" != x],
AS_IF([test x"$upcase_n[]_CPPFLAGS" = "xdefault"],[upcase_n[]_CPPFLAGS=""])
n_inc=$upcase_n[_CPPFLAGS],
[AC_MSG_ERROR([cannot find ]upcase_n[ headers])])])
AC_SUBST(upcase_n[_CPPFLAGS], [$n_inc])
dnl echo $n_inc
AS_VAR_POPDEF([with_n])dnl
AS_VAR_POPDEF([upcase_n])dnl
AS_VAR_POPDEF([n_root])dnl
AS_VAR_POPDEF([n_inc])dnl
])

dnl Sucht Bibliotheken
dnl FIXME: Parameter sinnvoll umstellen
dnl Parameter $1: Name
dnl Parameter $2: Body
dnl Parameter $3: LDFLAGS für Linken
dnl Parameter $4: Zusätzliches Suffix für Bibliotheken
dnl Parameter $5: Prolog
dnl Parameter $6: Optionaler Bibliotheksname(n)
dnl Es wird automatisch eine Option --with-$1-ldpath erzeugt
dnl außerdem wird die Umgebungsvariable $1_ROOT akzeptiert
dnl Ferner wird eine Substitutionsregel für $1_LDFLAGS und $1_LIBS
AC_DEFUN([SEARCH_LIBRARY],
[AS_VAR_PUSHDEF([with_n], [with_$1_ldpath])
AS_VAR_PUSHDEF([upcase_n], m4_translit([$1], [a-z], [A-Z]))dnl
AS_VAR_PUSHDEF([n_root], upcase_n[_ROOT])dnl
AS_VAR_PUSHDEF([n_lib], [$1_cv_lib_path])
AS_VAR_PUSHDEF([n_lib_name], [$1_cv_lib_name])
AC_ARG_WITH([$1-ldpath], 
	[AS_HELP_STRING([--with-$1-ldpath=DIR], [prefix of ]upcase_n)])dnl
AC_ARG_VAR(upcase_n[_ROOT],[Location of ]upcase_n[ libraries])dnl
AS_IF([test x"$n_root" != "x"], 
[AS_IF([test x"$with_n" = "x"],
      [AC_MSG_NOTICE([Detected \$]n_root[; assuming --with-ldapth-$1=$]n_root)
      with_n=$[]n_root],
      [AC_MSG_NOTICE(n_root[ overriden by --with-ldpath-$1=]$with_n)])
])
AS_IF([test x"$with_n" = x -a x"$with_$1" != "x"],[
	    AC_MSG_NOTICE([--with-$1 found but not --with-$1-ldpath. Assuming --with-$1-ldpath=$with_$1])
	    with_n=$with_$1])
AC_CACHE_VAL(n_lib,
[AC_CACHE_VAL(n_lib_name,
[n_lib_name=no
n_lib=no
AS_CASE([$with_n],[''|yes], 
	[libdirs="/usr/local/lib /usr/local/$1 /opt/$1 /usr/local/$1/lib /opt/$1/lib m4_if($4[]x,[x],[],[/usr/local/lib/$4 /usr/local/$1/$4 /opt/$1/$4 /usr/local/$1/$4/lib /opt/$1/$4/lib])"],
	[libdirs="$with_n $with_n/lib m4_if($4[]x,[x],[],[$with_n/$4 $with_n/$4/lib])"])
old_ldflapgs=$LDFLAGS
old_libs=$LIBS
AC_LANG_PUSH([C++])
shift
dnl AX_EXT_HAVE_LIB_SK([$libdirs],[$1], [$2], [$3])
#m4_if($6[]x,[x],[libnames="-l$1"],[libnames="-l$1 $6"])
m4_foreach_w([libname],[$1 $6],
[LIBS="$old_libs $3 -l[]libname"
for libdir in $libdirs; do
#echo $libdir
LDFLAGS="$old_ldflags -L$libdir"
AC_MSG_CHECKING([for $1 library with -L$libdir -l[]libname])
AC_LINK_IFELSE([AC_LANG_PROGRAM([[$5]],[[$2]])],[upcase_n[]_LDFLAGS="-L$libdir"
	upcase_n[]_LIBS="-l[]libname"; AC_MSG_RESULT([yes]); break], 
	AC_MSG_RESULT([no]))
done
])
AC_LANG_POP([C++])
AS_IF([test x"$upcase_n[]_LDFLAGS" != x],n_lib=$upcase_n[_LDFLAGS];
	    n_lib_name=$upcase_n[]_LIBS, 
	    [AC_MSG_ERROR([cannot find ]upcase_n[ library])])
])])
AC_SUBST(upcase_n[_LDFLAGS], [$n_lib])
AC_SUBST(upcase_n[_LIBS], [$n_lib_name])
dnl echo $n_lib
AS_VAR_POPDEF([with_n])dnl
AS_VAR_POPDEF([upcase_n])dnl
AS_VAR_POPDEF([n_root])dnl
AS_VAR_POPDEF([n_lib])dnl
AS_VAR_POPDEF([n_lib_name])dnl
LDFLAGS=$old_ldflags
LIBS=$old_libs
])

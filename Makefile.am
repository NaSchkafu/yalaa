SRC_FILES = src/helper/fphelper.cpp src/yalaa_fp_impl.cpp
ACLOCAL_AMFLAGS = -I m4

if CXSC
IV_CPPFLAGS = $(CXSC_CPPFLAGS)
IV_FLAGS = $(CXSC_LIBS)
endif

if FILIB
IV_CPPFLAGS = $(FILIB_FLAGS)
IV_FLAGS = $(FILIB_LDFLAGS)
IV_LIBS = $(FILIB_LIBS)
endif



AM_CPPFLAGS = $(EXTRA_INC) -Isrc $(IV_CPPFLAGS) $(BOOST_CPPFLAGS)

lib_LTLIBRARIES = libyalaa.la
libyalaa_la_SOURCES = $(SRC_FILES)
#libyalaa_la_LDFLAGS = $(IV_FLAGS)
#libyalaa_la_LIBADD = $(IV_LIBS)

bin_PROGRAMS = yalaa
if GTEST
bin_PROGRAMS += test_yalaa
endif

yalaa_SOURCES = src/main.cpp
yalaa_LDADD = $(LIBS) $(IV_LIBS) libyalaa.la
yalaa_LDFLAGS = $(LDFLAGS) $(IV_FLAGS)
yalaa_CPPFLAGS = $(AM_CPPFLAGS)
yalaa_CXXFLAGS = $(AM_CXXFLAGS)
nobase_include_HEADERS = src/yalaa_assert.hpp src/helper/ivhelper_hpp src/helper/fphelper.hpp src/helper/fastia.hpp src/helper/ivhelper.hpp src/comb/affinecombopimpl.hpp src/comb/affinecombimpl.hpp src/comb/affinecombbaseimpl.hpp src/errortermimpl.hpp src/affineform_double.hpp src/yalaa_iv.hpp src/yalaa.hpp src/yalaa_ios.hpp src/affineform_fwd.hpp src/traits/l_double_traits.hpp src/traits/double_traits.hpp src/traits/float_traits.hpp src/traits/filib_traits.hpp src/traits/base_traits.hpp src/traits/cxsc_traits.hpp src/kernel/arithmeticerror.hpp src/kernel/aff/exacterroraffinefp.hpp src/kernel/exacterror.hpp src/kernel/nonaff/minrangefp.hpp src/kernel/nonaff/mulfp.hpp src/kernel/nonaff/chebyshevfp.hpp src/specialterms.hpp src/pol/af1.hpp src/pol/af2.hpp src/pol/af0.hpp src/pol/errorpoldec.hpp src/pol/errorpolstd.hpp src/yalaa_fwd.hpp src/affineform.hpp src/affineform.inl src/kernel/arithmeticerror.inl src/pol/af0.inl src/pol/af2.inl src/pol/errorpoldec.inl src/pol/errorpolstd.inl src/pol/af1.inl src/affineform_double.inl src/errortermimpl.inl src/config_sel.h src/yalaa-config.h

if GTEST
test_yalaa_SOURCES = src/tests/ftmeta.cpp src/tests/test_main.cpp
test_yalaa_LDADD = $(LIBS) $(IV_LIBS) $(GTEST_LIBS) libyalaa.la
test_yalaa_LDFLAGS = $(LDFLAGS) $(IV_FLAGS) $(GTEST_LDFLAGS)
test_yalaa_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_FLAGS)
test_yalaa_CXXFLAGS = $(AM_CXXFLAGS)
endif

install-exec-data:
	mv $(DESTDIR)$(includedir)/src/* $(DESTDIR)$(includedir)/
	rm $(DESTDIR)$(includedir)/src

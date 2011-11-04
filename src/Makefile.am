SRC_FILES = helper/fphelper.cpp yalaa_fp_impl.cpp
ACLOCAL_AMFLAGS = -I ../m4

lib_LTLIBRARIES = libyalaa.la
libyalaa_la_SOURCES = $(SRC_FILES)
#libyalaa_la_LDFLAGS = $(IV_FLAGS)
#libyalaa_la_LIBADD = $(IV_LIBS)

if GTEST
bin_PROGRAMS = test_yalaa
endif

nobase_include_HEADERS = yalaa_assert.hpp helper/ivhelper_hpp helper/fphelper.hpp helper/fastia.hpp comb/affinecombopimpl.hpp comb/affinecombimpl.hpp comb/affinecombbaseimpl.hpp errortermimpl.hpp affineform_double.hpp yalaa_iv.hpp yalaa.hpp yalaa_ios.hpp affineform_fwd.hpp traits/l_double_traits.hpp traits/double_traits.hpp traits/float_traits.hpp traits/filib_traits.hpp traits/base_traits.hpp traits/cxsc_traits.hpp kernel/arithmeticerror.hpp kernel/aff/exacterroraffinefp.hpp kernel/exacterror.hpp kernel/nonaff/minrangefp.hpp kernel/nonaff/mulfp.hpp kernel/nonaff/chebyshevfp.hpp specialterms.hpp pol/af1.hpp pol/af2.hpp pol/af0.hpp pol/errorpoldec.hpp pol/errorpolstd.hpp yalaa_fwd.hpp affineform.hpp affineform.inl kernel/arithmeticerror.inl pol/af0.inl pol/af2.inl pol/errorpoldec.inl pol/errorpolstd.inl pol/af1.inl affineform_double.inl errortermimpl.inl config_sel.h yalaa-config.h traits/profil_traits.hpp traits/custom_iv_traits.hpp traits/interval_traits.hpp

EXTRA_libyalaa_la_SOURCES = comb/affinecombopimpl.cpp comb/affinecombimpl.cpp comb/affinecombbaseimpl.cpp kernel/aff/exacterroraffinefp.cpp kernel/nonaff/mulfp.cpp kernel/nonaff/minrangefp.cpp kernel/nonaff/chebyshevfp.cpp kernel/exacterror.cpp helper/ia_aa.hpp

if GTEST
test_yalaa_SOURCES = tests/ftmeta.cpp tests/test_main.cpp
test_yalaa_LDADD = $(LIBS) $(IV_LIBS) $(GTEST_LIBS) libyalaa.la
test_yalaa_LDFLAGS = $(LDFLAGS) $(IV_FLAGS) $(GTEST_LDFLAGS)
test_yalaa_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_FLAGS)
test_yalaa_CXXFLAGS = $(AM_CXXFLAGS)
endif


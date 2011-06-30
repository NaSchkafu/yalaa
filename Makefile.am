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



AM_CPPFLAGS = -frounding-math -mfpmath=sse -msse2 $(EXTRA_INC) -Isrc $(IV_CPPFLAGS) $(BOOST_CPPFLAGS)

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

if GTEST
test_yalaa_SOURCES = src/tests/ftmeta.cpp src/tests/test_main.cpp
test_yalaa_LDADD = $(LIBS) $(IV_LIBS) $(GTEST_LIBS) libyalaa.la
test_yalaa_LDFLAGS = $(LDFLAGS) $(IV_FLAGS) $(GTEST_LDFLAGS)
test_yalaa_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_FLAGS)
test_yalaa_CXXFLAGS = $(AM_CXXFLAGS)
endif

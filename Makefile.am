SRC_FILES = src/helper/fphelper.cpp src/yalaa.cpp 
ACLOCAL_AMFLAGS = -I m4

if CXSC
IV_CPP_FLAGS = $(CXSC_CPPFLAGS)
IV_LIBS = $(CXSC_LIBS)
endif

if FILIB
IV_CPP_CLFGAS = $(FILIB_FLAGS)
IV_LIBS = $(FILIB_LIB) $(FLIB_LDFLAGS)
endif


AM_CPPFLAGS = -frounding-math -mfpmath=sse -msse2 $(EXTRA_INC) -Isrc $(IV_CPP_FLAGS) $(BOOST_CPPFLAGS)

lib_LTLIBRARIES = libyalaa.la
libyalaa_la_SOURCES = $(SRC_FILES)

bin_PROGRAMS = yalaa
yalaa_SOURCES = src/main.cpp
yalaa_LDADD = $(LIBS) libyalaa.la
yalaa_LDFLAGS = $(LDFLAGS) $(IV_LIBS)
yalaa_CPPFLAGS = $(AM_CPPFLAGS)
yalaa_CXXFLAGS = $(AM_CXXFLAGS)


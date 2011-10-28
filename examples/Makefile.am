AM_CPPFLAGS = $(EXTRA_INC) -Isrc $(IV_CPPFLAGS) $(BOOST_CPPFLAGS) @AM_CPPFLAGS@

bin_PROGRAMS = function
function_SOURCES = function.cpp
function_LDADD = $(LIBS) $(IV_LIBS) libyalaa.la
function_LDFLAGS = $(LDFLAGS) $(IV_FLAGS)
function_CPPFLAGS = $(AM_CPPFLAGS)
function_CXXFLAGS = $(AM_CXXFLAGS)


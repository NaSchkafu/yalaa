override AM_CPPFLAGS += -I$(top_srcdir)/src
LDADD = $(top_builddir)/src/libyalaa.la $(LIBS) $(IV_LIBS)

bin_PROGRAMS = function decorations policies abs polarity
function_SOURCES = function.cpp
decorations_SOURCES = decorations.cpp
policies_SOURCES = policies.cpp
abs_SOURCES = abs.cpp
polarity_SOURCES = polarity.cpp
AM_LDFLAGS = $(LDFLAGS) $(IV_FLAGS)


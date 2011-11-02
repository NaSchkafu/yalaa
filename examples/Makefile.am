override AM_CPPFLAGS += -I$(top_srcdir)/src
LDADD = $(LIBS) $(IV_LIBS) $(top_builddir)/src/libyalaa.la

bin_PROGRAMS = function decorations policies
function_SOURCES = function.cpp
decorations_SOURCES = decorations.cpp
policies_SOURCES = policies.cpp
AM_LDFLAGS = $(LDFLAGS) $(IV_FLAGS)


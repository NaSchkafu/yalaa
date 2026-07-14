# Copyright 2026 Stefan Kiel <kiel@inf.uni-due.de>
#
# This file is part of yalaa.
#
# yalaa is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, version 3 of the License.
#
# yalaa is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with yalaa.  If not, see <http://www.gnu.org/licenses/>.

#[=======================================================================[.rst:
FindCXSC
--------

Finds the C-XSC extended-precision/interval arithmetic library
(https://www.xsc.de), version 2.5.0 or newer.

Hints
^^^^^

The ``CXSC_ROOT`` variable (or environment variable) may be set to the
install prefix of C-XSC (the directory containing ``include/`` and
``lib/``), matching the layout produced by C-XSC's own ``install_cxsc``
script.

Result Variables
^^^^^^^^^^^^^^^^^

``CXSC_FOUND``
  True if C-XSC headers and library were found and satisfy the requested
  version.
``CXSC_INCLUDE_DIR``
  Directory containing ``interval.hpp``.
``CXSC_LIBRARY``
  Path to the C-XSC library.
``CXSC_VERSION``
  Version of C-XSC found, e.g. ``2.5.4``.

Imported Targets
^^^^^^^^^^^^^^^^

``CXSC::CXSC``
  The C-XSC library, if found.
#]=======================================================================]

find_path(CXSC_INCLUDE_DIR
  NAMES interval.hpp
  HINTS ${CXSC_ROOT} ENV CXSC_ROOT
  PATH_SUFFIXES include
  PATHS /usr/local/cxsc $ENV{HOME}/cxsc
)

find_library(CXSC_LIBRARY
  NAMES cxsc
  HINTS ${CXSC_ROOT} ENV CXSC_ROOT
  PATH_SUFFIXES lib
  PATHS /usr/local/cxsc $ENV{HOME}/cxsc
)

if(CXSC_INCLUDE_DIR AND EXISTS "${CXSC_INCLUDE_DIR}/interval.hpp")
  file(STRINGS "${CXSC_INCLUDE_DIR}/interval.hpp" _cxsc_version_line
    REGEX "\\(V [0-9]+\\.[0-9]+(\\.[0-9]+)?\\)")
  if(_cxsc_version_line MATCHES "\\(V ([0-9]+\\.[0-9]+(\\.[0-9]+)?)\\)")
    set(CXSC_VERSION "${CMAKE_MATCH_1}")
  endif()
  unset(_cxsc_version_line)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CXSC
  REQUIRED_VARS CXSC_LIBRARY CXSC_INCLUDE_DIR
  VERSION_VAR CXSC_VERSION
)

if(CXSC_FOUND AND NOT TARGET CXSC::CXSC)
  add_library(CXSC::CXSC UNKNOWN IMPORTED)
  set_target_properties(CXSC::CXSC PROPERTIES
    IMPORTED_LOCATION "${CXSC_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${CXSC_INCLUDE_DIR}"
  )
endif()

mark_as_advanced(CXSC_INCLUDE_DIR CXSC_LIBRARY)

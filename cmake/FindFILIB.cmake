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
FindFILIB
---------

Finds the filib++ interval arithmetic library
(https://www.math.uni-wuppertal.de/~xsc/software/filib.html), version
3.0.2 or newer.

Hints
^^^^^

The ``FILIB_ROOT`` variable (or environment variable) may be set to the
filib++ install prefix.

Result Variables
^^^^^^^^^^^^^^^^^

``FILIB_FOUND``
  True if the filib++ headers and library were found.
``FILIB_INCLUDE_DIR``
  Directory containing ``interval/interval.hpp``.
``FILIB_LIBRARY``
  Path to the filib++ library.

Imported Targets
^^^^^^^^^^^^^^^^

``FILIB::FILIB``
  The filib++ library, if found.
#]=======================================================================]

find_path(FILIB_INCLUDE_DIR
  NAMES interval/interval.hpp
  HINTS ${FILIB_ROOT} ENV FILIB_ROOT
  PATH_SUFFIXES include
)

# Older filib++ releases ship the compiled library as libprim.a instead of
# libfilib.a
find_library(FILIB_LIBRARY
  NAMES filib prim
  HINTS ${FILIB_ROOT} ENV FILIB_ROOT
  PATH_SUFFIXES lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FILIB
  REQUIRED_VARS FILIB_LIBRARY FILIB_INCLUDE_DIR
)

if(FILIB_FOUND AND NOT TARGET FILIB::FILIB)
  add_library(FILIB::FILIB UNKNOWN IMPORTED)
  set_target_properties(FILIB::FILIB PROPERTIES
    IMPORTED_LOCATION "${FILIB_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${FILIB_INCLUDE_DIR}"
  )
endif()

mark_as_advanced(FILIB_INCLUDE_DIR FILIB_LIBRARY)

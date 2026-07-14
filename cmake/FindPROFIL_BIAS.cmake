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
FindPROFIL_BIAS
---------------

Finds the PROFIL/BIAS interval arithmetic library
(https://www.ti3.tu-harburg.de/keil/profil/), version 2.0.8 or newer.

Hints
^^^^^

The ``PROFIL_BIAS_ROOT`` variable (or environment variable) may be set to
the PROFIL/BIAS install prefix.

Result Variables
^^^^^^^^^^^^^^^^^

``PROFIL_BIAS_FOUND``
  True if the PROFIL/BIAS headers and libraries were found.
``PROFIL_BIAS_INCLUDE_DIR``
  Directory containing ``Interval.h``.
``PROFIL_BIAS_PROFIL_LIBRARY`` / ``PROFIL_BIAS_BIAS_LIBRARY``
  Paths to the Profil and Bias libraries.

Imported Targets
^^^^^^^^^^^^^^^^

``PROFIL_BIAS::PROFIL_BIAS``
  The combined Profil+Bias library, if found.
#]=======================================================================]

find_path(PROFIL_BIAS_INCLUDE_DIR
  NAMES Interval.h
  HINTS ${PROFIL_BIAS_ROOT} ENV PROFIL_BIAS_ROOT
  PATH_SUFFIXES include
)

find_library(PROFIL_BIAS_PROFIL_LIBRARY
  NAMES Profil
  HINTS ${PROFIL_BIAS_ROOT} ENV PROFIL_BIAS_ROOT
  PATH_SUFFIXES lib
)

find_library(PROFIL_BIAS_BIAS_LIBRARY
  NAMES Bias
  HINTS ${PROFIL_BIAS_ROOT} ENV PROFIL_BIAS_ROOT
  PATH_SUFFIXES lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PROFIL_BIAS
  REQUIRED_VARS PROFIL_BIAS_PROFIL_LIBRARY PROFIL_BIAS_BIAS_LIBRARY PROFIL_BIAS_INCLUDE_DIR
)

if(PROFIL_BIAS_FOUND AND NOT TARGET PROFIL_BIAS::PROFIL_BIAS)
  add_library(PROFIL_BIAS::PROFIL_BIAS UNKNOWN IMPORTED)
  set_target_properties(PROFIL_BIAS::PROFIL_BIAS PROPERTIES
    IMPORTED_LOCATION "${PROFIL_BIAS_PROFIL_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${PROFIL_BIAS_INCLUDE_DIR}"
    INTERFACE_LINK_LIBRARIES "${PROFIL_BIAS_BIAS_LIBRARY}"
  )
endif()

mark_as_advanced(PROFIL_BIAS_INCLUDE_DIR PROFIL_BIAS_PROFIL_LIBRARY PROFIL_BIAS_BIAS_LIBRARY)

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

cmake_minimum_required(VERSION 3.16)

project(yalaa
  VERSION 0.92
  DESCRIPTION "Yet Another Library for Affine Arithmetic"
  LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(CheckCXXSourceCompiles)

option(YALAA_BUILD_EXAMPLES "Build the example programs" ON)
option(YALAA_ENABLE_TESTS "Build the unit tests (requires GTest)" OFF)

set(YALAA_IV_BACKEND "cxsc" CACHE STRING "Interval backend to use (cxsc, filib, profil_bias, custom)")
set_property(CACHE YALAA_IV_BACKEND PROPERTY STRINGS cxsc filib profil_bias custom)

# --- Boost (header-only usage: type_traits, utility, operators) ---
find_package(Boost 1.47 REQUIRED)

# --- Interval backend ---
string(TOLOWER "${YALAA_IV_BACKEND}" _yalaa_iv_backend)
if(_yalaa_iv_backend STREQUAL "cxsc")
  find_package(CXSC 2.5.0 REQUIRED)
  set(YALAA_HAVE_CXSC 1)
  set(YALAA_IV_TARGET CXSC::CXSC)
elseif(_yalaa_iv_backend STREQUAL "filib")
  find_package(FILIB REQUIRED)
  set(YALAA_HAVE_FILIB 1)
  set(YALAA_IV_TARGET FILIB::FILIB)
elseif(_yalaa_iv_backend STREQUAL "profil_bias")
  find_package(PROFIL_BIAS REQUIRED)
  set(YALAA_HAVE_PROFIL_BIAS 1)
  set(YALAA_IV_TARGET PROFIL_BIAS::PROFIL_BIAS)
elseif(_yalaa_iv_backend STREQUAL "custom")
  set(YALAA_HAVE_CUSTOM_IV_LIB 1)
  set(YALAA_IV_TARGET "")
else()
  message(FATAL_ERROR "Unknown YALAA_IV_BACKEND '${YALAA_IV_BACKEND}'. Expected cxsc, filib, profil_bias or custom.")
endif()

# --- long double vs. double precision (replaces AC_TYPE_LONG_DOUBLE_WIDER) ---
check_cxx_source_compiles(
  "static_assert(sizeof(long double) > sizeof(double), \"\");
   int main() { return 0; }"
  YALAA_HAVE_LONG_DOUBLE_WIDER
)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/yalaa-config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/generated/yalaa-config.h"
  @ONLY
)

add_subdirectory(src)

if(YALAA_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# --- Installable CMake package config, so consumers can find_package(yalaa) ---
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/yalaaConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/yalaaConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/yalaaConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/yalaa"
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/yalaaConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/yalaaConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/yalaa"
)

install(
  EXPORT yalaaTargets
  FILE yalaaTargets.cmake
  NAMESPACE yalaa::
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/yalaa"
)

install(
  FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindCXSC.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindFILIB.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindPROFIL_BIAS.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/yalaa"
)

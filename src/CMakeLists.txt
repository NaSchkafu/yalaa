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

add_library(yalaa
  helper/fphelper.cpp
  yalaa_fp_impl.cpp
)
add_library(yalaa::yalaa ALIAS yalaa)

target_compile_features(yalaa PUBLIC cxx_std_11)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(yalaa PUBLIC -msse2 -Wno-logical-op-parentheses)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(yalaa PUBLIC -frounding-math -mfpmath=sse -msse2)
else()
  message(WARNING "Unknown compiler '${CMAKE_CXX_COMPILER_ID}'. Please set flags for rounding math if necessary!")
endif()

target_include_directories(yalaa PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/yalaa>
)

if(YALAA_IV_TARGET)
  target_link_libraries(yalaa PUBLIC ${YALAA_IV_TARGET})
endif()

install(TARGETS yalaa
  EXPORT yalaaTargets
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install(FILES "${CMAKE_BINARY_DIR}/generated/yalaa-config.h"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/yalaa"
)

# Mirrors src/Makefile.am's nobase_include_HEADERS exactly (including the
# two extension-less legacy files) so the installed layout is unchanged.
set(YALAA_PUBLIC_HEADERS
  yalaa_assert.hpp
  helper/ivhelper_hpp
  helper/fphelper.hpp
  helper/fastia.hpp
  comb/affinecombopimpl.hpp
  comb/affinecombimpl.hpp
  comb/affinecombbaseimpl.hpp
  errortermimpl.hpp
  affineform_double.hpp
  yalaa_iv.hpp
  yalaa.hpp
  yalaa_ios.hpp
  affineform_fwd.hpp
  traits/l_double_traits.hpp
  traits/double_traits.hpp
  traits/float_traits.hpp
  traits/filib_traits.hpp
  traits/base_traits.hpp
  traits/cxsc_traits.hpp
  kernel/arithmeticerror.hpp
  kernel/aff/exacterroraffinefp.hpp
  kernel/exacterror.hpp
  kernel/nonaff/miscfp.hpp
  kernel/nonaff/minrangefp.hpp
  kernel/nonaff/mulfp.hpp
  kernel/nonaff/chebyshevfp.hpp
  specialterms.hpp
  pol/af1.hpp
  pol/af2.hpp
  pol/af0.hpp
  pol/errorpoldec.hpp
  pol/errorpolstd.hpp
  yalaa_fwd.hpp
  affineform.hpp
  affineform.inl
  kernel/arithmeticerror.inl
  pol/af0.inl
  pol/af2.inl
  pol/errorpoldec.inl
  pol/errorpolstd.inl
  pol/af1.inl
  affineform_double.inl
  errortermimpl.inl
  config_sel.h
  traits/profil_traits.hpp
  traits/custom_iv_traits.hpp
  traits/interval_traits.hpp
)

foreach(_yalaa_header ${YALAA_PUBLIC_HEADERS})
  get_filename_component(_yalaa_header_dir "${_yalaa_header}" DIRECTORY)
  install(FILES "${_yalaa_header}"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/yalaa/${_yalaa_header_dir}"
  )
endforeach()

if(YALAA_ENABLE_TESTS)
  find_package(GTest REQUIRED)

  add_executable(test_yalaa
    tests/ftmeta.cpp
    tests/test_main.cpp
  )
  target_link_libraries(test_yalaa PRIVATE yalaa GTest::gtest)

  enable_testing()
  add_test(NAME test_yalaa COMMAND test_yalaa)
endif()

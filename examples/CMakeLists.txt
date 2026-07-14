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

foreach(_yalaa_example function decorations policies abs polarity)
  add_executable(${_yalaa_example} ${_yalaa_example}.cpp)
  target_link_libraries(${_yalaa_example} PRIVATE yalaa)
endforeach()

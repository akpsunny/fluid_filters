#
#                 Copyright (c) 2020 Anivesh Kumar
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#   Author : Anivesh Kumar
#   Email  : anivesh.pandeya@gotomain.io
#   Date   : Mon Sep 1 12:00:35 IST 2020
#

cmake_minimum_required(VERSION 3.10)

#set project name
project(fluid_filters)
set(PROJECT_AUTHOR "Anivesh Kumar")
set(PROJECT_YEAR 2020)

find_package(Threads REQUIRED)

include(ExternalProject)
ExternalProject_Add(ext_liblimpid
    GIT_REPOSITORY  https://github.com/akpsunny/limpid.git
    GIT_TAG master
    SOURCE_DIR  ${CMAKE_BINARY_DIR}/liblimpid/src
    BINARY_DIR  ${CMAKE_BINARY_DIR}/liblimpid/build
    CONFIGURE_COMMAND   cmake ${CMAKE_BINARY_DIR}/liblimpid/src
    BUILD_COMMAND make
    INSTALL_COMMAND make install DESTDIR=${CMAKE_BINARY_DIR}/liblimpid/install
)
include_directories("${CMAKE_BINARY_DIR}/liblimpid/install/include")
link_directories("${CMAKE_BINARY_DIR}/liblimpid/install/lib")

#add the executables
add_executable(fluid_filters "src/main.c")
add_dependencies(fluid_filters ext_liblimpid)
target_link_libraries(fluid_filters PRIVATE limpid)
target_link_libraries(fluid_filters PRIVATE ${CMAKE_THREAD_LIBS_INIT})

#
# FastCGI wire protocol implementation in C.
#

cmake_minimum_required(VERSION 2.6)

project(cb64)

  # base paths to source files.
set(b64_path ${CMAKE_CURRENT_SOURCE_DIR}/code)
set(demo_path ${CMAKE_CURRENT_SOURCE_DIR}/demo)

  # core library and c++ wrappers.
file(GLOB b64_headers ${b64_path}/*.h ${b64_path}/*.hpp)
file(GLOB b64_sources ${b64_path}/*.c ${b64_path}/*.cpp)
add_library(b64
  STATIC ${b64_sources} ${b64_headers})

  # demo program.
include_directories(${b64_path})
set(demo_sources
  ${demo_path}/demo.cpp)
add_executable(demo ${demo_sources})
target_link_libraries(demo b64)

  # make sure b64 library is built first.
add_dependencies(demo b64)

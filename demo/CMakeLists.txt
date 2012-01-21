# simple demo program for cb64 library.

set(demo_sources
  ${CMAKE_CURRENT_SOURCE_DIR}/demo.cpp
)
add_executable(demo ${demo_sources})
target_link_libraries(demo b64)
add_dependencies(demo b64)

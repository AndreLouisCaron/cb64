# simple demo program for cb64 library.

set(sources
  demo.cpp
)
add_executable(demo ${sources})
target_link_libraries(demo b64 b64xx)
add_dependencies(demo b64 b64xx)

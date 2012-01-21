# cb64 library.

file(GLOB b64_headers *.h *.hpp)
file(GLOB b64_sources *.c *.cpp)
add_library(b64
  STATIC
  ${b64_sources}
  ${b64_headers}
)

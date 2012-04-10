# C interface.
set(headers
  b64.h
)
set(sources
  b64.c
)
add_library(b64
  STATIC ${sources} ${headers}
)

# C++ interface.
set(headers
  b64.hpp
)
set(sources
  b64.cpp
)
add_library(b64xx
  STATIC ${sources} ${headers}
)

#
# Base64 streaming/incremental parser in C.
#

cmake_minimum_required(VERSION 2.6)

project(cb64)

function(add_api_documentation target)
  if(DOXYGEN_EXECUTABLE)
    add_custom_target(
      ${target}
      COMMAND
        ${DOXYGEN_EXECUTABLE}
      WORKING_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT
        "Compiling documentation."
      VERBATIM
    )
  endif()
endfunction()

enable_testing()

# Put all libraries and executables in the build folder root.
set(LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

# Build main library.
add_subdirectory(code)

# Optional targets (skip when building as a dependency).
if(${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})

  # Resolve our own library headers.
  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/code
  )

  # Build demo projects.
  add_subdirectory(demo)

  # Build test suite.
  add_subdirectory(test)

  # Build API documentation.
  find_package(Doxygen QUIET)
  configure_file(
    ${CMAKE_SOURCE_DIR}/help/Doxyfile
    ${CMAKE_BINARY_DIR}/Doxyfile @ONLY
  )
  add_api_documentation(help)

endif()

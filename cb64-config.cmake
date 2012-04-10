# Library configuration file used by dependent projects
# via find_package() built-in directive in "config" mode.

if(NOT DEFINED cb64_FOUND)

  # Locate library headers.
  find_path(cb64_include_dirs
    NAMES b64.h
    PATHS ${cb64_DIR}/code
  )

  # Common name for exported library targets.
  set(cb64_libraries
    cb64
    cb64xx
    CACHE INTERNAL "cb64 library" FORCE
  )

  # Usual "required" et. al. directive logic.
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(
    cb64 DEFAULT_MSG
    cb64_include_dirs
    cb64_libraries
  )

  # Add targets to dependent project.
  add_subdirectory(
    ${cb64_DIR}
    ${CMAKE_BINARY_DIR}/cb64
  )
endif()

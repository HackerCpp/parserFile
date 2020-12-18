#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libzippp::libzippp" for configuration "Release"
set_property(TARGET libzippp::libzippp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libzippp::libzippp PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/libzippp.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libzippp.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS libzippp::libzippp )
list(APPEND _IMPORT_CHECK_FILES_FOR_libzippp::libzippp "${_IMPORT_PREFIX}/lib/libzippp.lib" "${_IMPORT_PREFIX}/bin/libzippp.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

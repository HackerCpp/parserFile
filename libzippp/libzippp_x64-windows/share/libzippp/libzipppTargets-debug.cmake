#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libzippp::libzippp" for configuration "Debug"
set_property(TARGET libzippp::libzippp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libzippp::libzippp PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/libzippp.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/libzippp.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS libzippp::libzippp )
list(APPEND _IMPORT_CHECK_FILES_FOR_libzippp::libzippp "${_IMPORT_PREFIX}/debug/lib/libzippp.lib" "${_IMPORT_PREFIX}/debug/bin/libzippp.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

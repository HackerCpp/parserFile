#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "zip" for configuration "Debug"
set_property(TARGET zip APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(zip PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/zip.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/zip.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS zip )
list(APPEND _IMPORT_CHECK_FILES_FOR_zip "${_IMPORT_PREFIX}/debug/lib/zip.lib" "${_IMPORT_PREFIX}/debug/bin/zip.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

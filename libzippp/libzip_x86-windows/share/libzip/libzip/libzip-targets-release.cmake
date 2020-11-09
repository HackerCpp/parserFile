#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "zip" for configuration "Release"
set_property(TARGET zip APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(zip PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/zip.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/zip.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS zip )
list(APPEND _IMPORT_CHECK_FILES_FOR_zip "${_IMPORT_PREFIX}/lib/zip.lib" "${_IMPORT_PREFIX}/bin/zip.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

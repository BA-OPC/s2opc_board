#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "s2opc_clientserver-loader-embedded" for configuration "RelWithDebInfo"
set_property(TARGET s2opc_clientserver-loader-embedded APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(s2opc_clientserver-loader-embedded PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libs2opc_clientserver-loader-embedded.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS s2opc_clientserver-loader-embedded )
list(APPEND _IMPORT_CHECK_FILES_FOR_s2opc_clientserver-loader-embedded "${_IMPORT_PREFIX}/lib/libs2opc_clientserver-loader-embedded.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

set (LIBUTF_FOUND FALSE)
set (LIBUTF_INCLUDE_DIRECTORY)
set (LIBUTF_INCLUDE_DIRECTORIES)
set (LIBUTF_LIBRARY)
set (LIBUTF_LIBRARIES)
set (LIBUTF_VERSION 4.0.1)

if (WIN32)
	set (LIBUTF_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_DIR}/..")
elseif (UNIX)
	set (LIBUTF_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_DIR}/../../..")
endif (WIN32)

find_path (LIBUTF_INCLUDE_DIRECTORY "libutf/version.h"
	PATHS "${LIBUTF_INSTALL_PREFIX}/include")

find_library (LIBUTF_LIBRARY "utf"
	PATHS "${LIBUTF_INSTALL_PREFIX}/bin"
	      "${LIBUTF_INSTALL_PREFIX}/lib")

if (LIBUTF_LIBRARY AND LIBUTF_INCLUDE_DIRECTORY)
	set (LIBUTF_FOUND TRUE)
	set (LIBUTF_INCLUDE_DIRECTORIES ${LIBUTF_INCLUDE_DIRECTORY})
	set (LIBUTF_LIBRARIES ${LIBUTF_LIBRARY})
endif (LIBUTF_LIBRARY AND LIBUTF_INCLUDE_DIRECTORY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args("libutf"
	FOUND_VAR
		LIBUTF_FOUND
	VERSION_VAR
		LIBUTF_VERSION
	REQUIRED_VARS
		LIBUTF_INCLUDE_DIRECTORY
		LIBUTF_INCLUDE_DIRECTORIES
		LIBUTF_LIBRARY
		LIBUTF_LIBRARIES)


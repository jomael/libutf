cmake_minimum_required(VERSION 2.6)

if (APPLE)
	set (CMAKE_MACOSX_RPATH 1)
endif (APPLE)

project(libutf)

set (LIBUTF_VERSION_MAJOR 4)
set (LIBUTF_VERSION_MINOR 0)
set (LIBUTF_VERSION_PATCH 1)
set (LIBUTF_VERSION "4.0.1")

add_subdirectory("include/libutf")
add_subdirectory("src")
add_subdirectory("doxygen")
add_subdirectory("examples")

if (WIN32)
	install(FILES "libutf-config.cmake"
		DESTINATION "cmake")
elseif (UNIX)
	install(FILES "libutf-config.cmake"
		DESTINATION "share/libutf/cmake")
endif (WIN32)

set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "A UTF-8, UTF-16, and UTF-32 encoder and decoder library for C89")
set (CPACK_PACKAGE_VENDOR "Taylor Holberton")
set (CPACK_PACKAGE_VERSION_MAJOR ${LIBUTF_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${LIBUTF_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${LIBUTF_VERSION_PATCH})
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_CONTACT "taylorcholberton@gmail.com")

include(CPack)

enable_testing()


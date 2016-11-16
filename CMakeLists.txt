cmake_minimum_required(VERSION 2.6)

project(libutf)

set (LIBUTF_VERSION_MAJOR 4)
set (LIBUTF_VERSION_MINOR 0)
set (LIBUTF_VERSION_PATCH 1)
set (LIBUTF_VERSION "4.0.1")

add_subdirectory("src")
add_subdirectory("doxygen")
add_subdirectory("examples")

install(FILES ${LIBUTF_HEADERS}
	DESTINATION "include/libutf")

set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "A UTF-8, UTF-16, and UTF-32 encoder and decoder library for C89")
set (CPACK_PACKAGE_VENDOR "Taylor Holberton")
set (CPACK_PACKAGE_VERSION_MAJOR ${LIBUTF_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${LIBUTF_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${LIBUTF_VERSION_PATCH})
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_CONTACT "taylorcholberton@gmail.com")

include(CPack)

enable_testing()


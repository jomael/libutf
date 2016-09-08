cmake_minimum_required(VERSION 2.6)

project(libutf)

set (LIBUTF_VERSION_MAJOR 4)
set (LIBUTF_VERSION_MINOR 0)
set (LIBUTF_VERSION_PATCH 0)
set (LIBUTF_VERSION "4.0.0")

if (CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_C_COMPILER}" STREQUAL "Clang")
	set (CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic")
elseif (MSVC)
	set (CMAKE_C_FLAGS "/W3 /WX")
endif (CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_C_COMPILER}" STREQUAL "Clang")

set (LIBUTF_HEADERS
	"converter.h"
	"decoder.h"
	"encoder.h"
	"error.h"
	"utf8.h"
	"utf16.h"
	"utf32.h")

set (LIBUTF_SOURCES
	"converter.c"
	"decoder.c"
	"encoder.c"
	"error.c"
	"utf8.c"
	"utf16.c"
	"utf32.c")

add_library("utf" SHARED ${LIBUTF_SOURCES})

set_target_properties("utf" PROPERTIES SOVERSION ${LIBUTF_VERSION})

find_package(Doxygen)
if (DOXYGEN_EXECUTABLE)
	add_custom_target("doc" ALL
		COMMAND ${DOXYGEN_EXECUTABLE}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Generating doxygen files")
	if (WIN32)
		install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/doxygen/html"
			DESTINATION "documentation")
	endif (WIN32)
	if (UNIX)
		install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/doxygen/man"
			DESTINATION "share")
	endif (UNIX)
endif (DOXYGEN_EXECUTABLE)

add_subdirectory("examples")

configure_file("libutf-config.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/libutf-config.cmake" @ONLY)

install(TARGETS
		"utf"
	EXPORT "libutfTargets"
	ARCHIVE DESTINATION "lib"
	LIBRARY DESTINATION "lib")

install(EXPORT "libutfTargets"
	DESTINATION "share/libutf/cmake")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libutf-config.cmake"
	DESTINATION "share/libutf/cmake")

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

function(ADD_UTF_TEST TEST_NAME)
	add_executable(${TEST_NAME} ${ARGN})
	target_link_libraries(${TEST_NAME} "utf")
	add_test(${TEST_NAME} ${TEST_NAME})
endfunction(ADD_UTF_TEST TEST_NAME)

add_utf_test("utf8-test" "utf8-test.c")
add_utf_test("utf16-test" "utf16-test.c")
add_utf_test("decoder-test" "decoder-test.c")
add_utf_test("encoder-test" "encoder-test.c")
add_utf_test("converter-test" "converter-test.c")


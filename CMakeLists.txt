cmake_minimum_required(VERSION 2.6)

project(utfx)

set (UTFX_VERSION_MAJOR 2)
set (UTFX_VERSION_MINOR 1)
set (UTFX_VERSION_PATCH 1)

if (CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_C_COMPILER}" STREQUAL "Clang")
	set (CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic")
elseif (MSVC)
	set (CMAKE_CXX_FLAGS "/Wall /WX /EHsc")
	set (CMAKE_C_FLAGS "/Wall /WX")
	set (CMAKE_C_FLAGS_RELEASE "/wd4710 /wd4711")
endif (CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_C_COMPILER}" STREQUAL "Clang")

if (CMAKE_COMPILER_IS_GNUCXX OR ${CMAKE_CXX_COMPILER} STREQUAL "Clang")
	set (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -std=c++11")
endif (CMAKE_COMPILER_IS_GNUCXX OR ${CMAKE_CXX_COMPILER} STREQUAL "Clang")

set (UTFX_HEADERS
	"decoder.h"
	"encoder.h"
	"encoder.hpp"
	"error.h"
	"stl.hpp"
	"utf8.h"
	"utf16.h"
	"utf32.h")

set (UTFX_SOURCES
	"decoder.c"
	"encoder.c"
	"encoder.cpp"
	"error.c"
	"stl.cpp"
	"utf8.c"
	"utf16.c"
	"utf32.c")

add_library("utfx" ${UTFX_SOURCES})

find_package(Doxygen)
if (DOXYGEN_EXECUTABLE)
	add_custom_target("doc" ALL
		COMMAND ${DOXYGEN_EXECUTABLE}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Generating doxygen files")
	if (WIN32)
		install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/doc/html"
			DESTINATION "documentation")
	endif (WIN32)
	if (UNIX)
		install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/doc/man"
			DESTINATION "share")
	endif (UNIX)
endif (DOXYGEN_EXECUTABLE)

add_subdirectory("examples")

configure_file("utfx-config.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/utfx-config.cmake" @ONLY)

install(TARGETS "utfx"
	EXPORT "utfxTargets"
	ARCHIVE DESTINATION "lib"
	LIBRARY DESTINATION "lib")

install(EXPORT "utfxTargets"
	DESTINATION "share/utfx/cmake")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/utfx-config.cmake"
	DESTINATION "share/utfx/cmake")

install(FILES ${UTFX_HEADERS}
	DESTINATION "include/utfx")

set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "A UTF-8, UTF-16, and UTF-32 encoder and decoder library for C")
set (CPACK_PACKAGE_VENDOR "Taylor Holberton")
set (CPACK_PACKAGE_VERSION_MAJOR ${UTFX_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${UTFX_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${UTFX_VERSION_PATCH})
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR ${UTFX_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${UTFX_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${UTFX_VERSION_PATCH})
set (CPACK_PACKAGE_CONTACT "taylorcholberton@gmail.com")

include(CPack)

enable_testing()

function(ADD_UTFX_TEST TEST_NAME)
	add_executable(${TEST_NAME} ${ARGN})
	target_link_libraries(${TEST_NAME} "utfx")
	add_test(${TEST_NAME} ${TEST_NAME})
endfunction(ADD_UTFX_TEST TEST_NAME)

add_utfx_test("utf8-test" "utf8-test.c")

add_utfx_test("utf16-test" "utf16-test.c")

add_utfx_test("encoder-test" "encoder-test.cpp")


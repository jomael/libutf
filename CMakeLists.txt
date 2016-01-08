cmake_minimum_required(VERSION 2.6)

project(utfx)

if (CMAKE_COMPILER_IS_GNUCC)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wfatal-errors")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic")
elseif (MSVC)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Wall")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /WX")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4710")
endif (CMAKE_COMPILER_IS_GNUCC)

add_library("utfx" "utf8.c")

configure_file("utfx-config.cmake.in"
	"utfx-config.cmake" @ONLY)

install(TARGETS "utfx"
	EXPORT "utfxTargets"
	ARCHIVE DESTINATION "lib"
	LIBRARY DESTINATION "lib")

install(EXPORT "utfxTargets"
	DESTINATION "share/utfx/cmake")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/utfx-config.cmake"
	DESTINATION "share/utfx/cmake")

install(FILES "utf8.h"
	DESTINATION "include/utfx")

set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "A UTF-8 encoder and decoder library for C")
set (CPACK_PACKAGE_VENDOR "Taylor Holberton")
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR ${GCOLLECTOR_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${GCOLLECTOR_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${GCOLLECTOR_VERSION_PATCH})
set (CPACK_PACKAGE_CONTACT "taylorcholberton@gmail.com")

include(CPack)

enable_testing()

add_executable("utf8-test" "utf8-test.c")

target_link_libraries("utf8-test" "utfx")

add_test("utf8-test" "utf8-test")

find_package(Doxygen)
if (DOXYGEN_EXECUTABLE)
	add_custom_target("doc" ALL
		COMMAND ${DOXYGEN_EXECUTABLE}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Generating doxygen files")
endif (DOXYGEN_EXECUTABLE)


cmake_minimum_required(VERSION 2.6)

include_directories(${PROJECT_SOURCE_DIR})

function (ADD_UTFX_EXAMPLE EXAMPLE_NAME)
	add_executable(${EXAMPLE_NAME} ${ARGN})
	target_link_libraries(${EXAMPLE_NAME} "utfx")
endfunction (ADD_UTFX_EXAMPLE EXAMPLE_NAME)

add_utfx_example("sigma" "sigma.c")

add_utfx_example("iconv" "iconv.c")

add_utfx_example("iconvpp" "iconv.cpp")


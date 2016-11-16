cmake_minimum_required(VERSION 2.6)

include_directories("../include")

function (ADD_LIBUTF_EXAMPLE EXAMPLE_NAME)
	add_executable(${EXAMPLE_NAME} ${ARGN})
	target_link_libraries(${EXAMPLE_NAME} "utf-static")
endfunction (ADD_LIBUTF_EXAMPLE EXAMPLE_NAME)

add_libutf_example("sigma" "sigma.c")
add_libutf_example("iconv" "iconv.c")


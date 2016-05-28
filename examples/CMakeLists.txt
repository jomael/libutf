cmake_minimum_required(VERSION 2.6)

include_directories(${PROJECT_SOURCE_DIR})

add_executable("iconv" "iconv.c")

target_link_libraries("iconv" "utfx")


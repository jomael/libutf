cmake_minimum_required(VERSION 2.6)

include(TestBigEndian)

test_big_endian(LIBUTF_BIG_ENDIAN)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/config.h")

install(FILES
	"converter.h"
	"decoder.h"
	"encoder.h"
	"error.h"
	"ifstream.h"
	"istream.h"
	"iterator.h"
	"libutf.h"
	"ofstream.h"
	"ostream.h"
	"stream.h"
	"string.h"
	"utf8.h"
	"utf16.h"
	"utf32.h"
	"version.h"
	DESTINATION "include/libutf")


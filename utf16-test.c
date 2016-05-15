#include "utf16.h"

#include <assert.h>

static void test_encode_length(void);

int main(void){
	test_encode_length();
	return 0;
}

static void test_encode_length_be(void);

static void test_encode_length(void){
	test_encode_length_be();
}

static void test_encode_length_be(void){
	assert(utf16_encode_length(0x00000000) == 1);
	assert(utf16_encode_length(0x00000001) == 1);
	assert(utf16_encode_length(0x0000FFFF) == 1);
	assert(utf16_encode_length(0x00010000) == 2);
	assert(utf16_encode_length(0x7FFFFFFF) == 2);
	assert(utf16_encode_length(0x80000000) == -1);
	assert(utf16_encode_length(0xFFFFFFFF) == =1);
}


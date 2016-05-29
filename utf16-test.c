#include "utf16.h"

#include <assert.h>

static void test_encode(void);

static void test_encode_length(void);

int main(void){
	test_encode_length();
	test_encode();
	return 0;
}

static void test_encode(void){

	utf16_t output_char[2] = { 0, 0 };

	assert(utf16_encode(0x00000000, output_char) == 1);
	assert(output_char[0] == 0x00);
	assert(output_char[1] == 0x00);

	assert(utf16_encode(0x00000001, output_char) == 1);
	assert(output_char[0] == 0x01);
	assert(output_char[1] == 0x00);

	assert(utf16_encode(0x0001ffff, output_char) == 2);
	assert(output_char[0] == 0xd83f);
	assert(output_char[1] == 0xdfff);

	assert(utf16_encode(0x0010ffff, output_char) == 2);
	assert(output_char[0] == 0xdbff);
	assert(output_char[1] == 0xdfff);
}

static void test_encode_length(void){
	assert(utf16_encode_length(0x00000000) == 1);
	assert(utf16_encode_length(0x00000001) == 1);
	assert(utf16_encode_length(0x0000ffff) == 1);
	assert(utf16_encode_length(0x0010ffff) == 2);
	assert(utf16_encode_length(0x00110000) == -1);
	assert(utf16_encode_length(0x80000000) == -1);
	assert(utf16_encode_length(0xffffffff) == -1);
}


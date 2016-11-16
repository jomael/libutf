#include "utf16.h"

#include <assert.h>

static void test_decode(void);

static void test_decode_length(void);

static void test_encode(void);

static void test_encode_length(void);

static void test_utf16be(void);

static void test_utf16le(void);

static void test_strlen(void);

int main(void){
	test_decode_length();
	test_decode();
	test_encode_length();
	test_encode();
	test_utf16be();
	test_utf16le();
	test_strlen();
	return 0;
}

static void test_decode(void){

	utf32_t output_char = 0x00;

	utf16_t input_char[2] = { 0x00, 0x00 };

	input_char[0] = 0x00;
	input_char[1] = 0x00;
	assert(utf16_decode(input_char, &output_char) == 1);
	assert(output_char == 0x00);

	input_char[0] = 0x01;
	input_char[1] = 0x00;
	assert(utf16_decode(input_char, &output_char) == 1);
	assert(output_char == 0x01);

	input_char[0] = 0xd83f;
	input_char[1] = 0xdfff;
	assert(utf16_decode(input_char, &output_char) == 2);
	assert(output_char == 0x01ffff);

	input_char[0] = 0xdbff;
	input_char[1] = 0xdfff;
	assert(utf16_decode(input_char, &output_char) == 2);
	assert(output_char == 0x10ffff);
}

static void test_decode_length(void){
	assert(utf16_decode_length(0x00) == 1);
	assert(utf16_decode_length(0x01) == 1);
	assert(utf16_decode_length(0xd83f) == 2);
	assert(utf16_decode_length(0xdbff) == 2);
	assert(utf16_decode_length(0xdc00) == 0);
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
	assert(utf16_encode_length(0x00110000) == 0);
	assert(utf16_encode_length(0x80000000) == 0);
	assert(utf16_encode_length(0xffffffff) == 0);
}

static void test_utf16be(void){
	utf16_t out16 = 0;

	out16 = utf16be("\x01\x00");
	assert(out16 == 0x0100);

	out16 = utf16be("\x00\x01");
	assert(out16 == 0x0001);
}

static void test_utf16le(void){
	utf16_t out16 = 0;

	out16 = utf16le("\x00\x01");
	assert(out16 == 0x0100);

	out16 = utf16be("\x00\x01");
	assert(out16 == 0x0001);
}

static void test_strlen(void){
	const utf16_t in[] = {
		0xD801, 0xDC37,
		0x20AC,
		0xD852, 0xDF62 };
	assert(utf16_strlen(in, sizeof(in) / sizeof(in[0])) == 3);
}


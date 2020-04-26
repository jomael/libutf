#include <libutf/utf8.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void test_decode(void);

static void test_encode(void);

int main(void){
	test_decode();
	test_encode();
	return EXIT_SUCCESS;
}

static void test_decode(void){
	char in[] = u8"ó";
	char32_t out;
	assert(utf8_decode_length(in[0]) == (sizeof(in) - 1));
	assert(utf8_decode(in, &out) == (sizeof(in) - 1));
	assert(out == U'ó');
}

static void test_encode(void){
	char out[4];
	char out_expected[] = u8"ó";
	assert(utf8_encode_length(U'ó') == (sizeof(out_expected) - 1));
	assert(utf8_encode(U'ó', out) == (sizeof(out_expected) - 1));
	assert(memcmp(out, out_expected, sizeof(out_expected) - 1) == 0);
}


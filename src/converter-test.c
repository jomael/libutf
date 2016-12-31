#include <libutf/converter.h>

#include <assert.h>

static void test_utf8_to_utf16be(void);

int main(void){
	test_utf8_to_utf16be();
	return 0;
}

static void test_utf8_to_utf16be(void){

	unsigned int read_count = 0;

	unsigned int write_count = 0;

	/* UTF-32LE : 00 01 04 37 */
	/* UTF-16BE : D8 01 DC 37 */
	/* UTF-8    : F0 90 90 B7 */
	const unsigned char input[4] = {
		0xF0, 0x90, 0x90, 0xB7 };

	unsigned char output[4] = {
		0x00, 0x00, 0x00, 0x00 };

	utf_converter_t converter;

	utf_converter_init(&converter);

	utf_converter_set_encoder_mode(&converter, UTF_ENCODER_MODE_UTF16_BE);

	write_count = utf_converter_write(&converter, input, sizeof(input));
	assert(write_count == 4);

	read_count = utf_converter_read(&converter, output, sizeof(output));
	assert(read_count == 4);
	assert(output[0] == 0xD8);
	assert(output[1] == 0x01);
	assert(output[2] == 0xDC);
	assert(output[3] == 0x37);

	utf_converter_free(&converter);
}


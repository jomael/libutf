#include <libutf/decoder.h>

#include <assert.h>

static void test_utf16be(void);

int main(void){
	test_utf16be();
	return 0;
}

static void test_utf16be(void){

	/* UTF-32LE : 00 02 4B 62 */
	/* UTF-16BE : D8 52 DF 62 */

	utf_error_t error;

	unsigned int write_count = 0;

	utf32_t output = 0;

	utf_decoder_t decoder;

	utf_decoder_state_t state = UTF_DECODER_STATE_READING;

	utf_decoder_init(&decoder);
	
	utf_decoder_set_mode(&decoder, UTF_DECODER_MODE_UTF16_BE);

	state = utf_decoder_get_state(&decoder);
	assert(state == UTF_DECODER_STATE_READING);

	write_count = utf_decoder_write(&decoder, "\xd8", 1);
	assert(write_count == 1);

	state = utf_decoder_get_state(&decoder);
	assert(state == UTF_DECODER_STATE_READING);

	write_count = utf_decoder_write(&decoder, "\x52", 1);
	assert(write_count == 1);

	state = utf_decoder_get_state(&decoder);
	assert(state == UTF_DECODER_STATE_READING);

	write_count = utf_decoder_write(&decoder, "\xdf", 1);
	assert(write_count == 1);

	state = utf_decoder_get_state(&decoder);
	assert(state == UTF_DECODER_STATE_READING);

	write_count = utf_decoder_write(&decoder, "\x62", 1);
	assert(write_count == 1);
	
	state = utf_decoder_get_state(&decoder);
	assert(state == UTF_DECODER_STATE_WRITING);

	error = utf_decoder_read(&decoder, &output);
	assert(error == UTF_ERROR_NONE);
	assert(output == 0x00024b62);
}


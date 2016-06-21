#include "decoder.h"

#include <assert.h>

static void test_utf16be(void);

int main(void){
	test_utf16be();
	return 0;
}

static void test_utf16be(void){

	/* UTF-32LE : 00 02 4B 62 */
	/* UTF-16BE : D8 52 DF 62 */

	utfx_error_t error;

	unsigned int write_count = 0;

	utf32_t output = 0;

	utfx_decoder_t decoder;

	utfx_decoder_state_t state = UTFX_DECODER_STATE_READING;

	utfx_decoder_init(&decoder);
	
	utfx_decoder_set_mode(&decoder, UTFX_DECODER_MODE_UTF16_BE);

	state = utfx_decoder_get_state(&decoder);
	assert(state == UTFX_DECODER_STATE_READING);

	write_count = utfx_decoder_write(&decoder, "\xd8", 1);
	assert(write_count == 1);

	state = utfx_decoder_get_state(&decoder);
	assert(state == UTFX_DECODER_STATE_READING);

	write_count = utfx_decoder_write(&decoder, "\x52", 1);
	assert(write_count == 1);

	state = utfx_decoder_get_state(&decoder);
	assert(state == UTFX_DECODER_STATE_READING);

	write_count = utfx_decoder_write(&decoder, "\xdf", 1);
	assert(write_count == 1);

	state = utfx_decoder_get_state(&decoder);
	assert(state == UTFX_DECODER_STATE_READING);

	write_count = utfx_decoder_write(&decoder, "\x62", 1);
	assert(write_count == 1);
	
	state = utfx_decoder_get_state(&decoder);
	assert(state == UTFX_DECODER_STATE_WRITING);

	error = utfx_decoder_read_output(&decoder, &output);
	assert(error == UTFX_ERROR_NONE);
	assert(output == 0x00024b62);
}


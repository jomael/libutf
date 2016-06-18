#include "encoder.h"

#include <assert.h>

static void test_utf8(void);

int main(void){
	test_utf8();
	return 0;
}

static void test_utf8(void){

	unsigned char encoded_byte = 0;

	unsigned int read_count = 0;

	utfx_encoder_t encoder;

	/* should default to UTF-8 */
	assert(utfx_encoder_get_mode(&encoder) == UTFX_ENCODER_MODE_UTF8);

	/* should start in a reading state */
	assert(utfx_encoder_get_state(&encoder) == UTFX_ENCODER_STATE_READING);

	/* writes symbol 'delta' */
	/* UTF-32 : 0x0394       */
	/* UTF-8  : 0xce, 0x94   */
	utfx_encoder_write(&encoder, 0x0394);

	/* now that data has been written, should be in a writing state */
	assert(utfx_encoder_get_state(&encoder) == UTFX_ENCODER_STATE_WRITING);

	read_count = utfx_encoder_read(&encoder, &encoded_byte, 1);
	assert(read_count == 1);
	assert(encoded_byte == 0xce);

	/* should be in a writing state, still */
	assert(utfx_encoder_get_state(&encoder) == UTFX_ENCODER_STATE_WRITING);

	read_count = utfx_encoder_read(&encoder, &encoded_byte, 1);
	assert(read_count == 1);
	assert(encoded_byte == 0x94);

	/* there should be no more data letft */
	read_count = utfx_encoder_read(&encoder, &encoded_byte, 1);
	assert(read_count == 0);

	/* should be back in a reading state */
	assert(utfx_encoder_get_state(&encoder) == UTFX_ENCODER_STATE_READING);
} /* namespace */


#include "encoder.h"

#include "utf8.h"
#include "utf16.h"

void utfx_encoder_init(utfx_encoder_t * encoder){
	encoder->mode = UTFX_ENCODER_MODE_NONE;
	encoder->byte_array[0] = 0;
	encoder->byte_array[1] = 0;
	encoder->byte_array[2] = 0;
	encoder->byte_array[3] = 0;
	encoder->byte_count = 0;
}

void utfx_encoder_set_mode(utfx_encoder_t * encoder, int mode){
	encoder->mode = mode;
}

int utfx_encoder_put_input_char(utfx_encoder_t * encoder, utf32_t input_char){
	if (encoder->mode == UTFX_ENCODER_MODE_NONE){
		return -1;
	} else if (encoder->mode == UTFX_ENCODER_MODE_UTF8){
		return utf8_encode(encoder->byte_array, input_char);
	}
	/* not implemented */
	return -2;
}

int utfx_encoder_get_output_char(const utfx_encoder_t * encoder, void * output_char){
	(void) encoder;
	(void) output_char;
	/* not implemented */
	return -2;
}

int utfx_encoder_get_output_size(const utfx_encoder_t * encoder){
	(void) encoder;
	/* not implemented */
	return -2;
}


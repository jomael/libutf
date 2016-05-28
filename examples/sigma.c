#include <stdio.h>

#include "encoder.h"
#include "utf8.h"

int main(void){

	unsigned int output_length = 0;

	utfx_encoder_t encoder;

	utf32_t input_char = 0x03A3;

	utf8_t output_char[4];

	utfx_encoder_init(&encoder);

	utfx_encoder_set_mode(&encoder, UTFX_ENCODER_MODE_UTF8);

	utfx_encoder_put_input_char(&encoder, input_char);

	output_length = utfx_encoder_get_output_char(&encoder, output_char);

	fprintf(stdout, "sigma: %.*s\n", output_length, output_char);

	return 0;
}


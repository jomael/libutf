#include <stdio.h>

#ifdef _MSC_VER
/* on /Wall, it warns that fprintf is not inlined */
/* so, it's basically pointless */
#pragma warning(disable : 4710)
#endif /* _MSC_VER */

#include <libutf/encoder.h>
#include <libutf/utf8.h>

int main(void){

	unsigned int output_length = 0;

	utf_encoder_t encoder;

	utf32_t input_char = 0x03A3;

	utf8_t output_char[4];

	utf_encoder_init(&encoder);

	utf_encoder_set_codec(&encoder, UTF_CODEC_UTF8);

	utf_encoder_write(&encoder, input_char);

	output_length = utf_encoder_read(&encoder, output_char, sizeof(output_char));

	fprintf(stdout, "sigma: %.*s\n", output_length, output_char);

	return 0;
}


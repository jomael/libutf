#ifndef UTFX_ENCODER_H
#define UTFX_ENCODER_H

#include "utf32.h"

enum {
	UTFX_ENCODER_MODE_NONE = 0,
	UTFX_ENCODER_MODE_UTF8,
	UTFX_ENCODER_MODE_UTF16_LE,
	UTFX_ENCODER_MODE_UTF16_BE,
	UTFX_ENCODER_MODE_UTF32_LE,
	UTFX_ENCODER_MODE_UTF32_BE
};

typedef struct {
	int mode;
	unsigned char byte_array[4];
	unsigned int byte_count;
} utfx_encoder_t;

void utfx_encoder_init(utfx_encoder_t * encoder);

void utfx_encoder_set_mode(utfx_encoder_t * encoder, int output_mode);

int utfx_encoder_put_input_char(utfx_encoder_t * encoder, utf32_t input_char);

int utfx_encoder_get_output_char(const utfx_encoder_t * encoder, void * output_char);

int utfx_encoder_get_output_size(const utfx_encoder_t * encoder);

#endif /* UTFX_ENCODER_H */


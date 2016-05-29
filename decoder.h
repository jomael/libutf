/*
 *    This file is part of Utfx.
 *
 *    Utfx is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    Utfx is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Utfx.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UTFX_DECODER_H
#define UTFX_DECODER_H

#include "utf32.h"

typedef enum utfx_decoder_mode {
	UTFX_DECODER_MODE_NONE = 0,
	UTFX_DECODER_MODE_UTF8,
	UTFX_DECODER_MODE_UTF16_LE,
	UTFX_DECODER_MODE_UTF16_BE,
	UTFX_DECODER_MODE_UTF32_LE,
	UTFX_DECODER_MODE_UTF32_BE,
	UTFX_DECODER_MODE_UNKNOWN = -1
} utfx_decoder_mode_t;

typedef struct {
	utfx_decoder_mode_t mode;
	utf32_t output_char;
} utfx_decoder_t;

void utfx_decoder_init(utfx_decoder_t * decoder);

void utfx_decoder_set_mode(utfx_decoder_t * decoder, utfx_decoder_mode_t mode);

int utfx_decoder_put_input_char(utfx_decoder_t * decoder, const void * input_char);

int utfx_decoder_put_input_char_safely(utfx_decoder_t * decoder, const void * input_char, unsigned int input_size);

int utfx_decoder_get_output_char(const utfx_decoder_t * decoder, utf32_t * output_char);

#endif /* UTFX_DECODER_H */


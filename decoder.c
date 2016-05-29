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

#include "decoder.h"

#include "utf8.h"
#include "utf16.h"

void utfx_decoder_init(utfx_decoder_t * decoder){
	decoder->mode = UTFX_DECODER_MODE_NONE;
	decoder->output_char = 0;
}

void utfx_decoder_set_mode(utfx_decoder_t * decoder, utfx_decoder_mode_t mode){
	decoder->mode = mode;
}

utfx_error_t utfx_decoder_get_input_size(utfx_decoder_t * decoder, const void * input_char, unsigned int * input_size){

	if (decoder->mode == UTFX_DECODER_MODE_NONE){
		return UTFX_ERROR_MODE_NOT_SET;
	}

	if (decoder->mode == UTFX_DECODER_MODE_UTF8){
		*input_size = utf8_decode_length(*(const utf8_t *)(input_char));
		return UTFX_ERROR_NONE;
	}

	if (decoder->mode == UTFX_DECODER_MODE_UTF16_LE){
		unsigned int input_size_tmp = 0;
		utf16_t input_code = 0;
		const unsigned char * input_byte_array = (const unsigned char *)(input_char);
		input_code  = input_byte_array[0] << 0x00;
		input_code |= input_byte_array[1] << 0x08;
		input_size_tmp = utf16_decode_length(input_code) * 2;
		if (!input_size_tmp){
			return UTFX_ERROR_INVALID_SEQUENCE;
		} else {
			*input_size = input_size_tmp;
		}
		return UTFX_ERROR_NONE;
	}

	if (decoder->mode == UTFX_DECODER_MODE_UTF16_BE){
		unsigned int input_size_tmp = 0;
		utf16_t input_code = 0;
		const unsigned char * input_byte_array = (const unsigned char *)(input_char);
		input_code  = input_byte_array[0] << 0x08;
		input_code |= input_byte_array[1] << 0x00;
		input_size_tmp = utf16_decode_length(input_code) * 2;
		if (!input_size_tmp){
			return UTFX_ERROR_INVALID_SEQUENCE;
		} else {
			*input_size = input_size_tmp;
		}
		return UTFX_ERROR_NONE;
	}

	if (decoder->mode == UTFX_DECODER_MODE_UTF32_LE
	 || decoder->mode == UTFX_DECODER_MODE_UTF32_BE){
		*input_size = 4;
		return UTFX_ERROR_NONE;
	}

	return UTFX_ERROR_INVALID_MODE;
}

int utfx_decoder_put_input_char(utfx_decoder_t * decoder, const void * input_char){

	int result = 0;

	if (decoder->mode == UTFX_DECODER_MODE_NONE){
		return -1;
	} else if (decoder->mode == UTFX_DECODER_MODE_UTF8){
		result = utf8_decode((const utf8_t *)(input_char), &decoder->output_char);
	} else if (decoder->mode == UTFX_DECODER_MODE_UTF16_LE){

		const unsigned char * input_byte_array = (const unsigned char *)(input_char);

		utf16_t input_char_utf16[2] = { 0, 0 };

		int input_char_size = 0;

		input_char_utf16[0]  = input_byte_array[0] << 0x00;
		input_char_utf16[0] |= input_byte_array[1] << 0x08;

		input_char_size = utf16_decode_length(input_char_utf16[0]);
		if (input_char_size < 0){
			return -1;
		} else if (input_char_size == 2){
			input_char_utf16[1]  = input_byte_array[2] << 0x00;
			input_char_utf16[1] |= input_byte_array[3] << 0x08;
		}

		result = utf16_decode(input_char_utf16, &decoder->output_char);
		if (result > 0){
			/* result should be the number of bytes decoded */
			result *= 2;
		}

	} else if (decoder->mode == UTFX_DECODER_MODE_UTF16_BE){

		const unsigned char * input_byte_array = (const unsigned char *)(input_char);

		utf16_t input_char_utf16[2] = { 0, 0 };

		int input_char_size = 0;

		input_char_utf16[0]  = input_byte_array[0] << 0x08;
		input_char_utf16[0] |= input_byte_array[1] << 0x00;

		input_char_size = utf16_decode_length(input_char_utf16[0]);
		if (input_char_size < 0){
			return -1;
		} else if (input_char_size == 2){
			input_char_utf16[1]  = input_byte_array[2] << 0x08;
			input_char_utf16[1] |= input_byte_array[3] << 0x00;
		}

		result = utf16_decode(input_char_utf16, &decoder->output_char);
		if (result > 0){
			/* result should be the number of bytes decoded */
			result *= 2;
		}

	} else {
		/* not implemented */
		result = -2;
	}

	return result;
}

int utfx_decoder_put_input_char_safely(utfx_decoder_t * decoder, const void * input_char, unsigned int input_size){

	unsigned int expected_input_size = 0;

	if (!input_char || input_size == 0){
		return -1;
	}

	if (decoder->mode == UTFX_DECODER_MODE_UTF8){

		expected_input_size = utf8_decode_length(*(char *)(input_char));
		if (expected_input_size > input_size){
			/* not enough bytes from input_char */
			return -3;
		}

	} else if (decoder->mode == UTFX_DECODER_MODE_UTF16_LE){

		const unsigned char * input_byte_array = (const unsigned char *)(input_char);

		utf16_t input_char_utf16[2] = { 0, 0 };

		int input_char_size = 0;

		input_char_utf16[0]  = input_byte_array[0] << 0x00;
		input_char_utf16[0] |= input_byte_array[1] << 0x08;

		input_char_size = utf16_decode_length(input_char_utf16[0]);
		if (input_char_size < 0){
			return -1;
		} else if ((unsigned int)(input_char_size) > input_size){
			return -1;
		}

	} else if (decoder->mode == UTFX_DECODER_MODE_UTF16_BE){

		const unsigned char * input_byte_array = (const unsigned char *)(input_char);

		utf16_t input_char_utf16[2] = { 0, 0 };

		int input_char_size = 0;

		input_char_utf16[0]  = input_byte_array[0] << 0x08;
		input_char_utf16[0] |= input_byte_array[1] << 0x00;

		input_char_size = utf16_decode_length(input_char_utf16[0]);
		if (input_char_size < 0){
			return -1;
		} else if ((unsigned int)(input_char_size) > input_size){
			return -1;
		}

	} else {
		/* unsupported mode */
		return -2;
	}

	return utfx_decoder_put_input_char(decoder, input_char);
}

int utfx_decoder_get_output_char(const utfx_decoder_t * decoder, utf32_t * output_char){

	if (decoder->output_char <= utf32_max
	 && decoder->output_char >= utf32_min){
		*output_char = decoder->output_char;
	} else {
		return -1;
	}

	return 0;
}


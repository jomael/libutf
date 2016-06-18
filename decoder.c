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
	decoder->input_byte_array[0] = 0;
	decoder->input_byte_array[1] = 0;
	decoder->input_byte_array[2] = 0;
	decoder->input_byte_array[3] = 0;
	decoder->input_byte_count = 0;
	decoder->mode = UTFX_DECODER_MODE_UTF8;
	decoder->output_char = 0;
	decoder->state = UTFX_DECODER_STATE_ACCEPTING_WRITE;
}

utfx_decoder_mode_t utfx_decoder_get_mode(const utfx_decoder_t * decoder){
	return decoder->mode;
}

utfx_error_t utfx_decoder_get_input_size(utfx_decoder_t * decoder, const void * input_char, unsigned int * input_size){

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

utf32_t utfx_decoder_get_output_char(const utfx_decoder_t * decoder){
	return decoder->output_char;
}

utfx_decoder_state_t utfx_decoder_get_state(const utfx_decoder_t * decoder){
	return decoder->state;
}

utfx_error_t utfx_decoder_put_input_char(utfx_decoder_t * decoder, const void * input_char){

	int result = 0;

	if (decoder->mode == UTFX_DECODER_MODE_UTF8){

		result = utf8_decode((const utf8_t *)(input_char), &decoder->output_char);
		if (!result){
			return UTFX_ERROR_INVALID_SEQUENCE;
		}

	} else if (decoder->mode == UTFX_DECODER_MODE_UTF16_LE){

		const unsigned char * input_byte_array = (const unsigned char *)(input_char);

		utf16_t input_char_utf16[2] = { 0, 0 };

		unsigned int input_char_size = 0;

		input_char_utf16[0]  = input_byte_array[0] << 0x00;
		input_char_utf16[0] |= input_byte_array[1] << 0x08;

		input_char_size = utf16_decode_length(input_char_utf16[0]);
		if (!input_char_size){
			return UTFX_ERROR_INVALID_SEQUENCE;
		} else if (input_char_size == 2){
			input_char_utf16[1]  = input_byte_array[2] << 0x00;
			input_char_utf16[1] |= input_byte_array[3] << 0x08;
		}

		result = utf16_decode(input_char_utf16, &decoder->output_char);
		if (!result){
			return UTFX_ERROR_INVALID_SEQUENCE;
		}

	} else if (decoder->mode == UTFX_DECODER_MODE_UTF16_BE){

		const unsigned char * input_byte_array = (const unsigned char *)(input_char);

		utf16_t input_char_utf16[2] = { 0, 0 };

		unsigned int input_char_size = 0;

		input_char_utf16[0]  = input_byte_array[0] << 0x08;
		input_char_utf16[0] |= input_byte_array[1] << 0x00;

		input_char_size = utf16_decode_length(input_char_utf16[0]);
		if (!input_char_size){
			return UTFX_ERROR_INVALID_SEQUENCE;
		} else if (input_char_size == 2){
			input_char_utf16[1]  = input_byte_array[2] << 0x08;
			input_char_utf16[1] |= input_byte_array[3] << 0x00;
		}

		result = utf16_decode(input_char_utf16, &decoder->output_char);
		if (!result){
			return UTFX_ERROR_INVALID_SEQUENCE;
		}

	} else if (decoder->mode == UTFX_DECODER_MODE_UTF32_LE){
		const unsigned char * byte_array = (const unsigned char *)(input_char);
		decoder->output_char  = (byte_array[0] & 0xff) << 0x00;
		decoder->output_char |= (byte_array[1] & 0xff) << 0x08;
		decoder->output_char |= (byte_array[2] & 0xff) << 0x10;
		decoder->output_char |= (byte_array[3] & 0xff) << 0x18;
	} else if (decoder->mode == UTFX_DECODER_MODE_UTF32_BE){
		const unsigned char * byte_array = (const unsigned char *)(input_char);
		decoder->output_char  = (byte_array[0] & 0xff) << 0x18;
		decoder->output_char |= (byte_array[1] & 0xff) << 0x10;
		decoder->output_char |= (byte_array[2] & 0xff) << 0x08;
		decoder->output_char |= (byte_array[3] & 0xff) << 0x00;
	} else {
		return UTFX_ERROR_INVALID_MODE;
	}

	return UTFX_ERROR_NONE;
}

utfx_error_t utfx_decoder_put_input_char_safely(utfx_decoder_t * decoder, const void * input_char, unsigned int input_size){

	utfx_error_t error = UTFX_ERROR_NONE;

	unsigned int expected_input_size = 0;

	error = utfx_decoder_get_input_size(decoder, input_char, &expected_input_size);
	if (error != UTFX_ERROR_NONE){
		return error;
	} else if (expected_input_size > input_size){
		return UTFX_ERROR_OVERFLOW;
	}

	return utfx_decoder_put_input_char(decoder, input_char);
}

utfx_error_t utfx_decoder_read_output(utfx_decoder_t * decoder, utf32_t * output){

	if (decoder->state != UTFX_DECODER_STATE_ACCEPTING_READ){
		return UTFX_ERROR_NOT_ACCEPTING_READ;
	}

	*output = decoder->output_char;

	decoder->state = UTFX_DECODER_STATE_ACCEPTING_WRITE;

	return UTFX_ERROR_NONE;
}

void utfx_decoder_set_mode(utfx_decoder_t * decoder, utfx_decoder_mode_t mode){
	decoder->mode = mode;
}

utfx_error_t utfx_decoder_write_byte(utfx_decoder_t * decoder, unsigned char byte){

	unsigned int decoded_byte_count = 0;

	utfx_error_t error = UTFX_ERROR_NONE;

	switch (decoder->input_byte_count % 4){
		case 0:
			decoder->input_byte_array[0] = byte;
			decoder->input_byte_count = 1;
			break;
		case 1:
			decoder->input_byte_array[1] = byte;
			decoder->input_byte_count = 2;
			break;
		case 2:
			decoder->input_byte_array[2] = byte;
			decoder->input_byte_count = 3;
			break;
		case 3:
			decoder->input_byte_array[3] = byte;
			decoder->input_byte_count = 4;
			break;
		default:
			return UTFX_ERROR_OVERFLOW;
	}

	if (decoder->input_byte_count >= 4){

		error = utfx_decoder_put_input_char(decoder, decoder->input_byte_array);
		if (error){
			return error;
		}

		error = utfx_decoder_get_input_size(decoder, decoder->input_byte_array, &decoded_byte_count);
		if (error){
			return error;
		}

		decoder->state = UTFX_DECODER_STATE_ACCEPTING_READ;
	}

	switch (decoded_byte_count % 4){
		case 1:
			decoder->input_byte_array[0] = decoder->input_byte_array[1];
			decoder->input_byte_array[1] = decoder->input_byte_array[2];
			decoder->input_byte_array[2] = decoder->input_byte_array[3];
			decoder->input_byte_count = 3;
			break;
		case 2:
			decoder->input_byte_array[0] = decoder->input_byte_array[2];
			decoder->input_byte_array[1] = decoder->input_byte_array[3];
			decoder->input_byte_count = 2;
			break;
		case 3:
			decoder->input_byte_array[0] = decoder->input_byte_array[3];
			decoder->input_byte_count = 1;
			break;
		case 4:
			decoder->input_byte_count = 0;
			break;
		default:
			break;
	}

	return UTFX_ERROR_NONE;
}


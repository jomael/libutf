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

static utfx_error_t decode(utfx_decoder_t * decoder);

static utfx_error_t decode_utf8(utfx_decoder_t * decoder);

static utfx_error_t decode_utf16be(utfx_decoder_t * decoder);

static utfx_error_t decode_utf16le(utfx_decoder_t * decoder);

static utfx_error_t decode_utf32be(utfx_decoder_t * decoder);

static utfx_error_t decode_utf32le(utfx_decoder_t * decoder);

static utfx_error_t write_byte(utfx_decoder_t * decoder, unsigned char byte);

void utfx_decoder_init(utfx_decoder_t * decoder){
	decoder->input_byte_array[0] = 0;
	decoder->input_byte_array[1] = 0;
	decoder->input_byte_array[2] = 0;
	decoder->input_byte_array[3] = 0;
	decoder->input_byte_count = 0;
	decoder->mode = UTFX_DECODER_MODE_UTF8;
	decoder->output_char = 0;
	decoder->state = UTFX_DECODER_STATE_READING;
}

utfx_decoder_mode_t utfx_decoder_get_mode(const utfx_decoder_t * decoder){
	return decoder->mode;
}

utfx_decoder_state_t utfx_decoder_get_state(const utfx_decoder_t * decoder){
	return decoder->state;
}

utfx_error_t utfx_decoder_read(utfx_decoder_t * decoder, utf32_t * output){

	*output = decoder->output_char;

	decoder->state = UTFX_DECODER_STATE_READING;

	return UTFX_ERROR_NONE;
}

void utfx_decoder_set_mode(utfx_decoder_t * decoder, utfx_decoder_mode_t mode){
	decoder->mode = mode;
}

unsigned int utfx_decoder_write(utfx_decoder_t * decoder, const void * src, unsigned int src_size){

	utfx_error_t error = UTFX_ERROR_NONE;

	utfx_decoder_state_t state = UTFX_DECODER_STATE_READING;

	unsigned int i = 0;

	const unsigned char * src8 = (const unsigned char *)(src);

	for (i = 0; i < src_size; i++){

		state = utfx_decoder_get_state(decoder);
		if (state != UTFX_DECODER_STATE_READING){
			break;
		}

		error = write_byte(decoder, src8[i]);
		if (error != UTFX_ERROR_NONE){
			return 0;
		}
	}

	return i;
}

static utfx_error_t decode(utfx_decoder_t * decoder){

	utfx_error_t error = UTFX_ERROR_NONE;

	switch (decoder->mode){
		case UTFX_DECODER_MODE_UTF8:
			error = decode_utf8(decoder);
			break;
		case UTFX_DECODER_MODE_UTF16_LE:
			error = decode_utf16le(decoder);
			break;
		case UTFX_DECODER_MODE_UTF16_BE:
			error = decode_utf16be(decoder);
			break;
		case UTFX_DECODER_MODE_UTF32_LE:
			error = decode_utf32le(decoder);
			break;
		case UTFX_DECODER_MODE_UTF32_BE:
			error = decode_utf32be(decoder);
			break;
		default:
			error = UTFX_ERROR_INVALID_MODE;
			break;
	}

	if (error != UTFX_ERROR_NONE){
		return error;
	} else { 
		decoder->state = UTFX_DECODER_STATE_WRITING;
	}

	return UTFX_ERROR_NONE;
}

static utfx_error_t decode_utf8(utfx_decoder_t * decoder){

	unsigned int decode_length = 0;
	decode_length = utf8_decode(decoder->input_byte_array, &decoder->output_char);
	if (decode_length == 0){
		return UTFX_ERROR_INVALID_SEQUENCE;
	} else if (decode_length == 1){
		decoder->input_byte_array[0] = decoder->input_byte_array[1];
		decoder->input_byte_array[1] = decoder->input_byte_array[2];
		decoder->input_byte_array[2] = decoder->input_byte_array[3];
		decoder->input_byte_count = 3;
	} else if (decode_length == 2){
		decoder->input_byte_array[0] = decoder->input_byte_array[2];
		decoder->input_byte_array[1] = decoder->input_byte_array[3];
		decoder->input_byte_count = 2;
	} else if (decode_length == 3){
		decoder->input_byte_array[0] = decoder->input_byte_array[3];
		decoder->input_byte_count = 1;
	} else if (decode_length == 4){
		decoder->input_byte_count = 0;
	}

	return UTFX_ERROR_NONE;
}

static utfx_error_t decode_utf16be(utfx_decoder_t * decoder){

	utf16_t out16[2] = { 0, 0 };

	unsigned int decode_length = 0;

	out16[0] = utf16be(decoder->input_byte_array);
	out16[1] = utf16be(&decoder->input_byte_array[2]);

	decode_length = utf16_decode(out16, &decoder->output_char);
	if (decode_length == 0){
		return UTFX_ERROR_INVALID_SEQUENCE;
	} else if (decode_length == 1){
		decoder->input_byte_array[0] = decoder->input_byte_array[2];
		decoder->input_byte_array[1] = decoder->input_byte_array[3];
		decoder->input_byte_count = 2;
	} else if (decode_length == 2){
		decoder->input_byte_count = 0;
	}

	return UTFX_ERROR_NONE;
}

static utfx_error_t decode_utf16le(utfx_decoder_t * decoder){

	utf16_t out16[2] = { 0, 0 };

	unsigned int decode_length = 0;

	out16[0] = utf16le(decoder->input_byte_array);
	out16[1] = utf16le(&decoder->input_byte_array[2]);

	decode_length = utf16_decode(out16, &decoder->output_char);
	if (decode_length == 0){
		return UTFX_ERROR_INVALID_SEQUENCE;
	} else if (decode_length == 1){
		decoder->input_byte_array[0] = decoder->input_byte_array[2];
		decoder->input_byte_array[1] = decoder->input_byte_array[3];
		decoder->input_byte_count = 2;
	} else if (decode_length == 2){
		decoder->input_byte_count = 0;
	}

	return UTFX_ERROR_NONE;
}

static utfx_error_t decode_utf32be(utfx_decoder_t * decoder){
	decoder->output_char = utf32be(decoder->input_byte_array);
	decoder->input_byte_count = 0;
	return UTFX_ERROR_NONE;
}

static utfx_error_t decode_utf32le(utfx_decoder_t * decoder){
	decoder->input_byte_count = 0;
	return UTFX_ERROR_NONE;
}

static utfx_error_t write_byte(utfx_decoder_t * decoder, unsigned char byte){

	utfx_error_t error = UTFX_ERROR_NONE;

	decoder->input_byte_count %= 4;

	switch (decoder->input_byte_count){
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
			/* should be unreachable */
			return UTFX_ERROR_OVERFLOW;
	}

	if (decoder->input_byte_count >= 4){
		error = decode(decoder);
		if (error != UTFX_ERROR_NONE){
			return error;
		}
	}

	return UTFX_ERROR_NONE;
}


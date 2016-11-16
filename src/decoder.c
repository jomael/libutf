/*
 *    This file is part of libutf.
 *
 *    libutf is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    libutf is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with libutf.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libutf/decoder.h>
#include <libutf/utf8.h>
#include <libutf/utf16.h>

static utf_error_t decode(utf_decoder_t * decoder);

static utf_error_t decode_utf8(utf_decoder_t * decoder);

static utf_error_t decode_utf16be(utf_decoder_t * decoder);

static utf_error_t decode_utf16le(utf_decoder_t * decoder);

static utf_error_t decode_utf32be(utf_decoder_t * decoder);

static utf_error_t decode_utf32le(utf_decoder_t * decoder);

static utf_error_t write_byte(utf_decoder_t * decoder, unsigned char byte);

void utf_decoder_init(utf_decoder_t * decoder){
	decoder->input_byte_array[0] = 0;
	decoder->input_byte_array[1] = 0;
	decoder->input_byte_array[2] = 0;
	decoder->input_byte_array[3] = 0;
	decoder->input_byte_count = 0;
	decoder->mode = UTF_DECODER_MODE_UTF8;
	decoder->output_char = 0;
	decoder->state = UTF_DECODER_STATE_READING;
}

utf_decoder_mode_t utf_decoder_get_mode(const utf_decoder_t * decoder){
	return decoder->mode;
}

utf_decoder_state_t utf_decoder_get_state(const utf_decoder_t * decoder){
	return decoder->state;
}

utf_error_t utf_decoder_read(utf_decoder_t * decoder, utf32_t * output){

	*output = decoder->output_char;

	decoder->state = UTF_DECODER_STATE_READING;

	return UTF_ERROR_NONE;
}

void utf_decoder_set_mode(utf_decoder_t * decoder, utf_decoder_mode_t mode){
	decoder->mode = mode;
}

unsigned int utf_decoder_write(utf_decoder_t * decoder, const void * src, unsigned int src_size){

	utf_error_t error = UTF_ERROR_NONE;

	utf_decoder_state_t state = UTF_DECODER_STATE_READING;

	unsigned int i = 0;

	const unsigned char * src8 = (const unsigned char *)(src);

	for (i = 0; i < src_size; i++){

		state = utf_decoder_get_state(decoder);
		if (state != UTF_DECODER_STATE_READING){
			break;
		}

		error = write_byte(decoder, src8[i]);
		if (error != UTF_ERROR_NONE){
			return 0;
		}
	}

	return i;
}

static utf_error_t decode(utf_decoder_t * decoder){

	utf_error_t error = UTF_ERROR_NONE;

	switch (decoder->mode){
		case UTF_DECODER_MODE_UTF8:
			error = decode_utf8(decoder);
			break;
		case UTF_DECODER_MODE_UTF16_LE:
			error = decode_utf16le(decoder);
			break;
		case UTF_DECODER_MODE_UTF16_BE:
			error = decode_utf16be(decoder);
			break;
		case UTF_DECODER_MODE_UTF32_LE:
			error = decode_utf32le(decoder);
			break;
		case UTF_DECODER_MODE_UTF32_BE:
			error = decode_utf32be(decoder);
			break;
		default:
			break;
	}

	if (error != UTF_ERROR_NONE){
		return error;
	} else { 
		decoder->state = UTF_DECODER_STATE_WRITING;
	}

	return UTF_ERROR_NONE;
}

static utf_error_t decode_utf8(utf_decoder_t * decoder){

	unsigned int decode_length = 0;
	decode_length = utf8_decode(decoder->input_byte_array, &decoder->output_char);
	if (decode_length == 0){
		return UTF_ERROR_INVALID_SEQUENCE;
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

	return UTF_ERROR_NONE;
}

static utf_error_t decode_utf16be(utf_decoder_t * decoder){

	utf16_t out16[2] = { 0, 0 };

	unsigned int decode_length = 0;

	out16[0] = utf16be(decoder->input_byte_array);
	out16[1] = utf16be(&decoder->input_byte_array[2]);

	decode_length = utf16_decode(out16, &decoder->output_char);
	if (decode_length == 0){
		return UTF_ERROR_INVALID_SEQUENCE;
	} else if (decode_length == 1){
		decoder->input_byte_array[0] = decoder->input_byte_array[2];
		decoder->input_byte_array[1] = decoder->input_byte_array[3];
		decoder->input_byte_count = 2;
	} else if (decode_length == 2){
		decoder->input_byte_count = 0;
	}

	return UTF_ERROR_NONE;
}

static utf_error_t decode_utf16le(utf_decoder_t * decoder){

	utf16_t out16[2] = { 0, 0 };

	unsigned int decode_length = 0;

	out16[0] = utf16le(decoder->input_byte_array);
	out16[1] = utf16le(&decoder->input_byte_array[2]);

	decode_length = utf16_decode(out16, &decoder->output_char);
	if (decode_length == 0){
		return UTF_ERROR_INVALID_SEQUENCE;
	} else if (decode_length == 1){
		decoder->input_byte_array[0] = decoder->input_byte_array[2];
		decoder->input_byte_array[1] = decoder->input_byte_array[3];
		decoder->input_byte_count = 2;
	} else if (decode_length == 2){
		decoder->input_byte_count = 0;
	}

	return UTF_ERROR_NONE;
}

static utf_error_t decode_utf32be(utf_decoder_t * decoder){
	decoder->output_char = utf32be(decoder->input_byte_array);
	decoder->input_byte_count = 0;
	return UTF_ERROR_NONE;
}

static utf_error_t decode_utf32le(utf_decoder_t * decoder){
	decoder->input_byte_count = 0;
	return UTF_ERROR_NONE;
}

static utf_error_t write_byte(utf_decoder_t * decoder, unsigned char byte){

	utf_error_t error = UTF_ERROR_NONE;

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
			return UTF_ERROR_OVERFLOW;
	}

	if (decoder->input_byte_count >= 4){
		error = decode(decoder);
		if (error != UTF_ERROR_NONE){
			return error;
		}
	}

	return UTF_ERROR_NONE;
}


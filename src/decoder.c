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

#include <stdlib.h>
#include <string.h>

static utf_error_t add_output_char(utf_decoder_t * decoder, utf32_t output);

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
	decoder->codec = UTF_CODEC_UTF8;
	decoder->output_array = NULL;
	decoder->output_count = 0;
	decoder->output_count_res = 0;
}

void utf_decoder_free(utf_decoder_t * decoder){
	if (decoder != NULL){
		free(decoder->output_array);
	}
}

utf_codec_t utf_decoder_get_codec(const utf_decoder_t * decoder){
	return decoder->codec;
}

utf_error_t utf_decoder_read(utf_decoder_t * decoder, utf32_t * dst, unsigned long int dst_count){

	unsigned long int read_count;

	if (dst_count > decoder->output_count){
		read_count = decoder->output_count;
	} else {
		read_count = dst_count;
	}

	memcpy(dst, decoder->output_array, read_count * sizeof(utf32_t));

	memmove(decoder->output_array,
	        &decoder->output_array[read_count],
	        (decoder->output_count - read_count) * sizeof(utf32_t));

	decoder->output_count -= read_count;

	return UTF_ERROR_NONE;
}

utf_error_t utf_decoder_reserve(utf_decoder_t * decoder, unsigned long int count){
	utf32_t * tmp;
	tmp = realloc(decoder->output_array, count * sizeof(utf32_t));
	if ((tmp == NULL) && (count > 0)){
		return UTF_ERROR_MALLOC;
	}
	decoder->output_array = tmp;
	decoder->output_count_res = count;
	if (count < decoder->output_count){
		decoder->output_count = count;
	}
	return UTF_ERROR_NONE;
}

void utf_decoder_set_codec(utf_decoder_t * decoder, utf_codec_t codec){
	decoder->codec = codec;
}

unsigned int utf_decoder_write(utf_decoder_t * decoder, const void * src, unsigned int src_size){

	utf_error_t error = UTF_ERROR_NONE;

	unsigned int i = 0;

	const unsigned char * src8 = (const unsigned char *)(src);

	for (i = 0; i < src_size; i++){
		error = write_byte(decoder, src8[i]);
		if (error != UTF_ERROR_NONE){
			return 0;
		}
	}

	return i;
}

static utf_error_t add_output_char(utf_decoder_t * decoder, utf32_t output){
	utf_error_t error;
	if (decoder->output_count >= decoder->output_count_res){
		error = utf_decoder_reserve(decoder, decoder->output_count_res + 32);
		if (error){
			return error;
		}
	}
	decoder->output_array[decoder->output_count] = output;
	decoder->output_count++;
	return UTF_ERROR_NONE;
}

static utf_error_t decode(utf_decoder_t * decoder){

	utf_error_t error = UTF_ERROR_NONE;

	switch (decoder->codec){
		case UTF_CODEC_UTF8:
			error = decode_utf8(decoder);
			break;
		case UTF_CODEC_UTF16_LE:
			error = decode_utf16le(decoder);
			break;
		case UTF_CODEC_UTF16_BE:
			error = decode_utf16be(decoder);
			break;
		case UTF_CODEC_UTF32_LE:
			error = decode_utf32le(decoder);
			break;
		case UTF_CODEC_UTF32_BE:
			error = decode_utf32be(decoder);
			break;
		default:
			break;
	}

	if (error != UTF_ERROR_NONE){
		return error;
	}

	return UTF_ERROR_NONE;
}

static utf_error_t decode_utf8(utf_decoder_t * decoder){

	utf_error_t error;
	unsigned int decode_length = 0;
	utf32_t out32;

	decode_length = utf8_decode(decoder->input_byte_array, &out32);

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

	error = add_output_char(decoder, out32);
	if (error){
		return error;
	}

	return UTF_ERROR_NONE;
}

static utf_error_t decode_utf16be(utf_decoder_t * decoder){

	utf_error_t error;
	utf16_t out16[2] = { 0, 0 };
	utf32_t out32;
	unsigned int decode_length = 0;

	out16[0] = utf16be(decoder->input_byte_array);
	out16[1] = utf16be(&decoder->input_byte_array[2]);

	decode_length = utf16_decode(out16, &out32);
	if (decode_length == 0){
		return UTF_ERROR_INVALID_SEQUENCE;
	} else if (decode_length == 1){
		decoder->input_byte_array[0] = decoder->input_byte_array[2];
		decoder->input_byte_array[1] = decoder->input_byte_array[3];
		decoder->input_byte_count = 2;
	} else if (decode_length == 2){
		decoder->input_byte_count = 0;
	}

	error = add_output_char(decoder, out32);
	if (error){
		return error;
	}

	return UTF_ERROR_NONE;
}

static utf_error_t decode_utf16le(utf_decoder_t * decoder){

	utf_error_t error;
	utf16_t out16[2] = { 0, 0 };
	utf32_t out32;
	unsigned int decode_length = 0;

	out16[0] = utf16le(decoder->input_byte_array);
	out16[1] = utf16le(&decoder->input_byte_array[2]);

	decode_length = utf16_decode(out16, &out32);
	if (decode_length == 0){
		return UTF_ERROR_INVALID_SEQUENCE;
	} else if (decode_length == 1){
		decoder->input_byte_array[0] = decoder->input_byte_array[2];
		decoder->input_byte_array[1] = decoder->input_byte_array[3];
		decoder->input_byte_count = 2;
	} else if (decode_length == 2){
		decoder->input_byte_count = 0;
	}

	error = add_output_char(decoder, out32);
	if (error){
		return error;
	}

	return UTF_ERROR_NONE;
}

static utf_error_t decode_utf32be(utf_decoder_t * decoder){
	utf_error_t error;
	error = add_output_char(decoder, utf32be(decoder->input_byte_array));
	if (error){
		return error;
	}
	decoder->input_byte_count = 0;
	return UTF_ERROR_NONE;
}

static utf_error_t decode_utf32le(utf_decoder_t * decoder){
	utf_error_t error;
	error = add_output_char(decoder, utf32le(decoder->input_byte_array));
	if (error){
		return error;
	}
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


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

#include <libutf/encoder.h>
#include <libutf/utf8.h>
#include <libutf/utf16.h>

#include <stdlib.h>
#include <string.h>

void utf_encoder_init(utf_encoder_t * encoder){
	encoder->codec = UTF_CODEC_UTF8;
	encoder->byte_array = NULL;
	encoder->byte_count = 0;
	encoder->byte_count_res = 0;
}

void utf_encoder_free(utf_encoder_t * encoder){
	if (encoder != NULL){
		free(encoder->byte_array);
	}
}

utf_codec_t utf_encoder_get_codec(const utf_encoder_t * encoder){
	return encoder->codec;
}

unsigned long int utf_encoder_read(utf_encoder_t * encoder, void * dst, unsigned long int dst_size){

	unsigned long int i = 0;
	unsigned char * dst8 = (unsigned char *)(dst);

	for (i = 0; (i < encoder->byte_count) && (i < dst_size); i++){
		dst8[i] = encoder->byte_array[i];
	}

	memmove(encoder->byte_array,
	       &encoder->byte_array[dst_size],
	        encoder->byte_count - i);

	encoder->byte_count -= i;

	return i;
}

void utf_encoder_set_codec(utf_encoder_t * encoder, utf_codec_t codec){
	encoder->codec = codec;
}

utf_error_t utf_encoder_write(utf_encoder_t * encoder, utf32_t input_char){

	utf_error_t error = UTF_ERROR_NONE;

	if ((encoder->byte_count + 4) > encoder->byte_count_res){
		error = utf_encoder_reserve(encoder, encoder->byte_count_res + 32);
		if (error){
			return error;
		}
	}

	if (encoder->codec == UTF_CODEC_UTF8){

		unsigned int result = utf8_encode(input_char, encoder->byte_array);
		if (!result){
			return UTF_ERROR_INVALID_SEQUENCE;
		} else {
			encoder->byte_count += result;
		}

	} else if (encoder->codec == UTF_CODEC_UTF16_LE){

		utf16_t output_char[2] = { 0, 0 };

		unsigned int result = utf16_encode(input_char, output_char);
		if (!result){
			return UTF_ERROR_INVALID_SEQUENCE;
		} else {
			encoder->byte_count += result * 2;
		}

		encoder->byte_array[0] = (output_char[0] >> 0) & 0xff;
		encoder->byte_array[1] = (output_char[0] >> 8) & 0xff;
		encoder->byte_array[2] = (output_char[1] >> 0) & 0xff;
		encoder->byte_array[3] = (output_char[1] >> 8) & 0xff;

	} else if (encoder->codec == UTF_CODEC_UTF16_BE){

		utf16_t output_char[2] = { 0, 0 };

		unsigned int result = utf16_encode(input_char, output_char);
		if (!result){
			return UTF_ERROR_INVALID_SEQUENCE;
		} else {
			encoder->byte_count += result * 2;
		}

		encoder->byte_array[0] = (output_char[0] >> 8) & 0xff;
		encoder->byte_array[1] = (output_char[0] >> 0) & 0xff;
		encoder->byte_array[2] = (output_char[1] >> 8) & 0xff;
		encoder->byte_array[3] = (output_char[1] >> 0) & 0xff;

	} else if (encoder->codec == UTF_CODEC_UTF32_LE){
		encoder->byte_array[0] = (input_char >> 0x00) & 0xff;
		encoder->byte_array[1] = (input_char >> 0x08) & 0xff;
		encoder->byte_array[2] = (input_char >> 0x10) & 0xff;
		encoder->byte_array[3] = (input_char >> 0x18) & 0xff;
		encoder->byte_count += 4;
	} else if (encoder->codec == UTF_CODEC_UTF32_BE){
		encoder->byte_array[0] = (input_char >> 0x18) & 0xff;
		encoder->byte_array[1] = (input_char >> 0x10) & 0xff;
		encoder->byte_array[2] = (input_char >> 0x08) & 0xff;
		encoder->byte_array[3] = (input_char >> 0x00) & 0xff;
		encoder->byte_count += 4;
	}

	return UTF_ERROR_NONE;
}

utf_error_t utf_encoder_reserve(utf_encoder_t * encoder, unsigned long int size){
	unsigned char * tmp;
	tmp = realloc(encoder->byte_array, size);
	if ((tmp == NULL) && (size > 0)){
		return UTF_ERROR_MALLOC;
	}
	encoder->byte_array = tmp;
	encoder->byte_count_res = size;
	if (size < encoder->byte_count){
		encoder->byte_count = size;
	}
	return UTF_ERROR_NONE;
}


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

void utf_encoder_init(utf_encoder_t * encoder){
	encoder->mode = UTF_ENCODER_MODE_UTF8;
	encoder->byte_array[0] = 0;
	encoder->byte_array[1] = 0;
	encoder->byte_array[2] = 0;
	encoder->byte_array[3] = 0;
	encoder->byte_count = 0;
	encoder->byte_count_read = 0;
	encoder->state = UTF_ENCODER_STATE_READING;
}

utf_encoder_mode_t utf_encoder_get_mode(const utf_encoder_t * encoder){
	return encoder->mode;
}

utf_encoder_state_t utf_encoder_get_state(const utf_encoder_t * encoder){
	return encoder->state;
}

unsigned long int utf_encoder_read(utf_encoder_t * encoder, void * dst, unsigned long int dst_size){

	unsigned long int i = 0;
	unsigned long int i_start = encoder->byte_count_read;
	unsigned long int j = 0;
	unsigned char * dst8 = (unsigned char *)(dst);

	for (i = i_start, j = 0; i < encoder->byte_count && j < dst_size; i++, j++){
		dst8[j] = encoder->byte_array[i];
	}

	encoder->byte_count_read = i;
	if (encoder->byte_count_read >= encoder->byte_count){
		encoder->byte_count = 0;
		encoder->byte_count_read = 0;
		encoder->state = UTF_ENCODER_STATE_READING;
	}

	return j;
}

void utf_encoder_set_mode(utf_encoder_t * encoder, utf_encoder_mode_t mode){
	encoder->mode = mode;
}

utf_error_t utf_encoder_write(utf_encoder_t * encoder, utf32_t input_char){

	if (encoder->mode == UTF_ENCODER_MODE_UTF8){

		unsigned int result = utf8_encode(encoder->byte_array, input_char);
		if (!result){
			return UTF_ERROR_INVALID_SEQUENCE;
		} else {
			encoder->byte_count = result;
		}

	} else if (encoder->mode == UTF_ENCODER_MODE_UTF16_LE){

		utf16_t output_char[2] = { 0, 0 };

		unsigned int result = utf16_encode(input_char, output_char);
		if (!result){
			return UTF_ERROR_INVALID_SEQUENCE;
		} else {
			encoder->byte_count = result * 2;
		}

		encoder->byte_array[0] = (output_char[0] >> 0) & 0xff;
		encoder->byte_array[1] = (output_char[0] >> 8) & 0xff;
		encoder->byte_array[2] = (output_char[1] >> 0) & 0xff;
		encoder->byte_array[3] = (output_char[1] >> 8) & 0xff;

	} else if (encoder->mode == UTF_ENCODER_MODE_UTF16_BE){

		utf16_t output_char[2] = { 0, 0 };

		unsigned int result = utf16_encode(input_char, output_char);
		if (!result){
			return UTF_ERROR_INVALID_SEQUENCE;
		} else {
			encoder->byte_count = result * 2;
		}

		encoder->byte_array[0] = (output_char[0] >> 8) & 0xff;
		encoder->byte_array[1] = (output_char[0] >> 0) & 0xff;
		encoder->byte_array[2] = (output_char[1] >> 8) & 0xff;
		encoder->byte_array[3] = (output_char[1] >> 0) & 0xff;

	} else if (encoder->mode == UTF_ENCODER_MODE_UTF32_LE){
		encoder->byte_array[0] = (input_char >> 0x00) & 0xff;
		encoder->byte_array[1] = (input_char >> 0x08) & 0xff;
		encoder->byte_array[2] = (input_char >> 0x10) & 0xff;
		encoder->byte_array[3] = (input_char >> 0x18) & 0xff;
		encoder->byte_count = 4;
	} else if (encoder->mode == UTF_ENCODER_MODE_UTF32_BE){
		encoder->byte_array[0] = (input_char >> 0x18) & 0xff;
		encoder->byte_array[1] = (input_char >> 0x10) & 0xff;
		encoder->byte_array[2] = (input_char >> 0x08) & 0xff;
		encoder->byte_array[3] = (input_char >> 0x00) & 0xff;
		encoder->byte_count = 4;
	}

	encoder->state = UTF_ENCODER_STATE_WRITING;

	return UTF_ERROR_NONE;
}


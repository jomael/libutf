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

#include "encoder.h"

#include "utf8.h"
#include "utf16.h"

void utfx_encoder_init(utfx_encoder_t * encoder){
	encoder->mode = UTFX_ENCODER_MODE_NONE;
	encoder->byte_array[0] = 0;
	encoder->byte_array[1] = 0;
	encoder->byte_array[2] = 0;
	encoder->byte_array[3] = 0;
	encoder->byte_count = 0;
}

void utfx_encoder_set_mode(utfx_encoder_t * encoder, int mode){
	encoder->mode = mode;
}

int utfx_encoder_put_input_char(utfx_encoder_t * encoder, utf32_t input_char){

	int result = 0;

	if (encoder->mode == UTFX_ENCODER_MODE_NONE){
		result = -1;
	} else if (encoder->mode == UTFX_ENCODER_MODE_UTF8){
		result = utf8_encode(encoder->byte_array, input_char);
	} else if (encoder->mode == UTFX_ENCODER_MODE_UTF16_LE){

		utf16_t output_char[2] = { 0, 0 };

		result = utf16_encode(input_char, output_char);
		if (result < 0){
			return -1;
		}

		encoder->byte_array[0] = (output_char[0] << 0) & 0xff;
		encoder->byte_array[1] = (output_char[0] << 8) & 0xff;
		encoder->byte_array[2] = (output_char[1] << 0) & 0xff;
		encoder->byte_array[3] = (output_char[1] << 8) & 0xff;

		encoder->byte_count = result;

	} else if (encoder->mode == UTFX_ENCODER_MODE_UTF16_BE){

		utf16_t output_char[2] = { 0, 0 };

		result = utf16_encode(input_char, output_char);
		if (result < 0){
			return -1;
		}

		encoder->byte_array[0] = (output_char[0] << 8) & 0xff;
		encoder->byte_array[1] = (output_char[0] << 0) & 0xff;
		encoder->byte_array[2] = (output_char[1] << 8) & 0xff;
		encoder->byte_array[3] = (output_char[1] << 0) & 0xff;

		encoder->byte_count = result;

	} else {

		/* not implemented */
		return -2;
	}

	if (result > 0){
		encoder->byte_count = result;
	} else {
		encoder->byte_count = 0;
	}

	return result;
}

int utfx_encoder_get_output_char(const utfx_encoder_t * encoder, void * output_char){

	unsigned int i = 0;

	unsigned char * output_char_ptr = 0;

	output_char_ptr = (unsigned char *)(output_char);

	for (i = 0; i < encoder->byte_count; i++){
		output_char_ptr[i] = encoder->byte_array[i];
	}

	return i;
}

int utfx_encoder_get_output_size(const utfx_encoder_t * encoder){
	return encoder->byte_count;
}


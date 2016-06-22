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

#include "converter.h"

void utfx_converter_init(utfx_converter_t * converter){

	utfx_decoder_t * decoder = 0;
	utfx_encoder_t * encoder = 0;

	decoder = utfx_converter_get_decoder(converter);
	utfx_decoder_init(decoder);

	encoder = utfx_converter_get_encoder(converter);
	utfx_encoder_init(encoder);
}

utfx_decoder_t * utfx_converter_get_decoder(utfx_converter_t * converter){
	return &converter->decoder;
}

const utfx_decoder_t * utfx_converter_get_decoder_const(const utfx_converter_t * converter){
	return &converter->decoder;
}

utfx_decoder_mode_t utfx_converter_get_decoder_mode(const utfx_converter_t * converter){
	const utfx_decoder_t * decoder = 0;
	decoder = utfx_converter_get_decoder_const(converter);
	return utfx_decoder_get_mode(decoder);
}

utfx_decoder_state_t utfx_converter_get_decoder_state(const utfx_converter_t * converter){
	const utfx_decoder_t * decoder = 0;
	decoder = utfx_converter_get_decoder_const(converter);
	return utfx_decoder_get_state(decoder);
}

utfx_encoder_t * utfx_converter_get_encoder(utfx_converter_t * converter){
	return &converter->encoder;
}

const utfx_encoder_t * utfx_converter_get_encoder_const(const utfx_converter_t * converter){
	return &converter->encoder;
}

utfx_encoder_mode_t utfx_converter_get_encoder_mode(const utfx_converter_t * converter){
	const utfx_encoder_t * encoder = 0;
	encoder = utfx_converter_get_encoder_const(converter);
	return utfx_encoder_get_mode(encoder);
}

utfx_encoder_state_t utfx_converter_get_encoder_state(const utfx_converter_t * converter){
	const utfx_encoder_t * encoder = 0;
	encoder = utfx_converter_get_encoder_const(converter);
	return utfx_encoder_get_state(encoder);
}

utfx_converter_state_t utfx_converter_get_state(const utfx_converter_t * converter){

	utfx_converter_state_t state = UTFX_CONVERTER_STATE_READING;
	utfx_encoder_state_t encoder_state;

	encoder_state = utfx_converter_get_encoder_state(converter);
	if (encoder_state == UTFX_ENCODER_STATE_WRITING){
		state = UTFX_CONVERTER_STATE_WRITING;
	}

	return state;
}

unsigned int utfx_converter_read(utfx_converter_t * converter, void * dst, unsigned int dst_size){

	utfx_encoder_t * encoder = 0;

	encoder = utfx_converter_get_encoder(converter);

	return utfx_encoder_read(encoder, dst, dst_size);
}

void utfx_converter_set_decoder_mode(utfx_converter_t * converter, utfx_decoder_mode_t decoder_mode){
	utfx_decoder_t * decoder = 0;
	decoder = utfx_converter_get_decoder(converter);
	utfx_decoder_set_mode(decoder, decoder_mode);
}

void utfx_converter_set_encoder_mode(utfx_converter_t * converter, utfx_encoder_mode_t encoder_mode){
	utfx_encoder_t * encoder = 0;
	encoder = utfx_converter_get_encoder(converter);
	utfx_encoder_set_mode(encoder, encoder_mode);
}

unsigned int utfx_converter_write(utfx_converter_t * converter, const void * src, unsigned int src_size){

	utfx_error_t error = UTFX_ERROR_NONE;
	utfx_decoder_t * decoder = 0;
	utfx_encoder_t * encoder = 0;
	utfx_decoder_state_t decoder_state = UTFX_DECODER_STATE_READING;
	unsigned int write_count = 0;

	decoder = utfx_converter_get_decoder(converter);
	write_count = utfx_decoder_write(decoder, src, src_size);

	decoder_state = utfx_decoder_get_state(decoder);
	if (decoder_state == UTFX_DECODER_STATE_WRITING){
		utf32_t output = 0;
		error = utfx_decoder_read(decoder, &output);
		if (error == UTFX_ERROR_NONE){
			encoder = utfx_converter_get_encoder(converter);
			/* ignoring return code */
			/* low-risk of error */
			utfx_encoder_write(encoder, output);
		}
	}

	return write_count;
}


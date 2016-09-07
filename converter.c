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

#include "converter.h"

void utf_converter_init(utf_converter_t * converter){

	utf_decoder_t * decoder = 0;
	utf_encoder_t * encoder = 0;

	decoder = utf_converter_get_decoder(converter);
	utf_decoder_init(decoder);

	encoder = utf_converter_get_encoder(converter);
	utf_encoder_init(encoder);
}

utf_decoder_t * utf_converter_get_decoder(utf_converter_t * converter){
	return &converter->decoder;
}

const utf_decoder_t * utf_converter_get_decoder_const(const utf_converter_t * converter){
	return &converter->decoder;
}

utf_decoder_mode_t utf_converter_get_decoder_mode(const utf_converter_t * converter){
	const utf_decoder_t * decoder = 0;
	decoder = utf_converter_get_decoder_const(converter);
	return utf_decoder_get_mode(decoder);
}

utf_decoder_state_t utf_converter_get_decoder_state(const utf_converter_t * converter){
	const utf_decoder_t * decoder = 0;
	decoder = utf_converter_get_decoder_const(converter);
	return utf_decoder_get_state(decoder);
}

utf_encoder_t * utf_converter_get_encoder(utf_converter_t * converter){
	return &converter->encoder;
}

const utf_encoder_t * utf_converter_get_encoder_const(const utf_converter_t * converter){
	return &converter->encoder;
}

utf_encoder_mode_t utf_converter_get_encoder_mode(const utf_converter_t * converter){
	const utf_encoder_t * encoder = 0;
	encoder = utf_converter_get_encoder_const(converter);
	return utf_encoder_get_mode(encoder);
}

utf_encoder_state_t utf_converter_get_encoder_state(const utf_converter_t * converter){
	const utf_encoder_t * encoder = 0;
	encoder = utf_converter_get_encoder_const(converter);
	return utf_encoder_get_state(encoder);
}

utf_converter_state_t utf_converter_get_state(const utf_converter_t * converter){

	utf_converter_state_t state = UTF_CONVERTER_STATE_READING;
	utf_encoder_state_t encoder_state;

	encoder_state = utf_converter_get_encoder_state(converter);
	if (encoder_state == UTF_ENCODER_STATE_WRITING){
		state = UTF_CONVERTER_STATE_WRITING;
	}

	return state;
}

unsigned int utf_converter_read(utf_converter_t * converter, void * dst, unsigned int dst_size){

	utf_encoder_t * encoder = 0;

	encoder = utf_converter_get_encoder(converter);

	return utf_encoder_read(encoder, dst, dst_size);
}

void utf_converter_set_decoder_mode(utf_converter_t * converter, utf_decoder_mode_t decoder_mode){
	utf_decoder_t * decoder = 0;
	decoder = utf_converter_get_decoder(converter);
	utf_decoder_set_mode(decoder, decoder_mode);
}

void utf_converter_set_encoder_mode(utf_converter_t * converter, utf_encoder_mode_t encoder_mode){
	utf_encoder_t * encoder = 0;
	encoder = utf_converter_get_encoder(converter);
	utf_encoder_set_mode(encoder, encoder_mode);
}

unsigned int utf_converter_write(utf_converter_t * converter, const void * src, unsigned int src_size){

	utf_error_t error = UTF_ERROR_NONE;
	utf_decoder_t * decoder = 0;
	utf_encoder_t * encoder = 0;
	utf_decoder_state_t decoder_state = UTF_DECODER_STATE_READING;
	unsigned int write_count = 0;

	decoder = utf_converter_get_decoder(converter);
	write_count = utf_decoder_write(decoder, src, src_size);

	decoder_state = utf_decoder_get_state(decoder);
	if (decoder_state == UTF_DECODER_STATE_WRITING){
		utf32_t output = 0;
		error = utf_decoder_read(decoder, &output);
		if (error == UTF_ERROR_NONE){
			encoder = utf_converter_get_encoder(converter);
			/* ignoring return code */
			/* low-risk of error */
			utf_encoder_write(encoder, output);
		}
	}

	return write_count;
}


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

#include <libutf/converter.h>

#include <stdlib.h>

void utf_converter_init(utf_converter_t * converter){

	utf_decoder_t * decoder = 0;
	utf_encoder_t * encoder = 0;

	decoder = utf_converter_get_decoder(converter);
	utf_decoder_init(decoder);

	encoder = utf_converter_get_encoder(converter);
	utf_encoder_init(encoder);
}

void utf_converter_free(utf_converter_t * converter){
	if (converter != NULL){
		utf_decoder_free(&converter->decoder);
		utf_encoder_free(&converter->encoder);
	}
}

utf_decoder_t * utf_converter_get_decoder(utf_converter_t * converter){
	return &converter->decoder;
}

const utf_decoder_t * utf_converter_get_decoder_const(const utf_converter_t * converter){
	return &converter->decoder;
}

utf_codec_t utf_converter_get_decoder_codec(const utf_converter_t * converter){
	const utf_decoder_t * decoder = 0;
	decoder = utf_converter_get_decoder_const(converter);
	return utf_decoder_get_codec(decoder);
}

utf_encoder_t * utf_converter_get_encoder(utf_converter_t * converter){
	return &converter->encoder;
}

const utf_encoder_t * utf_converter_get_encoder_const(const utf_converter_t * converter){
	return &converter->encoder;
}

utf_codec_t utf_converter_get_encoder_codec(const utf_converter_t * converter){
	const utf_encoder_t * encoder = 0;
	encoder = utf_converter_get_encoder_const(converter);
	return utf_encoder_get_codec(encoder);
}

unsigned int utf_converter_read(utf_converter_t * converter, void * dst, unsigned int dst_size){

	utf_encoder_t * encoder = 0;

	encoder = utf_converter_get_encoder(converter);

	return utf_encoder_read(encoder, dst, dst_size);
}

void utf_converter_set_decoder_codec(utf_converter_t * converter, utf_codec_t decoder_codec){
	utf_decoder_t * decoder = 0;
	decoder = utf_converter_get_decoder(converter);
	utf_decoder_set_codec(decoder, decoder_codec);
}

void utf_converter_set_encoder_codec(utf_converter_t * converter, utf_codec_t encoder_codec){
	utf_encoder_t * encoder = 0;
	encoder = utf_converter_get_encoder(converter);
	utf_encoder_set_codec(encoder, encoder_codec);
}

unsigned int utf_converter_write(utf_converter_t * converter, const void * src, unsigned int src_size){

	utf_error_t error = UTF_ERROR_NONE;
	utf_decoder_t * decoder = 0;
	utf_encoder_t * encoder = 0;
	unsigned int write_count = 0;
	utf32_t output = 0;

	decoder = utf_converter_get_decoder(converter);

	write_count = utf_decoder_write(decoder, src, src_size);

	error = utf_decoder_read(decoder, &output, 1);
	if (error == UTF_ERROR_NONE){
		encoder = utf_converter_get_encoder(converter);
		/* ignoring return code */
		/* low-risk of error */
		utf_encoder_write(encoder, output);
	}

	return write_count;
}


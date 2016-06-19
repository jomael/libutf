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

utfx_encoder_t * utfx_converter_get_encoder(utfx_converter_t * converter){
	return &converter->encoder;
}


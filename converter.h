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

#ifndef UTFX_CONVERTER_H
#define UTFX_CONVERTER_H

#include "decoder.h"
#include "encoder.h"

typedef struct utfx_converter {
	utfx_decoder_t decoder;
	utfx_encoder_t encoder;
} utfx_converter_t;

void utfx_converter_init(utfx_converter_t * converter);

utfx_decoder_t * utfx_converter_get_decoder(utfx_converter_t * converter);

utfx_encoder_t * utfx_converter_get_encoder(utfx_converter_t * converter);

unsigned int utfx_converter_read(utfx_converter_t * converter, void * dst, unsigned int dst_size);

unsigned int utfx_converter_write(utfx_converter_t * converter, const void * src, unsigned int src_size);

#endif /* UTFX_CONVERTER_H */


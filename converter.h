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

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** The state of the converter
 * @ingroup utfx
 */

typedef enum utfx_converter_state {
	UTFX_CONVERTER_STATE_READING,
	UTFX_CONVERTER_STATE_WRITING
} utfx_converter_state_t;

/** A UTF-8, UTF-16 or UTF-32 converter
 * @ingroup utfx
 */

typedef struct utfx_converter {
	/** The decoder of the converter structure */
	utfx_decoder_t decoder;
	/** The encoder of the converter structure */
	utfx_encoder_t encoder;
} utfx_converter_t;


/** Initializes the members of a converter structure.
 * @param converter An uninitialized converter structure.
 * @ingroup utfx
 */

void utfx_converter_init(utfx_converter_t * converter);

/** Returns the decoder of the converter.
 * @param converter An initialized converter.
 * @ingroup utfx
 */

utfx_decoder_t * utfx_converter_get_decoder(utfx_converter_t * converter);

/** Returns the decoder of the converter.
 * @param converter An initialized converter.
 * @ingroup utfx
 */

const utfx_decoder_t * utfx_converter_get_decoder_const(const utfx_converter_t * converter);

/** Returns the mode of the decoder
 * @param converter An initialized converter
 * @ingroup utfx
 */

utfx_decoder_mode_t utfx_converter_get_decoder_mode(const utfx_converter_t * converter);

/** Returns the state of the decoder.
 * @param converter An initialized converter
 * @ingroup utfx
 */

utfx_decoder_state_t utfx_converter_get_decoder_state(const utfx_converter_t * converter);

/** Returns the encoder of the converter.
 * @param converter An initialized converter.
 * @ingroup utfx
 */

utfx_encoder_t * utfx_converter_get_encoder(utfx_converter_t * converter);

/** Returns the encoder of the converter.
 * @param converter An initialized converter.
 * @ingroup utfx
 */

const utfx_encoder_t * utfx_converter_get_encoder_const(const utfx_converter_t * converter);

/** Returns the mode of the encoder.
 * @param converter An initialized converter structure.
 * @ingroup utfx
 */

utfx_encoder_mode_t utfx_converter_get_encoder_mode(const utfx_converter_t * converter);

/** Returns the state of the encoder.
 * @param converter An initialized converter structure.
 * @ingroup utfx
 */

utfx_encoder_state_t utfx_converter_get_encoder_state(const utfx_converter_t * converter);

/** Returns the state of the converter.
 * @param converter An initialized converter structure.
 * @ingroup utfx
 */

utfx_converter_state_t utfx_converter_get_state(const utfx_converter_t * converter);

/** Sets the mode of the decoder.
 * @param converter An initialized converter.
 * @param decoder_mode The new decoder mode for the converter.
 * @ingroup utfx
 */

void utfx_converter_set_decoder_mode(utfx_converter_t * converter, utfx_decoder_mode_t decoder_mode);

/** Sets the mode of the encoder.
 * @param converter An initialized converter.
 * @param encoder_mode The new decoder mode for the converter.
 * @ingroup utfx
 */

void utfx_converter_set_encoder_mode(utfx_converter_t * converter, utfx_encoder_mode_t encoder_mode);

/** Reads encoded data from the converter.
 * @param converter An initialized converter structure.
 * @param dst The address to write the encoded data to
 * @param dst_size The number of bytes that the destination address can store.
 * @returns The number of bytes read from the converter.
 * @ingroup utfx
 */

unsigned int utfx_converter_read(utfx_converter_t * converter, void * dst, unsigned int dst_size);

/** Writes data to the converter for decoding.
 * @param converter An initialized converter structure.
 * @param src The address to containing the encoded data
 * @param src_size The number of bytes that the source address contains
 * @returns The number of bytes to write to the converter
 * @ingroup utfx
 */

unsigned int utfx_converter_write(utfx_converter_t * converter, const void * src, unsigned int src_size);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* UTFX_CONVERTER_H */


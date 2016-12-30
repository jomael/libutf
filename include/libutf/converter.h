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

#ifndef LIBUTF_CONVERTER_H
#define LIBUTF_CONVERTER_H

#include "decoder.h"
#include "encoder.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** The state of the converter
 * @ingroup libutf
 */

typedef enum utf_converter_state {
	/** The converter has data that has not been fully decoded. */
	UTF_CONVERTER_STATE_READING,
	/** The converter has data that has not been read */
	UTF_CONVERTER_STATE_WRITING,
	/** The converter has no data in it's internal buffers.
	 * The converter may be closed without losing data. */
	UTF_CONVERTER_STATE_DONE
} utf_converter_state_t;

/** A UTF-8, UTF-16 or UTF-32 converter
 * @ingroup libutf
 */

typedef struct utf_converter {
	/** The decoder of the converter structure */
	utf_decoder_t decoder;
	/** The encoder of the converter structure */
	utf_encoder_t encoder;
} utf_converter_t;


/** Initializes the members of a converter structure.
 * @param converter An uninitialized converter structure.
 * @ingroup libutf
 */

void utf_converter_init(utf_converter_t * converter);

/** Returns the decoder of the converter.
 * @param converter An initialized converter.
 * @ingroup libutf
 */

utf_decoder_t * utf_converter_get_decoder(utf_converter_t * converter);

/** Returns the decoder of the converter.
 * @param converter An initialized converter.
 * @ingroup libutf
 */

const utf_decoder_t * utf_converter_get_decoder_const(const utf_converter_t * converter);

/** Returns the mode of the decoder
 * @param converter An initialized converter
 * @ingroup libutf
 */

utf_decoder_mode_t utf_converter_get_decoder_mode(const utf_converter_t * converter);

/** Returns the state of the decoder.
 * @param converter An initialized converter
 * @ingroup libutf
 */

utf_decoder_state_t utf_converter_get_decoder_state(const utf_converter_t * converter);

/** Returns the encoder of the converter.
 * @param converter An initialized converter.
 * @ingroup libutf
 */

utf_encoder_t * utf_converter_get_encoder(utf_converter_t * converter);

/** Returns the encoder of the converter.
 * @param converter An initialized converter.
 * @ingroup libutf
 */

const utf_encoder_t * utf_converter_get_encoder_const(const utf_converter_t * converter);

/** Returns the mode of the encoder.
 * @param converter An initialized converter structure.
 * @ingroup libutf
 */

utf_encoder_mode_t utf_converter_get_encoder_mode(const utf_converter_t * converter);

/** Returns the state of the encoder.
 * @param converter An initialized converter structure.
 * @ingroup libutf
 */

utf_encoder_state_t utf_converter_get_encoder_state(const utf_converter_t * converter);

/** Returns the state of the converter.
 * @param converter An initialized converter structure.
 * @ingroup libutf
 */

utf_converter_state_t utf_converter_get_state(const utf_converter_t * converter);

/** Sets the mode of the decoder.
 * @param converter An initialized converter.
 * @param decoder_mode The new decoder mode for the converter.
 * @ingroup libutf
 */

void utf_converter_set_decoder_mode(utf_converter_t * converter, utf_decoder_mode_t decoder_mode);

/** Sets the mode of the encoder.
 * @param converter An initialized converter.
 * @param encoder_mode The new decoder mode for the converter.
 * @ingroup libutf
 */

void utf_converter_set_encoder_mode(utf_converter_t * converter, utf_encoder_mode_t encoder_mode);

/** Reads encoded data from the converter.
 * @param converter An initialized converter structure.
 * @param dst The address to write the encoded data to
 * @param dst_size The number of bytes that the destination address can store.
 * @returns The number of bytes read from the converter.
 * @ingroup libutf
 */

unsigned int utf_converter_read(utf_converter_t * converter, void * dst, unsigned int dst_size);

/** Writes data to the converter for decoding.
 * @param converter An initialized converter structure.
 * @param src The address to containing the encoded data
 * @param src_size The number of bytes that the source address contains
 * @returns The number of bytes to write to the converter
 * @ingroup libutf
 */

unsigned int utf_converter_write(utf_converter_t * converter, const void * src, unsigned int src_size);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* LIBUTF_CONVERTER_H */


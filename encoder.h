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

#ifndef UTFX_ENCODER_H
#define UTFX_ENCODER_H

#include "utf32.h"
#include "error.h"

/** The mode of the encoder.
 * This is a combination of the choice of codec and choice of byte order.
 * @ingroup encoding
 */

typedef enum utfx_encoder_mode {
	UTFX_ENCODER_MODE_UTF8,
	UTFX_ENCODER_MODE_UTF16_LE,
	UTFX_ENCODER_MODE_UTF16_BE,
	UTFX_ENCODER_MODE_UTF32_LE,
	UTFX_ENCODER_MODE_UTF32_BE
} utfx_encoder_mode_t;

/** The state of the encoder.
 * Determines if the encoder is taking reads or writes.
 * @ingroup encoding */

typedef enum utfx_encoder_state {
	UTFX_ENCODER_STATE_READING,
	UTFX_ENCODER_STATE_WRITING
} utfx_encoder_state_t;

/** A UTF8, UTF16 and UTF32 encoder.
 * It may be used so that, once the mode is set, the encoding of the input text may be abstracted.
 * @ingroup encoding
 */

typedef struct {
	/** The encoding mode of the encoder */
	utfx_encoder_mode_t mode;
	/** An output buffer, which contains just enough bytes for any UTF codec */
	unsigned char byte_array[4];
	/** The number of bytes in the output buffer that are part of the encoded character */
	unsigned long int byte_count;
	/** The number of bytes that have been read by the client */
	unsigned long int byte_count_read;
	/** The state of the encoder. */
	utfx_encoder_state_t state;
} utfx_encoder_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Initializes the members of an encoder structure.
 * Sets the encoding mode to UTF-8.
 * @param encoder An uninitialized encoder structure.
 * @ingroup encoding
 */

void utfx_encoder_init(utfx_encoder_t * encoder);

/** Returns the mode of the encoder.
 * @param encoder An initialized encoder structure.
 * @returns The current mode of the encoder.
 * @ingroup encoding
 */

utfx_encoder_mode_t utfx_encoder_get_mode(const utfx_encoder_t * encoder);

/** Returns the state of the encoder.
 * @param encoder An initialized encoder structure.
 * @returns The current state of the encoder.
 * @ingroup encoding
 * */

utfx_encoder_state_t utfx_encoder_get_state(const utfx_encoder_t * encoder);

/** Reads the internal output character of the last encoded input character.
 * The encoding of the output character is determined by what mode the encoder is in.
 * The mode of the encoder can be set with the function @ref utfx_encoder_set_mode.
 * @param encoder An initialized encoder structure.
 * @param dst The address of where the output character will be written.
 * @param dst_size The number of bytes to read from the encoder.
 * @return The number of bytes read from the encoder.
 */

unsigned long int utfx_encoder_read(utfx_encoder_t * encoder, void * dst, unsigned long int dst_size);

/** Sets the encoding mode of the encoder.
 * @param encoder An initialized encoder structure.
 * @param mode The new mode of the encoder.
 * @ingroup encoding
 */

void utfx_encoder_set_mode(utfx_encoder_t * encoder, utfx_encoder_mode_t mode);

/** Encodes an input character.
 * The output of the encoding is determined by what mode the encoder is in.
 * @param encoder An initialized encoder structure
 * @param input_char A valid UTF-32 character.
 * @returns On success, UTFX_ERROR_NONE is returned.
 * @ingroup encoding
 */

utfx_error_t utfx_encoder_write(utfx_encoder_t * encoder, utf32_t input_char);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* UTFX_ENCODER_H */


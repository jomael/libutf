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
	UTFX_ENCODER_MODE_NONE = 0,
	UTFX_ENCODER_MODE_UTF8,
	UTFX_ENCODER_MODE_UTF16_LE,
	UTFX_ENCODER_MODE_UTF16_BE,
	UTFX_ENCODER_MODE_UTF32_LE,
	UTFX_ENCODER_MODE_UTF32_BE,
	UTFX_ENCODER_MODE_UNKNOWN = -1
} utfx_encoder_mode_t;

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
	unsigned int byte_count;
} utfx_encoder_t;

/** Initializes the members of an encoder structure.
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

/** Returns the size of the encoded output character, from the last call to utfx_encoder_put_input_char.
 * This may be used to insure that enough memory is allocated for a subsequent call to utfx_encoder_get_output_char or utfx_encoder_get_output_char_safely.
 * @param encoder An initialized encoder structure.
 * @returns The number of bytes occupied by the output character of the last encoding operation.
 * @ingroup encoding
 */

unsigned int utfx_encoder_get_output_size(const utfx_encoder_t * encoder);

/** Reads the internal output character of the last encoded input character.
 * The encoding of the output character is determined by what mode the encoder is in.
 * The mode of the encoder can be set with the function @ref utfx_encoder_set_mode.
 * @param encoder An initialized encoder structure.
 * @param output_char The address of where the output character will be written.
 *  It should be at least 4 bytes long.
 * @return On success, UTFX_ERROR_NONE is returned.
 */

utfx_error_t utfx_encoder_get_output_char(const utfx_encoder_t * encoder, void * output_char);

/** Reads the internal output character of the last encoded input character, without risk of a out-of-bounds write.
 * The encoding of the output character is determined by what mode the encoder is in.
 * The mode of the encoder can be set with the function @ref utfx_encoder_set_mode.
 * The number of bytes used by the output can be accessed with @ref utfx_encoder_get_output_size
 * @param encoder An initialized encoder structure.
 * @param output_char The address of where the output character will be written.
 * @param output_size The number of writable bytes pointed to by output_char.
 * @return On success, @ref UTFX_ERROR_NONE is returned.
 * @ingroup encoding
 */

utfx_error_t utfx_encoder_get_output_char_safely(const utfx_encoder_t * encoder, void * output_char, unsigned int output_size);

/** Reads and encodes an input character.
 * The output of the encoding is determined by what mode the encoder is in.
 * @param encoder An initialized encoder structure
 * @param input_char A valid UTF-32 character.
 * @returns On success, UTFX_ERROR_NONE is returned.
 * @ingroup encoding
 */

utfx_error_t utfx_encoder_put_input_char(utfx_encoder_t * encoder, utf32_t input_char);

/** Sets the encoding mode of the encoder.
 * @param encoder An initialized encoder structure.
 * @param mode The new mode of the encoder.
 * @ingroup encoding
 */

void utfx_encoder_set_mode(utfx_encoder_t * encoder, utfx_encoder_mode_t mode);

#endif /* UTFX_ENCODER_H */


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

#ifndef LIBUTF_ENCODER_H
#define LIBUTF_ENCODER_H

#include "utf32.h"
#include "error.h"

/** The mode of the encoder.
 * This is a combination of the choice of codec and choice of byte order.
 * @ingroup libutf
 */

typedef enum utf_encoder_mode {
	UTF_ENCODER_MODE_UTF8,
	UTF_ENCODER_MODE_UTF16_LE,
	UTF_ENCODER_MODE_UTF16_BE,
	UTF_ENCODER_MODE_UTF32_LE,
	UTF_ENCODER_MODE_UTF32_BE
} utf_encoder_mode_t;

/** The state of the encoder.
 * Determines if the encoder is taking reads or writes.
 * @ingroup libutf */

typedef enum utf_encoder_state {
	UTF_ENCODER_STATE_READING,
	UTF_ENCODER_STATE_WRITING
} utf_encoder_state_t;

/** A UTF-8, UTF-16 or UTF-32 encoder.
 * It may be used so that, once the mode is set, the encoding of the input text may be abstracted.
 * @ingroup libutf
 */

typedef struct {
	/** The encoding mode of the encoder */
	utf_encoder_mode_t mode;
	/** An output buffer, which contains just enough bytes for any UTF codec */
	unsigned char byte_array[4];
	/** The number of bytes in the output buffer that are part of the encoded character */
	unsigned long int byte_count;
	/** The number of bytes that have been read by the client */
	unsigned long int byte_count_read;
	/** The state of the encoder. */
	utf_encoder_state_t state;
} utf_encoder_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Initializes the members of an encoder structure.
 * Sets the encoding mode to UTF-8.
 * @param encoder An uninitialized encoder structure.
 * @ingroup libutf
 */

void utf_encoder_init(utf_encoder_t * encoder);

/** Returns the mode of the encoder.
 * @param encoder An initialized encoder structure.
 * @returns The current mode of the encoder.
 * @ingroup libutf
 */

utf_encoder_mode_t utf_encoder_get_mode(const utf_encoder_t * encoder);

/** Returns the state of the encoder.
 * @param encoder An initialized encoder structure.
 * @returns The current state of the encoder.
 * @ingroup libutf
 * */

utf_encoder_state_t utf_encoder_get_state(const utf_encoder_t * encoder);

/** Reads the internal output character of the last encoded input character.
 * The encoding of the output character is determined by what mode the encoder is in.
 * The mode of the encoder can be set with the function @ref utf_encoder_set_mode.
 * @param encoder An initialized encoder structure.
 * @param dst The address of where the output character will be written.
 * @param dst_size The number of bytes to read from the encoder.
 * @return The number of bytes read from the encoder.
 */

unsigned long int utf_encoder_read(utf_encoder_t * encoder, void * dst, unsigned long int dst_size);

/** Sets the encoding mode of the encoder.
 * @param encoder An initialized encoder structure.
 * @param mode The new mode of the encoder.
 * @ingroup libutf
 */

void utf_encoder_set_mode(utf_encoder_t * encoder, utf_encoder_mode_t mode);

/** Encodes an input character.
 * The output of the encoding is determined by what mode the encoder is in.
 * @param encoder An initialized encoder structure
 * @param input_char A valid UTF-32 character.
 * @returns On success, UTF_ERROR_NONE is returned.
 * @ingroup libutf
 */

utf_error_t utf_encoder_write(utf_encoder_t * encoder, utf32_t input_char);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* LIBUTF_ENCODER_H */


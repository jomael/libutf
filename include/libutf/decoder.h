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

#ifndef LIBUTF_DECODER_H
#define LIBUTF_DECODER_H

#include "utf32.h"
#include "error.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** The mode of the decoder.
 * This is a combination of the choice of codec and choice of byte order.
 * @ingroup libutf
 */

typedef enum utf_decoder_mode {
	/** Mode is UTF-8 */
	UTF_DECODER_MODE_UTF8,
	/** Mode is UTF-16 (little endian) */
	UTF_DECODER_MODE_UTF16_LE,
	/** Mode is UTF-16 (big endian) */
	UTF_DECODER_MODE_UTF16_BE,
	/** Mode is UTF-32 (little endian) */
	UTF_DECODER_MODE_UTF32_LE,
	/** Mode is UTF-32 (big endian) */
	UTF_DECODER_MODE_UTF32_BE
} utf_decoder_mode_t;

/** The state of the decoder.
 * The state of the decoder describes
 * whether or not it can read input or
 * write output.
 * @ingroup libutf
 */

typedef enum utf_decoder_state {
	/** The decoder is done decoding the data written to it. */
	UTF_DECODER_STATE_DONE = 0,
	/** Alias for @ref UTF_DECODER_STATE_DONE.
	 * @deprecated use @ref UTF_DECODER_STATE_DONE instead */
	UTF_DECODER_STATE_WRITING = 0,
	/** The decoder is reading.
	 * This means there are bytes in the decoder that have not been fully decoded. */
	UTF_DECODER_STATE_READING
} utf_decoder_state_t;

/** A UTF-8, UTF-16 and UTF-32 decoder.
 * It may be used so that, once the mode is set, the decoding of the input text may be abstracted.
 * @ingroup libutf
 */

typedef struct {
	/** The input byte array, containing undecoded input */
	unsigned char input_byte_array[4];
	/** The number of bytes in the input byte array */
	unsigned long int input_byte_count;
	/** The mode of the decoder */
	utf_decoder_mode_t mode;
	/** The last decoded character */
	utf32_t output_char;
	/** The decoder state */
	utf_decoder_state_t state;
} utf_decoder_t;

/** Initializes a decoder structure.
 * @ingroup libutf
 */

void utf_decoder_init(utf_decoder_t * decoder);

/** Returns the mode of the decoder.
 * @param decoder An initialized decoder structure.
 * @returns The current mode of the decoder.
 * @ingroup libutf
 */

utf_decoder_mode_t utf_decoder_get_mode(const utf_decoder_t * decoder);

/** Returns the state of the decoder.
 * @param decoder An initialized decoder structure.
 * @returns The current state of the decoder.
 * @ingroup libutf
 */

utf_decoder_state_t utf_decoder_get_state(const utf_decoder_t * decoder);

/** Reads an output character of the decoder.
 * If the decoder is not accepting reads, this function will fail.
 * If the decoder is accepting reads, it will accept writes after this call.
 * @param decoder An initialized decoder in a state that accepts reading.
 * @param output An address to write the output character to.
 * @returns On success, @ref UTF_ERROR_NONE is returned.
 * @ingroup libutf
 */

utf_error_t utf_decoder_read(utf_decoder_t * decoder, utf32_t * output);

/** Sets the mode of decoder.
 * @ingroup libutf
 */

void utf_decoder_set_mode(utf_decoder_t * decoder, utf_decoder_mode_t mode);

/** Writes a byte array to the decoder.
 * Stops the write operation when a valid sequence is decoded or when an error occurs.
 * @param decoder An initialized decoder structure.
 * @param src The source of data to write to the decoder.
 * @param src_size The number of bytes to send to the decoder.
 * @returns The number of bytes decoded.
 *  If an error occurs during the operation, zero is returned.
 * @ingroup libutf
 */

unsigned int utf_decoder_write(utf_decoder_t * decoder, const void * src, unsigned int src_size);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* LIBUTF_DECODER_H */


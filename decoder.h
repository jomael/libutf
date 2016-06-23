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

#ifndef UTFX_DECODER_H
#define UTFX_DECODER_H

#include "utf32.h"
#include "error.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** The mode of the decoder.
 * This is a combination of the choice of codec and choice of byte order.
 * @ingroup utfx
 */

typedef enum utfx_decoder_mode {
	/** Mode is UTF-8 */
	UTFX_DECODER_MODE_UTF8,
	/** Mode is UTF-16 (little endian) */
	UTFX_DECODER_MODE_UTF16_LE,
	/** Mode is UTF-16 (big endian) */
	UTFX_DECODER_MODE_UTF16_BE,
	/** Mode is UTF-32 (little endian) */
	UTFX_DECODER_MODE_UTF32_LE,
	/** Mode is UTF-32 (big endian) */
	UTFX_DECODER_MODE_UTF32_BE
} utfx_decoder_mode_t;

/** The state of the decoder.
 * The state of the decoder describes
 * whether or not it can read input or
 * write output.
 */

typedef enum utfx_decoder_state {
	/** The decoder is reading. The client can call write functions. */
	UTFX_DECODER_STATE_READING,
	/** The decoder is writing. The client can call read functions. */
	UTFX_DECODER_STATE_WRITING
} utfx_decoder_state_t;

/** A UTF-8, UTF-16 and UTF-32 decoder.
 * It may be used so that, once the mode is set, the decoding of the input text may be abstracted.
 * @ingroup utfx
 */

typedef struct {
	/** The input byte array, containing undecoded input */
	unsigned char input_byte_array[4];
	/** The number of bytes in the input byte array */
	unsigned long int input_byte_count;
	/** The mode of the decoder */
	utfx_decoder_mode_t mode;
	/** The last decoded character */
	utf32_t output_char;
	/** The decoder state */
	utfx_decoder_state_t state;
} utfx_decoder_t;

/** Initializes a decoder structure.
 * @ingroup utfx
 */

void utfx_decoder_init(utfx_decoder_t * decoder);

/** Returns the mode of the decoder.
 * @param decoder An initialized decoder structure.
 * @returns The current mode of the decoder.
 * @ingroup utfx
 */

utfx_decoder_mode_t utfx_decoder_get_mode(const utfx_decoder_t * decoder);

/** Returns the state of the decoder.
 * @param decoder An initialized decoder structure.
 * @returns The current state of the decoder.
 * @ingroup utfx
 */

utfx_decoder_state_t utfx_decoder_get_state(const utfx_decoder_t * decoder);

/** Reads an output character of the decoder.
 * If the decoder is not accepting reads, this function will fail.
 * If the decoder is accepting reads, it will accept writes after this call.
 * @param decoder An initialized decoder in a state that accepts reading.
 * @param output An address to write the output character to.
 * @returns On success, @ref UTFX_ERROR_NONE is returned.
 * @ingroup utfx
 */

utfx_error_t utfx_decoder_read(utfx_decoder_t * decoder, utf32_t * output);

/** Sets the mode of decoder.
 * @ingroup utfx
 */

void utfx_decoder_set_mode(utfx_decoder_t * decoder, utfx_decoder_mode_t mode);

/** Writes a byte array to the decoder.
 * Stops the write operation when a valid sequence is decoded or when an error occurs.
 * @param decoder An initialized decoder structure.
 * @param src The source of data to write to the decoder.
 * @param src_size The number of bytes to send to the decoder.
 * @returns The number of bytes decoded.
 *  If an error occurs during the operation, zero is returned.
 * @ingroup utfx
 */

unsigned int utfx_decoder_write(utfx_decoder_t * decoder, const void * src, unsigned int src_size);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* UTFX_DECODER_H */


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
#include "config.h"
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
	UTF_DECODER_MODE_UTF32_BE,
#ifdef LIBUTF_BIG_ENDIAN
	/** Mode is UTF-16 (native endian) */
	UTF_DECODER_MODE_UTF16 = UTF_DECODER_MODE_UTF16_BE,
	/** Mode is UTF-32 (native endian) */
	UTF_DECODER_MODE_UTF32 = UTF_DECODER_MODE_UTF32_BE
#else
	/** Mode is UTF-16 (native endian) */
	UTF_DECODER_MODE_UTF16 = UTF_DECODER_MODE_UTF16_LE,
	/** Mode is UTF-32 (native endian) */
	UTF_DECODER_MODE_UTF32 = UTF_DECODER_MODE_UTF32_LE
#endif /* LIBUTF_BIG_ENDIAN */
} utf_decoder_mode_t;

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
	/** The decoded characters */
	utf32_t * output_array;
	/** The number of decoded characters */
	unsigned long int output_count;
	/** The number of character slots reserved */
	unsigned long int output_count_res;
} utf_decoder_t;

/** Initializes a decoder structure.
 * @param decoder An uninitialized decoder structure.
 * @ingroup libutf
 */

void utf_decoder_init(utf_decoder_t * decoder);

/** Frees resources allocated by decoder structure.
 * @param decoder An initialized decoder structure.
 * @ingroup libutf
 */

void utf_decoder_free(utf_decoder_t * decoder);

/** Returns the mode of the decoder.
 * @param decoder An initialized decoder structure.
 * @returns The current mode of the decoder.
 * @ingroup libutf
 */

utf_decoder_mode_t utf_decoder_get_mode(const utf_decoder_t * decoder);

/** Reads decoded characters from the decoder.
 * @param decoder An initialized decoder.
 * @param dst_array An address to write the output characters to.
 * @param dst_count The number of UTF-32 characters that can fit in @p dst_array
 * @returns On success, @ref UTF_ERROR_NONE is returned.
 * @ingroup libutf
 */

utf_error_t utf_decoder_read(utf_decoder_t * decoder, utf32_t * dst_array, unsigned long int dst_count);

/** Reserves memory for the decoder's internal character buffer.
 * This can be useful to reduce the number of memory allocations for
 * a series of write operations.
 * @param decoder An initialized decoder structure
 * @param count The number of UTF-32 characters to reserve in memory
 * @returns On success, @ref UTF_ERROR_NONE
 * @ingroup libutf
 */

utf_error_t utf_decoder_reserve(utf_decoder_t * decoder, unsigned long int count);

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


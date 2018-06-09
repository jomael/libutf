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

#include <libutf/codec.h>
#include <libutf/error.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** A UTF-8, UTF-16 and UTF-32 decoder.
 * It may be used so that, once the codec is set, the decoding of the input text may be abstracted.
 * @ingroup libutf
 */

typedef struct {
	/** The input byte array, containing undecoded input */
	unsigned char input_byte_array[4];
	/** The number of bytes in the input byte array */
	unsigned long int input_byte_count;
	/** The codec of the decoder */
	utf_codec_t codec;
	/** The decoded characters */
	char32_t * output_array;
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

/** Returns the number of available decoded characters.
 * @param decoder An initialized decoder structure.
 * @returns The number of decoded characters available.
 * @ingroup libutf
 */

unsigned int utf_decoder_avail(const utf_decoder_t * decoder);

/** Decodes left over input.
 * If the left over input is not a complete sequence, this function fails.
 * This function should be called when no more input will be written to the
 * decoder.
 * @param decoder An initialized decoder structure.
 * @returns On success, it returns @ref UTF_ERROR_NONE.
 * @ingroup libutf
 */

utf_error_t utf_decoder_flush(utf_decoder_t * decoder);

/** Returns the codec of the decoder.
 * @param decoder An initialized decoder structure.
 * @returns The current codec of the decoder.
 * @ingroup libutf
 */

utf_codec_t utf_decoder_get_codec(const utf_decoder_t * decoder);

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

/** Sets the codec of decoder.
 * @ingroup libutf
 */

void utf_decoder_set_codec(utf_decoder_t * decoder, utf_codec_t codec);

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

/** Determines whether or not the decoder needs more data.
 * @param decoder An initialized decoder structure.
 * @returns @ref LIBUTF_TRUE if the decoder needs more
 * data, @ref LIBUTF_FALSE if it does not.
 * @ingroup libutf
 * */

utf_bool_t utf_decoder_needs_data(const utf_decoder_t * decoder);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* LIBUTF_DECODER_H */


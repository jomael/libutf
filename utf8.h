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

/* The following comment tells doxygen to parse the comments of this file. */

/** @file */

#ifndef UTFX_UTF8_H
#define UTFX_UTF8_H

#include "utf32.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup utf8 utf8
 * @brief A collection of low-level routines for the UTF-8 codec.
 */

/** A utf8 character.
 * Used in encoding and decoding of UTF-8 data.
 * @ingroup utf8
 */

typedef uint8_t utf8_t;

/** Decode a UTF-8 sequence.
 * @param in A buffer containing a UTF-8 sequence.
 *  The size of the buffer is calculated by the first byte in the sequence.
 * @param out A pointer to at least a 32 bit data type to store the result.
 * @returns The amount of bytes in the sequence that were decoded.
 * If an error occurs, zero is returned.
 * @ingroup utf8
 */

unsigned int utf8_decode(const utf8_t * in, utf32_t * out);

/** Calculate the expected length of a UTF-8 sequence based on the first byte in the sequence.
 * @param in The first byte in the UTF-8 sequence.
 * @returns The length of the UTF-8 sequence, including the first byte.
 *  If an error occurs, zero is returned.
 * @ingroup utf8
 */

unsigned int utf8_decode_length(utf8_t in);

/** Decode a UTF-8 string.
 * @param in A UTF-8, null terminated string.
 * @param out A pointer to a utf-32 string. It must be large
 * enough to fit the size of the decoding.
 * @returns The number of UTF-8 points decoded.
 *  If an error occurs, zero is returned.
 * @ingroup utf8
 */

unsigned int utf8_decode_string(const utf8_t * in, utf32_t * out);

/** Encode a UTF-8 sequence.
 * @param out A buffer where the result will be stored.
 *  This buffer must be large enough to store the sequence.
 *  The size may be calculated with utf_8_codec_Calculate_Length_Encoded().
 * @param in The character to encode. Must be > 0 and < 0x110000.
 * @returns The amount of bytes written to the buffer.
 *  If an error occurs, zero is returned.
 * @ingroup utf8
 */

unsigned int utf8_encode(utf8_t * out, utf32_t in);

/** Calculate what the sequence length would be of a 32 bit character.
 * @param in A 32 bit character.
 * @returns The length of what the encoded sequence would be.
 *  If an error occurs, zero is returned.
 * @ingroup utf8
 */

unsigned int utf8_encode_length(utf32_t in);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* UTFX_UTF8_H */


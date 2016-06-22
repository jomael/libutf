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

#ifndef UTFX_UTF16_H
#define UTFX_UTF16_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "utf32.h"

/** The UTF-16 data type.
 * Used in the encoding and decoding of UTF-16 data.
 * @ingroup utfx-lowlevel
 */

typedef uint16_t utf16_t;

/** Decode a UTF-16 sequence.
 * @param in A UTF-16 sequence, which may contain one or two elements.
 * @param out The decoded UTF-32 value.
 * @returns The amount of elements in the sequence that were decoded.
 *  If an error occurs, zero is returned.
 * @ingroup utfx-lowlevel
 */

unsigned int utf16_decode(const utf16_t * in, utf32_t * out);

/** Calculate the number of code units that a sequence is made of.
 * @param in The first code unit of a UTF-16 sequence.
 * @returns On success, the number of code units in the sequence.
 *  On error, zero is returned.
 * @ingroup utfx-lowlevel
 */

unsigned int utf16_decode_length(utf16_t in);

/** Encode a UTF-16 sequence.
 * @param in A UTF-32 sequence.
 * @param out A pointer to a UTF-16 sequence, which may contain one or two code units.
 * @returns On success, the number of code units encoded.
 *  On failure, zero is returned.
 * @ingroup utfx-lowlevel
 */

unsigned int utf16_encode(utf32_t in, utf16_t * out);

/** Calculate the number of code units needed to encode a UTF-32 sequence.
 * @param in A UTF-32 sequence.
 * @returns On success, the number of code units needed to encode the sequence.
 *  On failure, zero is returned.
 * @ingroup utfx-lowlevel
 */

unsigned int utf16_encode_length(utf32_t in);

/** Converts a UTF-16BE sequence to the native endian UTF-16 type.
 * @param in The address of the UTF-16BE sequence.
 *  Must be at least two bytes long.
 * @returns The UTF-16 type in the native endian format.
 * @ingroup utfx-lowlevel
 */

utf16_t utf16be(const void * in);

/** Converts a UTF-16LE sequence to the native endian UTF-16 type.
 * @param in The address of the UTF-16LE sequence.
 *  Must be at least two bytes long.
 * @returns The UTF-16 type in the native endian format.
 * @ingroup utfx-lowlevel
 */

utf16_t utf16le(const void * in);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* UTFX_UTF16_H */


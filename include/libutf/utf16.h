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

/* The following comment tells doxygen to parse the comments of this file. */

/** @file */

#ifndef LIBUTF_UTF16_H
#define LIBUTF_UTF16_H

/* for char16_t and char32_t */
#include <uchar.h>

/* for size_t */
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Decode a UTF-16 sequence.
 * @param in A UTF-16 sequence, which may contain one or two elements.
 * @param out The decoded UTF-32 value.
 * @returns The amount of elements in the sequence that were decoded.
 *  If an error occurs, zero is returned.
 * @ingroup libutf-procedural
 */

size_t utf16_decode(const char16_t * in, char32_t * out);

/** Calculate the number of code units that a sequence is made of.
 * @param in The first code unit of a UTF-16 sequence.
 * @returns On success, the number of code units in the sequence.
 *  On error, zero is returned.
 * @ingroup libutf-procedural
 */

size_t utf16_decode_length(char16_t in);

/** Encode a UTF-16 sequence.
 * @param in A UTF-32 sequence.
 * @param out A pointer to a UTF-16 sequence, which may contain one or two code units.
 * @returns On success, the number of code units encoded.
 *  On failure, zero is returned.
 * @ingroup libutf-procedural
 */

size_t utf16_encode(char32_t in, char16_t * out);

/** Calculate the number of code units needed to encode a UTF-32 sequence.
 * @param in A UTF-32 sequence.
 * @returns On success, the number of code units needed to encode the sequence.
 *  On failure, zero is returned.
 * @ingroup libutf-procedural
 */

size_t utf16_encode_length(char32_t in);

/** Converts a UTF-16BE sequence to the native endian UTF-16 type.
 * @param in The address of the UTF-16BE sequence.
 *  Must be at least two bytes long.
 * @returns The UTF-16 type in the native endian format.
 * @ingroup libutf-procedural
 */

char16_t utf16be(const void * in);

/** Converts a UTF-16LE sequence to the native endian UTF-16 type.
 * @param in The address of the UTF-16LE sequence.
 *  Must be at least two bytes long.
 * @returns The UTF-16 type in the native endian format.
 * @ingroup libutf-procedural
 */

char16_t utf16le(const void * in);

/** Calculate the length of a UTF-16 string.
 * The function will stop at the end of the string or at the first error.
 * @param in The UTF-16 string.
 * @param in_size The number of code units occupied by the UTF-16 string.
 * @returns The length of the UTF-16 string, in code points.
 * @ingroup libutf-procedural
 */

size_t utf16_strlen(const char16_t * in, size_t in_size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBUTF_UTF16_H */


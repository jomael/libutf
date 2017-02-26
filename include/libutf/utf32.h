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

#ifndef LIBUTF_UTF32_H
#define LIBUTF_UTF32_H

/* for char32_t */
#include <uchar.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Converts a UTF-32BE sequence to a UTF-32 native endian type.
 * @param src The address of the UTF-32LE sequence.
 * @returns The UTF-32 sequence in native endian format.
 * @ingroup libutf-procedural
 */

char32_t utf32be(const void * src);

/** Converts a UTF-32LE sequence to a UTF-32 native endian type.
 * @param src The address of the UTF-32LE sequence.
 * @returns The UTF-32 sequence in native endian format.
 * @ingroup libutf-procedural
 */

char32_t utf32le(const void * src);

/** Compares two UTF-32 strings.
 * @param a A null-terminated UTF-32 string.
 * @param b A null-terminated UTF-32 string.
 * @returns Zero if the strings are equal.
 *  Returns greater than zero if @p a is greater than @p b.
 *  Returns less than zero if @p a is less than @p b.
 * @ingroup libutf-procedural
 */

int utf32_cmp(const char32_t * a, const char32_t * b);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBUTF_UTF32_H */


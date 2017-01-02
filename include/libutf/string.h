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

#ifndef LIBUTF_STRING_H
#define LIBUTF_STRING_H

#include "error.h"
#include "types.h"

typedef struct utf_string {
	utf_bit_count_t bits;
	utf_unit_count_t count;
	utf_unit_count_t reserved;
	union {
		utf8_t * u8;
		utf16_t * u16;
		utf32_t * u32;
	} data;
	union {
		const utf8_t * u8;
		const utf16_t * u16;
		const utf32_t * u32;
	} data_const;
} utf_string_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void utf_string_init(utf_string_t * string);

void utf_string_free(utf_string_t * string);

utf_unit_count_t utf_string_avail(const utf_string_t * string);

utf_byte_count_t utf_string_byte_count(const utf_string_t * string);

utf_unit_count_t utf_string_unit_count(const utf_string_t * string);

utf_point_count_t utf_string_point_count(const utf_string_t * string);

int utf_string_compare(const utf_string_t * a, const utf_string_t * b);

int utf_string_compare_ascii(const utf_string_t * a, const char * b, utf_byte_count_t b_len);

int utf_string_compare_asciiz(const utf_string_t * a, const char * b);

int utf_string_compare_utf8(const utf_string_t * a, const utf8_t * b, utf_unit_count_t b_len);

int utf_string_compare_utf16(const utf_string_t * a, const utf16_t * b, utf_unit_count_t b_len);

int utf_string_compare_utf32(const utf_string_t * a, const utf32_t * b, utf_unit_count_t b_len);

utf_error_t utf_string_copy(utf_string_t * dst, const utf_string_t * src);

utf_error_t utf_string_copy_ascii(utf_string_t * dst, const char * ascii, utf_byte_count_t ascii_len);

utf_error_t utf_string_copy_asciiz(utf_string_t * dst, const char * asciiz);

utf_error_t utf_string_copy_utf8(utf_string_t * dst, const utf8_t * src, utf_unit_count_t src_len);

utf_error_t utf_string_copy_utf16(utf_string_t * dst, const utf16_t * src, utf_unit_count_t src_len);

utf_error_t utf_string_copy_utf32(utf_string_t * dst, const utf32_t * src, utf_unit_count_t src_len);

utf_error_t utf_string_insert(utf_string_t * dst, const utf_string_t * src, utf_unit_index_t index);

utf_error_t utf_string_insert_ascii(utf_string_t * dst, const char * ascii, utf_byte_count_t ascii_len, utf_unit_index_t index);

utf_error_t utf_string_insert_asciiz(utf_string_t * dst, const char * asciiz, utf_unit_index_t index);

utf_error_t utf_string_insert_utf8(utf_string_t * dst, const utf8_t * src, utf_unit_count_t src_len, utf_unit_index_t index);

utf_error_t utf_string_insert_utf16(utf_string_t * dst, const utf16_t * src, utf_unit_count_t src_len, utf_unit_index_t index);

utf_error_t utf_string_insert_utf32(utf_string_t * dst, const utf32_t * src, utf_unit_count_t src_len, utf_unit_index_t index);

utf_error_t utf_string_reserve(utf_string_t * string, utf_unit_count_t count);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* LIBUTF_STRING_H */


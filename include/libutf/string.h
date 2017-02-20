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

#include <uchar.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct utf_string {
	char32_t * data;
	size_t data_len;
	size_t data_res;
};

void utf_string_init(struct utf_string * string);

void utf_string_free(struct utf_string * string);

int utf_string_compare(const struct utf_string * a, const struct utf_string * b);

int utf_string_compare_utf8(const struct utf_string * a, const char * b);

int utf_string_compare_utf16(const struct utf_string * a, const char16_t * b);

int utf_string_compare_utf32(const struct utf_string * a, const char32_t * b);

int utf_string_copy(struct utf_string * dst, const struct utf_string * src);

int utf_string_copy_utf8(struct utf_string * dst, const char * src);

int utf_string_copy_utf16(struct utf_string * dst, const char16_t * src);

int utf_string_copy_utf32(struct utf_string * dst, const char32_t * src);

int utf_string_insert(struct utf_string * dst, const struct utf_string * src, size_t index);

int utf_string_insert_utf8(struct utf_string * dst, const char * src, size_t index);

int utf_string_insert_utf16(struct utf_string * dst, const char16_t * src, size_t index);

int utf_string_insert_utf32(struct utf_string * dst, const char32_t * src, size_t index);

int utf_string_reserve(struct utf_string * string, size_t count);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* LIBUTF_STRING_H */


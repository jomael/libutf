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

#include "utf8.h"
#include "utf16.h"
#include "utf32.h"

typedef struct utf_string {
	unsigned long int bits;
	unsigned long int count;
	unsigned long int count_res;
	union {
		utf8_t * u8;
		utf16_t * u16;
		utf32_t * u32;
	} u;
} utf_string_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void utf_string_init(utf_string_t * string);

void utf_string_free(utf_string_t * string);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* LIBUTF_STRING_H */


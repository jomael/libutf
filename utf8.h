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

#ifndef UTFX_UTF8_H
#define UTFX_UTF8_H

#include "utf32.h"

typedef uint8_t utf8_t;

int utf8_decode_length(utf8_t in);

int utf8_decode(const utf8_t * in, utf32_t * out);

int utf8_decode_string(const utf8_t * in, utf32_t * out);

int utf8_encode_length(utf32_t in);

int utf8_encode(utf8_t * out, utf32_t in);

#endif


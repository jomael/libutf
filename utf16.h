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

#ifndef UTFX_UTF16_H
#define UTFX_UTF16_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "utf32.h"

typedef uint16_t utf16_t;

int utf16_encode_length(utf32_t in);

int utf16_encode(utf32_t in, utf16_t * out);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* UTFX_UTF16_H */


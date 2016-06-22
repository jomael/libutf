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

#include "utf32.h"

const utf32_t utf32_max = 0x10ffff;

const utf32_t utf32_min = 0x00;

utf32_t utf32be(const void * src){
	utf32_t out32 = 0;
	const unsigned char * src8 = (const unsigned char *)(src);
	out32 |= src8[0] << 0x18;
	out32 |= src8[1] << 0x10;
	out32 |= src8[2] << 0x08;
	out32 |= src8[3] << 0x00;
	return out32;
}

utf32_t utf32le(const void * src){
	utf32_t out32 = 0;
	const unsigned char * src8 = (const unsigned char *)(src);
	out32 |= src8[0] << 0x00;
	out32 |= src8[1] << 0x08;
	out32 |= src8[2] << 0x10;
	out32 |= src8[3] << 0x18;
	return out32;
}


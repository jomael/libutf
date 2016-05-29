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

#include "utf16.h"

int utf16_encode_length(utf32_t in){
	if (in < 0x10000){
		return 1;
	} else if (in < 0x80000000){
		return 2;
	} else {
		return -1;
	}
}

int utf16_encode_le(utf32_t in, utf16_t * out){
	(void) in;
	(void) out;
	return 0;
}


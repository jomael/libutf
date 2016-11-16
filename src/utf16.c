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

#include "utf16.h"

unsigned int utf16_decode_length(utf16_t in){
	if (in < 0xd800 || in > 0xdfff){
		return 1;
	} else if (in >= 0xd800 && in <= 0xdbff){
		return 2;
	}
	/* out of bounds */
	return 0;
}

unsigned int utf16_decode(const utf16_t * in, utf32_t * out){
	if (in[0] < 0xd800 || in[0] > 0xdfff){
		(*out) = in[0];
		return 1;
	} else if ((in[0] >= 0xd800 && in[0] <= 0xdbff)
	        && (in[1] >= 0xdc00 && in[1] <= 0xdfff)){
		(*out)  = (in[0] & 0x03ff) << 0x0a;
		(*out) |= (in[1] & 0x03ff) << 0x00;
		(*out) += 0x010000;
		return 2;
	}
	/* out of bounds */
	return 0;
}

unsigned int utf16_encode_length(utf32_t in){
	if (in <= 0xffff){
		return 1;
	} else if (in <= 0x10ffff){
		return 2;
	} else {
		return 0;
	}
}

unsigned int utf16_encode(utf32_t in, utf16_t * out){

	if (in <= 0xffff){
		out[0] = in & 0xffff;
		out[1] = 0x00;
		return 1;
	} else if (in <= 0x10ffff){
		in -= 0x010000;
		out[0] = 0xd800 | ((in >> 0x0a) & 0x3ff);
		out[1] = 0xdc00 | ((in >> 0x00) & 0x3ff);
		return 2;
	}
	/* out of bounds */
	return 0;
}

utf16_t utf16be(const void * in){
	const unsigned char * in8 = in;
	utf16_t out16 = 0;
	out16 = in8[0] << 0x08;
	out16 |= in8[1];
	return out16;
}

utf16_t utf16le(const void * in){
	const unsigned char * in8 = in;
	utf16_t out16 = 0;
	out16 = in8[0];
	out16 |= in8[1] << 0x08;
	return out16;
}

unsigned int utf16_strlen(const utf16_t * in, unsigned int in_size){
	unsigned int size = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	while (i < in_size){
		j = utf16_decode_length(in[i]);
		if (j == 0){
			break;
		}
		i += j;
		size++;
	}
	return size;
}


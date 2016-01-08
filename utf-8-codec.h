/*
 *    This file is part of Utf8Codec.
 *
 *    Utf8Codec is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    Utf8Codec is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Utf8Codec.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UTF_8_CODEC__UTF_8_CODEC_H
#define UTF_8_CODEC__UTF_8_CODEC_H

int utf8_decode_length(unsigned char in);

int utf8_decode(const unsigned char * in, long int * out);

int utf8_encode_length(signed long int in);

int utf8_encode(unsigned char * out, long int in);

#endif


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

#include <libutf/utf8.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void test_decode(void);

static void test_encode(void);

int main(void){
	test_decode();
	test_encode();
	return EXIT_SUCCESS;
}

static void test_decode(void){
	char in[] = u8"ó";
	char32_t out;
	assert(utf8_decode_length(in[0]) == (sizeof(in) - 1));
	assert(utf8_decode(in, &out) == (sizeof(in) - 1));
	assert(out == U'ó');
}

static void test_encode(void){
	char out[4];
	char out_expected[] = u8"ó";
	assert(utf8_encode_length(U'ó') == (sizeof(out_expected) - 1));
	assert(utf8_encode(U'ó', out) == (sizeof(out_expected) - 1));
	assert(memcmp(out, out_expected, sizeof(out_expected) - 1) == 0);
}


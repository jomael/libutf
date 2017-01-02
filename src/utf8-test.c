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

#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER
#pragma warning(disable : 4710)
#endif /* _MSC_VER */

int utf8_test_decode_length(void);

int utf8_test_encode_length(void);

int utf8_test_decode(void);

int utf8_test_encode(void);

int utf8_test_strlen(void);

int main(void){

	fprintf(stdout, "Running decode length calculation test...");
	if (utf8_test_decode_length() < 0){
		fprintf(stdout, "failed\n");
		return EXIT_FAILURE;
	}
	fprintf(stdout, "passed\n");

	fprintf(stdout, "Running decode test...");
	if (utf8_test_decode() < 0){
		fprintf(stdout, "failed\n");
		return EXIT_FAILURE;
	}
	fprintf(stdout, "passed\n");

	fprintf(stdout, "Running encode test...");
	if (utf8_test_encode() < 0){
		fprintf(stdout, "failed\n");
		return EXIT_FAILURE;
	}
	fprintf(stdout, "passed\n");

	fprintf(stdout, "Running strlen test...");
	if (utf8_test_strlen() < 0){
		fprintf(stdout, "failed\n");
		return EXIT_FAILURE;
	}
	fprintf(stdout, "passed\n");

	return 0;
}

int utf8_test_decode_length(void){

	if (utf8_decode_length(0x00) != 1){
		fprintf(stderr, "length calculation of 0x00 failed\n");
		return -1;
	}

	if (utf8_decode_length(0x7F) != 1){
		fprintf(stderr, "length calculation of 0x7F failed\n");
		return -1;
	}

	if (utf8_decode_length(0xC0) != 2){
		fprintf(stderr, "length calculation of 0xC0 failed\n");
		return -1;
	}

	if (utf8_decode_length(0xE0) != 3){
		fprintf(stderr, "length calculation of 0xE0 failed\n");
		return -1;
	}

	if (utf8_decode_length(0xF0) != 4){
		fprintf(stderr, "length calculation of 0xF0 failed\n");
		return -1;
	}

	if (utf8_decode_length(0xF8) > 0){
		fprintf(stderr, "length calculation of 0xF8 should cause error\n");
		return -1;
	}

	return 0;
}

int utf8_test_encode_length(void){

	if (utf8_encode_length(0x00) != 1){
		fprintf(stderr, "length calculation of 0x00 failed\n");
		return -1;
	}

	if (utf8_encode_length(0x7F) != 1){
		fprintf(stderr, "length calculation of 0x7F failed\n");
		return -1;
	}

	if (utf8_encode_length(0x80) != 2){
		fprintf(stderr, "length calculation of 0x80 failed\n");
		return -1;
	}

	if (utf8_encode_length(0x07FF) != 2){
		fprintf(stderr, "length calculation of 0x07FF failed\n");
		return -1;
	}

	if (utf8_encode_length(0x0800) != 3){
		fprintf(stderr, "length calculation of 0x0800 failed\n");
		return -1;
	}

	if (utf8_encode_length(0xFFFF) != 3){
		fprintf(stderr, "length calculation of 0xFFFF failed\n");
		return -1;
	}

	if (utf8_encode_length(0x010000) != 4){
		fprintf(stderr, "length calculation of 0x01000 failed\n");
		return -1;
	}

	if (utf8_encode_length(0x10FFFF) != 4){
		fprintf(stderr, "length calculation of 0x10FFFF failed\n");
		return -1;
	}

	if (utf8_encode_length(0x110000) > 0){
		fprintf(stderr, "length calculation of 0x110000 should cause error\n");
		return -1;
	}

	return 0;
}

int utf8_test_decode(void){

	utf8_t test_buffer[4];

	utf32_t test_c = 0;

	test_buffer[0] = 0x00;
	if (utf8_decode(test_buffer, &test_c) == 0 || test_c != 0x00){
		fprintf(stderr, "failed to decode 0x00\n");
		return -1;
	}

	test_buffer[0] = 0x7F;
	if (utf8_decode(test_buffer, &test_c) == 0 || test_c != 0x7F){
		fprintf(stderr, "failed to decode 0x7F\n");
		return -1;
	}

	test_buffer[0] = 0xC2;
	test_buffer[1] = 0x80;
	if (utf8_decode(test_buffer, &test_c) == 0 || test_c != 0x80){
		fprintf(stderr, "failed to decode 0x80\n");
		return -1;
	}

	test_buffer[0] = 0xDF;
	test_buffer[1] = 0xBF;
	if (utf8_decode(test_buffer, &test_c) == 0 || test_c != 0x07FF){
		fprintf(stderr, "failed to decode 0x07FF\n");
		return -1;
	}

	test_buffer[0] = 0xE0;
	test_buffer[1] = 0xA0;
	test_buffer[2] = 0x80;
	if (utf8_decode(test_buffer, &test_c) == 0 || test_c != 0x0800){
		fprintf(stderr, "failed to decode 0x0800\n");
		return -1;
	}

	test_buffer[0] = 0xEF;
	test_buffer[1] = 0xBF;
	test_buffer[2] = 0xBF;
	if (utf8_decode(test_buffer, &test_c) == 0 || test_c != 0xFFFF){
		fprintf(stderr, "failed to decode 0xFFFF\n");
		return -1;
	}

	test_buffer[0] = 0xF0;
	test_buffer[1] = 0x90;
	test_buffer[2] = 0x80;
	test_buffer[3] = 0x80;
	if (utf8_decode(test_buffer, &test_c) == 0 || test_c != 0x010000){
		fprintf(stderr, "failed to decode 0x010000\n");
		return -1;
	}

	test_buffer[0] = 0xF7;
	test_buffer[1] = 0xBF;
	test_buffer[2] = 0xBF;
	test_buffer[3] = 0xBF;
	if (utf8_decode(test_buffer, &test_c) == 0 || test_c != 0x1FFFFF){
		fprintf(stderr, "failed to decode 0x1FFFFF\n");
		return -1;
	}

	/* check to make sure that this fails */
	test_buffer[0] = 0xF8;
	if (utf8_decode(test_buffer, &test_c) > 0){
		fprintf(stderr, "decode did not fail in an out of bounds encoding\n");
		return -1;
	}

	return 0;
}

int utf8_test_encode(void){

	utf8_t test_buffer[4];

	utf32_t test_c = 0;

	test_c = 0x00;
	if (utf8_encode(test_c, test_buffer) == 0 || test_buffer[0] != 0x00){
		fprintf(stderr, "failed to encode 0x00\n");
		return -1;
	}

	test_c = 0x7F;
	if (utf8_encode(test_c, test_buffer) == 0 || test_buffer[0] != 0x7F){
		fprintf(stderr, "failed to encode 0x7F\n");
		return -1;
	}

	test_c = 0x80;
	if (utf8_encode(test_c, test_buffer) == 0
	 || test_buffer[0] != 0xC2 || test_buffer[1] != 0x80){
		fprintf(stderr, "failed to encode 0x80\n");
		return -1;
	}

	test_c = 0x07FF;
	if (utf8_encode(test_c, test_buffer) == 0
	 || test_buffer[0] != 0xDF || test_buffer[1] != 0xBF){
		fprintf(stderr, "failed to encode 0x07FF\n");
		return -1;
	}

	test_c = 0x0800;
	if (utf8_encode(test_c, test_buffer) == 0 || test_buffer[0] != 0xE0
	 || test_buffer[1] != 0xA0 || test_buffer[2] != 0x80){
		fprintf(stderr, "failed to encode 0x0800\n");
		return -1;
	}

	test_c = 0xFFFF;
	if (utf8_encode(test_c, test_buffer) == 0 || test_buffer[0] != 0xEF
	 || test_buffer[1] != 0xBF || test_buffer[2] != 0xBF){
		fprintf(stderr, "failed to encode 0xFFFF\n");
		return -1;
	}

	test_c = 0x010000;
	if (utf8_encode(test_c, test_buffer) == 0
	 || test_buffer[0] != 0xF0 || test_buffer[1] != 0x90
	 || test_buffer[2] != 0x80 || test_buffer[3] != 0x80){
		fprintf(stderr, "failed to encode 0x010000\n");
		return -1;
	}

	test_c = 0x10FFFF;
	if (utf8_encode(test_c, test_buffer) == 0
	 || test_buffer[0] != 0xF4 || test_buffer[1] != 0x8F
	 || test_buffer[2] != 0xBF || test_buffer[3] != 0xBF){
		fprintf(stderr, "failed to encode 0x10FFFF\n");
		return -1;
	}

	test_c = 0x110000;
	if (utf8_encode(test_c, test_buffer) > 0){
		fprintf(stderr, "encoding did not fail on 0x110000\n");
		return -1;
	}

	return 0;
}

int utf8_test_strlen(void){
	const utf8_t in[] = {
		0xC2, 0xA2,
		0x24,
		0xE2, 0x82, 0xAC,
		0xF0, 0x90, 0x8D, 0x88 };
	if (utf8_strlen(in, sizeof(in)) != 4){
		fprintf(stderr, "strlen failed\n");
		return -1;
	}
	return 0;
}


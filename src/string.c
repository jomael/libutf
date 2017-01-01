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

#include <libutf/string.h>
#include <libutf/iterator.h>

#include <stdlib.h>
#include <string.h>

void utf_string_init(utf_string_t * string){
	string->bits = 8;
	string->count = 0;
	string->count_res = 0;
	string->u.u8 = NULL;
}

void utf_string_free(utf_string_t * string){
	if (string != NULL){
		free(string->u.u8);
	}
}

unsigned long int utf_string_avail(const utf_string_t * string){
	return string->count_res - string->count;
}

utf_byte_count_t utf_string_byte_count(const utf_string_t * string){
	return (string->count * string->bits) / 8;
}

utf_unit_count_t utf_string_unit_count(const utf_string_t * string){
	return string->count;
}

utf_point_count_t utf_string_point_count(const utf_string_t * string){
	utf_point_count_t count = 0;
	utf_iterator_t it;
	utf_iterator_init(&it, string);
	while (utf_iterator_end(&it) == LIBUTF_FALSE){
		utf_iterator_next(&it);
		count++;
	}
	return count;
}

int utf_string_compare(const utf_string_t * a, const utf_string_t * b){

	utf32_t ch_a;
	utf32_t ch_b;
	utf_iterator_t it_a;
	utf_iterator_t it_b;

	utf_iterator_init(&it_a, a);
	utf_iterator_init(&it_b, b);

	while (1){
		if (utf_iterator_end(&it_a)
		 || utf_iterator_end(&it_b)){
			break;
		}

		ch_a = utf_iterator_get(&it_a);
		ch_b = utf_iterator_get(&it_b);

		if (ch_a < ch_b){
			return -1;
		} else if (ch_a > ch_b){
			return 1;
		}

		utf_iterator_next(&it_a);
		utf_iterator_next(&it_b);
	}

	if (utf_iterator_end(&it_a)
	&& !utf_iterator_end(&it_b)){
		return -1;
	} else if (!utf_iterator_end(&it_a)
	         && utf_iterator_end(&it_b)){
		return 1;
	}

	return 0;
}

utf_error_t utf_string_copy(utf_string_t * dst, const utf_string_t * src){
	unsigned long int size = 0;
	if (dst->u.u8 != NULL){
		free(dst->u.u8);
	}
	dst->bits = src->bits;
	dst->count = src->count;
	dst->count_res = src->count_res;
	if (dst->bits == 8){
		size = dst->count;
	} else if (dst->bits == 16){
		size = dst->count * 2;
	} else if (dst->bits == 32){
		size = dst->count * 4;
	}
	dst->u.u8 = malloc(size);
	if ((dst->u.u8 == NULL) && (size > 0)){
		return UTF_ERROR_MALLOC;
	}
	memcpy(dst->u.u8, src->u.u8, size);
	return UTF_ERROR_NONE;
}

utf_error_t utf_string_copy_utf8(utf_string_t * dst, const utf8_t * src, unsigned long int src_len){
	if (dst->u.u8 != NULL){
		free(dst->u.u8);
	}
	dst->bits = 8;
	dst->count = src_len;
	dst->count_res = 0;
	dst->u.u8 = malloc(src_len);
	if (dst->u.u8 == NULL){
		return UTF_ERROR_MALLOC;
	}
	memcpy(dst->u.u8, src, src_len);
	return UTF_ERROR_NONE;
}

utf_error_t utf_string_insert(utf_string_t * dst, unsigned long int pos, const utf_string_t * src){

	if (pos > dst->count){
		return UTF_ERROR_BOUNDARY;
	}

	if (utf_string_avail(dst) < src->count){
		utf_error_t error;
		error = utf_string_reserve(dst, src->count);
		if (error){
			return error;
		}
	}

	return UTF_ERROR_NONE;
}

utf_error_t utf_string_reserve(utf_string_t * string, unsigned long int count){

	utf8_t * tmp;
	unsigned long int size;

	size = (count * string->bits) / 8;

	tmp = realloc(string->u.u8, size);
	if ((tmp == NULL) && (count > 0)){
		return UTF_ERROR_MALLOC;
	}

	string->u.u8 = tmp;
	string->count_res = count;
	if (count < string->count){
		string->count = count;
	}

	return UTF_ERROR_NONE;
}


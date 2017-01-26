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

#include <libutf/utf8.h>
#include <libutf/utf16.h>

#include <stdlib.h>
#include <string.h>

void utf_string_init(utf_string_t * string){
	string->bits = 8;
	string->count = 0;
	string->reserved = 0;
	string->data.u8 = NULL;
	string->data_const.u8 = NULL;
}

void utf_string_free(utf_string_t * string){
	if (string != NULL){
		free(string->data.u8);
	}
}

static void utf_string_assign_ascii(utf_string_t * string, const char * ascii, utf_byte_count_t ascii_len){
	string->bits = 8;
	string->count = ascii_len;
	string->reserved = ascii_len;
	string->data.u8 = NULL;
	string->data_const.u8 = (const utf8_t *)(ascii);
}

static void utf_string_assign_utf8(utf_string_t * string, const utf8_t * src, utf_unit_count_t src_len){
	string->bits = 8;
	string->count = src_len;
	string->reserved = src_len;
	string->data.u8 = NULL;
	string->data_const.u8 = src;
}

static void utf_string_assign_utf16(utf_string_t * string, const utf16_t * src, utf_unit_count_t src_len){
	string->bits = 16;
	string->count = src_len;
	string->reserved = src_len;
	string->data.u16 = NULL;
	string->data_const.u16 = src;
}

static void utf_string_assign_utf32(utf_string_t * string, const utf32_t * src, utf_unit_count_t src_len){
	string->bits = 32;
	string->count = src_len;
	string->reserved = src_len;
	string->data.u32 = NULL;
	string->data_const.u32 = src;
}

utf_unit_count_t utf_string_avail(const utf_string_t * string){
	return string->reserved - string->count;
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

int utf_string_compare_ascii(const utf_string_t * a, const char * b, utf_byte_count_t b_len){
	utf_string_t b2;
	utf_string_assign_ascii(&b2, b, b_len);
	return utf_string_compare(a, &b2);
}

int utf_string_compare_asciiz(const utf_string_t * a, const char * b){
	return utf_string_compare_ascii(a, b, strlen(b));
}

int utf_string_compare_utf8(const utf_string_t * a, const utf8_t * b, utf_unit_count_t b_len){
	utf_string_t b2;
	utf_string_assign_utf8(&b2, b, b_len);
	return utf_string_compare(a, &b2);
}

int utf_string_compare_utf16(const utf_string_t * a, const utf16_t * b, utf_unit_count_t b_len){
	utf_string_t b2;
	utf_string_assign_utf16(&b2, b, b_len);
	return utf_string_compare(a, &b2);
}

int utf_string_compare_utf32(const utf_string_t * a, const utf32_t * b, utf_unit_count_t b_len){
	utf_string_t b2;
	utf_string_assign_utf32(&b2, b, b_len);
	return utf_string_compare(a, &b2);
}

utf_error_t utf_string_copy(utf_string_t * dst, const utf_string_t * src){
	unsigned long int size = 0;
	if (dst->data.u8 != NULL){
		free(dst->data.u8);
	}
	dst->bits = src->bits;
	dst->count = src->count;
	dst->reserved = src->reserved;
	if (dst->bits == 8){
		size = dst->count;
	} else if (dst->bits == 16){
		size = dst->count * 2;
	} else if (dst->bits == 32){
		size = dst->count * 4;
	}
	dst->data.u8 = malloc(size);
	if ((dst->data.u8 == NULL) && (size > 0)){
		return UTF_ERROR_MALLOC;
	}
	dst->data_const.u8 = dst->data.u8;
	memcpy(dst->data.u8, src->data_const.u8, size);
	return UTF_ERROR_NONE;
}

utf_error_t utf_string_copy_ascii(utf_string_t * dst, const char * src, utf_byte_count_t src_len){
	utf_string_t src2;
	utf_string_assign_ascii(&src2, src, src_len);
	return utf_string_copy(dst, &src2);
}

utf_error_t utf_string_copy_asciiz(utf_string_t * dst, const char * asciiz){
	return utf_string_copy_ascii(dst, asciiz, strlen(asciiz));
}

utf_error_t utf_string_copy_utf8(utf_string_t * dst, const utf8_t * src, unsigned long int src_len){
	utf_string_t src2;
	utf_string_assign_utf8(&src2, src, src_len);
	return utf_string_copy(dst, &src2);
}

utf_error_t utf_string_copy_utf16(utf_string_t * dst, const utf16_t * src, unsigned long int src_len){
	utf_string_t src2;
	utf_string_assign_utf16(&src2, src, src_len);
	return utf_string_copy(dst, &src2);
}

utf_error_t utf_string_copy_utf32(utf_string_t * dst, const utf32_t * src, unsigned long int src_len){
	utf_string_t src2;
	utf_string_assign_utf32(&src2, src, src_len);
	return utf_string_copy(dst, &src2);
}

utf_error_t utf_string_insert(utf_string_t * dst, const utf_string_t * src, utf_unit_index_t index){

	utf_byte_index_t byte_index;
	utf_byte_count_t dst_size;
	utf_byte_count_t src_size;
	utf_unit_count_t i;
	utf_unit_count_t j = 0;

	if (index > dst->count){
		return UTF_ERROR_BOUNDARY;
	}

	if (utf_string_avail(dst) < src->count){
		utf_error_t error;
		error = utf_string_reserve(dst, dst->count + src->count);
		if (error){
			return error;
		}
	}

	byte_index = (index * dst->bits) / 8;
	dst_size = utf_string_byte_count(dst);
	src_size = utf_string_byte_count(src);

	memmove(&dst->data.u8[byte_index + src_size],
	        &dst->data.u8[byte_index],
	        dst_size - byte_index);

	i = 0;
	while (i < src->count){

		utf32_t ch = 0;

		if (src->bits == 8){
			j = utf8_decode(&src->data_const.u8[i], &ch);
			if (j == 0){
				return UTF_ERROR_INVALID_SEQUENCE;
			}
		} else if (src->bits == 16){
			j = utf16_decode(&src->data_const.u16[i], &ch);
			if (j == 0){
				return UTF_ERROR_INVALID_SEQUENCE;
			}
		} else if (src->bits == 32){
			ch = src->data_const.u32[i];
			j = 1;
		}

		if (dst->bits == 8){
			utf8_encode(ch, &dst->data.u8[index + i]);
		} else if (dst->bits == 16){
			utf16_encode(ch, &dst->data.u16[index + i]);
		} else if (dst->bits == 32){
			dst->data.u32[index + i] = ch;
		}

		i += j;
	}

	dst->count += i;

	return UTF_ERROR_NONE;
}

utf_error_t utf_string_insert_ascii(utf_string_t * dst, const char * ascii, utf_byte_count_t ascii_len, utf_unit_index_t index){
	utf_string_t src;
	utf_string_assign_ascii(&src, ascii, ascii_len);
	return utf_string_insert(dst, &src, index);
}

utf_error_t utf_string_insert_asciiz(utf_string_t * dst, const char * asciiz, utf_unit_index_t index){
	return utf_string_insert_ascii(dst, asciiz, strlen(asciiz), index);
}

utf_error_t utf_string_insert_utf8(utf_string_t * dst, const utf8_t * src, utf_unit_count_t src_len, utf_unit_index_t index){
	utf_string_t src2;
	utf_string_assign_utf8(&src2, src, src_len);
	return utf_string_insert(dst, &src2, index);
}

utf_error_t utf_string_insert_utf16(utf_string_t * dst, const utf16_t * src, utf_unit_count_t src_len, utf_unit_index_t index){
	utf_string_t src2;
	utf_string_assign_utf16(&src2, src, src_len);
	return utf_string_insert(dst, &src2, index);
}

utf_error_t utf_string_insert_utf32(utf_string_t * dst, const utf32_t * src, utf_unit_count_t src_len, utf_unit_index_t index){
	utf_string_t src2;
	utf_string_assign_utf32(&src2, src, src_len);
	return utf_string_insert(dst, &src2, index);
}

utf_error_t utf_string_reserve(utf_string_t * string, unsigned long int count){

	utf8_t * tmp;
	unsigned long int size;

	size = (count * string->bits) / 8;

	tmp = realloc(string->data.u8, size);
	if ((tmp == NULL) && (count > 0)){
		return UTF_ERROR_MALLOC;
	}

	string->data.u8 = tmp;
	string->data_const.u8 = tmp;
	string->reserved = count;
	if (count < string->count){
		string->count = count;
	}

	return UTF_ERROR_NONE;
}


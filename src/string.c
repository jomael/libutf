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

#include <libutf/utf8.h>
#include <libutf/utf16.h>
#include <libutf/codec.h>

#include <stdlib.h>
#include <string.h>

/** Initializes the string.
 * @param string An unitialized string.
 * @ingroup libutf
 */

void utf_string_init(struct utf_string * string){
	string->data = NULL;
	string->data_len = 0;
	string->data_res = 0;
}

/** Releases memory allocated by string.
 * This function is safe from double frees.
 * @param string An initialized string.
 * @ingroup libutf
 */

void utf_string_free(struct utf_string * string){
	if (string != NULL){
		free(string->data);
		string->data = NULL;
	}
}

int utf_string_compare(const struct utf_string * a, const struct utf_string * b){

	unsigned long int min_size;

	if (a->data_len < b->data_len){
		min_size = a->data_len;
	} else {
		min_size = b->data_len;
	}

	min_size *= sizeof(char32_t);

	return memcmp(a->data, b->data, min_size);
}

int utf_string_compare_utf8(const struct utf_string * a, const char * b){
	(void) a;
	(void) b;
	return 0;
}

int utf_string_compare_utf16(const struct utf_string * a, const char16_t * b){
	(void) a;
	(void) b;
	return 0;
}

int utf_string_compare_utf32(const struct utf_string * a, const char32_t * b){

	size_t i;

	for (i = 0; i < a->data_len; i++){
		if (a->data[i] > b[i]){
			return 1;
		} else if (a->data[i] < b[i]){
			return -1;
		} else if (!b[i]){
			break;
		}
	}

	return 0;
}

/** Copies the contents of @p src to @p dst.
 * This function initializes @p dst, and does not attempt
 * to free any data allocated in it.
 * @param dst An unitialized @ref utf_string.
 * @param src An initialized @ref utf_string.
 * @returns On success, zero is returned.
 *  If a memory allocation fails, ENOMEM is returned.
 * @ingroup libutf
 */

int utf_string_copy(struct utf_string * dst, const struct utf_string * src){
	dst->data = malloc(src->data_res);
	if (dst->data == NULL){
		return ENOMEM;
	}
	dst->data_len = src->data_len;
	dst->data_res = src->data_res;
	memcpy(dst->data, src->data, src->data_len * sizeof(char32_t));
	dst->data[dst->data_len] = 0;
	return 0;
}

int utf_string_copy_utf8(struct utf_string * dst, const char * src){
	(void) dst;
	(void) src;
	return 0;
}

int utf_string_copy_utf16(struct utf_string * dst, const char16_t * src){
	(void) dst;
	(void) src;
	return 0;
}

int utf_string_copy_utf32(struct utf_string * dst, const char32_t * src){

	size_t src_len = 0;

	while (src[src_len] != 0){
		src_len++;
	}

	dst->data = malloc(src_len + 1);
	if (dst->data == NULL){
		return ENOMEM;
	}
	dst->data_len = src_len;
	dst->data_res = src_len + 1;
	memcpy(dst->data, src, src_len * sizeof(char32_t));
	dst->data[src_len] = 0;
	return 0;
}

int utf_string_insert(struct utf_string * dst, const struct utf_string * src, size_t index){

	int err;

	if ((dst->data_len + src->data_len) > dst->data_res){
		err = utf_string_reserve(dst, dst->data_len + src->data_len + 1);
		if (err != 0){
			return err;
		}
	}

	memmove(&dst->data[index + src->data_len],
	        &dst->data[index],
	        (dst->data_len - index) * sizeof(char32_t));

	memcpy(&dst->data[index],
	       src->data,
	       src->data_len * sizeof(char32_t));

	dst->data_len += src->data_len;

	dst->data[dst->data_len] = 0;

	return 0;
}

int utf_string_insert_utf8(struct utf_string * dst, const char * src, size_t index){
	(void) dst;
	(void) src;
	(void) index;
	return 0;
}

int utf_string_insert_utf16(struct utf_string * dst, const char16_t * src, size_t index){
	(void) dst;
	(void) src;
	(void) index;
	return 0;
}

int utf_string_insert_utf32(struct utf_string * dst, const char32_t * src, size_t index){
	(void) dst;
	(void) src;
	(void) index;
	return 0;
}

int utf_string_reserve(struct utf_string * string, size_t count){

	char32_t * tmp;
	size_t size;

	size = count * sizeof(char32_t);

	tmp = realloc(string->data, size);
	if ((tmp == NULL) && (count > 0)){
		return ENOMEM;
	}

	string->data = tmp;
	string->data_res = count;

	if (count == 0){
		string->data_len = 0;
		return 0;
	}

	if (string->data_len > string->data_res){
		/* minus one because null terminator doesn't count */
		string->data_len = string->data_res - 1;
		/* add null terminator */
		string->data[string->data_len] = 0;
	}

	return 0;
}

const struct utf_string utf8_name = { U"UTF-8", 5, 5 };

const struct utf_string utf16le_name = { U"UTF-16LE", 8, 8 };

const struct utf_string utf16be_name = { U"UTF-16BE", 8, 8 };

const struct utf_string utf32le_name = { U"UTF-32LE", 8, 8 };

const struct utf_string utf32be_name = { U"UTF-32BE", 8, 8 };

const struct utf_string * utf_codec_to_string(utf_codec_t codec){
	switch (codec){
	case UTF_CODEC_UTF8:
		return &utf8_name;
	case UTF_CODEC_UTF16_LE:
		return &utf16le_name;
	case UTF_CODEC_UTF16_BE:
		return &utf16be_name;
	case UTF_CODEC_UTF32_LE:
		return &utf32le_name;
	case UTF_CODEC_UTF32_BE:
		return &utf32be_name;
	default:
		break;
	}
	return NULL;
}


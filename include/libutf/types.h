#ifndef LIBUTF_TYPES_H
#define LIBUTF_TYPES_H

#include <stdlib.h>
#include <limits.h>
#include <uchar.h>

#define LIBUTF_UTF8_MAX 0xf7
#define LIBUTF_UTF8_MIN 0

typedef char utf8_t;

#define LIBUTF_UTF16_MAX 0xffff
#define LIBUTF_UTF16_MIN 0

typedef char16_t utf16_t;

#define LIBUTF_UTF32_MAX 0x10ffff
#define LIBUTF_UTF32_MIN 0

typedef char32_t utf32_t;

#define LIBUTF_TRUE 1
#define LIBUTF_FALSE 0

typedef unsigned char utf_bool_t;

#define LIBUTF_BIT_COUNT_MAX SIZE_MAX
#define LIBUTF_BIT_COUNT_MIN 0UL

typedef size_t utf_bit_count_t;

#define LIBUTF_BYTE_COUNT_MAX (SIZE_MAX / 8UL)
#define LIBUTF_BYTE_COUNT_MIN 0UL

typedef size_t utf_byte_count_t;

#define LIBUTF_UNIT_COUNT_MAX (SIZE_MAX / 32UL)
#define LIBUTF_UNIT_COUNT_MIN 0UL

typedef size_t utf_unit_count_t;

#define LIBUTF_POINT_COUNT_MAX (SIZE_MAX / 32UL)
#define LIBUTF_POINT_COUNT_MIN 0UL

typedef size_t utf_point_count_t;

#define LIBUTF_BYTE_INDEX_MAX LIBUTF_BYTE_COUNT_MAX
#define LIBUTF_BYTE_INDEX_MIN LIBTUF_BYTE_COUNT_MIN

typedef size_t utf_byte_index_t;

#define LIBUTF_UNIT_INDEX_MAX LIBUTF_UNIT_COUNT_MAX
#define LIBUTF_UNIT_INDEX_MIN LIBTUF_UNIT_COUNT_MIN

typedef size_t utf_unit_index_t;

#define LIBUTF_POINT_INDEX_MAX LIBUTF_POINT_COUNT_MAX
#define LIBUTF_POINT_INDEX_MIN LIBTUF_POINT_COUNT_MIN

typedef size_t utf_point_index_t;

#endif /* LIBUTF_TYPES_H */


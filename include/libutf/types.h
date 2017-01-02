#ifndef LIBUTF_TYPES_H
#define LIBUTF_TYPES_H

#include <limits.h>

#define LIBUTF_TRUE 1
#define LIBUTF_FALSE 0

typedef unsigned char utf_bool_t;

#define LIBUTF_BIT_COUNT_MAX ULONG_MAX
#define LIBUTF_BIT_COUNT_MIN 0UL

typedef unsigned long int utf_bit_count_t;

#define LIBUTF_BYTE_COUNT_MAX (ULONG_MAX / 8UL)
#define LIBUTF_BYTE_COUNT_MIN 0UL

typedef unsigned long int utf_byte_count_t;

#define LIBUTF_UNIT_COUNT_MAX (ULONG_MAX / 32UL)
#define LIBUTF_UNIT_COUNT_MIN 0UL

typedef unsigned long int utf_unit_count_t;

#define LIBUTF_POINT_COUNT_MAX (ULONG_MAX / 32UL)
#define LIBUTF_POINT_COUNT_MIN 0UL

typedef unsigned long int utf_point_count_t;

#define LIBUTF_BYTE_INDEX_MAX LIBUTF_BYTE_COUNT_MAX
#define LIBUTF_BYTE_INDEX_MIN LIBTUF_BYTE_COUNT_MIN

typedef unsigned long int utf_byte_index_t;

#define LIBUTF_UNIT_INDEX_MAX LIBUTF_UNIT_COUNT_MAX
#define LIBUTF_UNIT_INDEX_MIN LIBTUF_UNIT_COUNT_MIN

typedef unsigned long int utf_unit_index_t;

#define LIBUTF_POINT_INDEX_MAX LIBUTF_POINT_COUNT_MAX
#define LIBUTF_POINT_INDEX_MIN LIBTUF_POINT_COUNT_MIN

typedef unsigned long int utf_point_index_t;

#endif /* LIBUTF_TYPES_H */


#ifndef LIBUTF_IFSTREAM_H
#define LIBUTF_IFSTREAM_H

#include <libutf/istream.h>

typedef struct utf_ifstream {
	utf_istream_t istream;
} utf_ifstream_t;

void utf_ifstream_init(utf_ifstream_t * ifstream);

void utf_ifstream_free(utf_ifstream_t * ifstream);

utf_error_t utf_ifstream_open(utf_ifstream_t * ifstream, const char * path);

utf_unit_count_t utf_ifstream_read_utf8(utf_ifstream_t * ifstream, utf8_t * data, utf_unit_count_t data_max);

utf_unit_count_t utf_ifstream_read_utf16(utf_ifstream_t * ifstream, utf8_t * data, utf_unit_count_t data_max);

utf_unit_count_t utf_ifstream_read_utf32(utf_ifstream_t * ifstream, utf8_t * data, utf_unit_count_t data_max);

#endif /* LIBUTF_IFSTREAM_H */


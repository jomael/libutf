#ifndef LIBUTF_IFSTREAM_H
#define LIBUTF_IFSTREAM_H

#include <libutf/ostream.h>

typedef struct utf_ofstream {
	utf_istream_t istream;
} utf_ofstream_t;

void utf_ofstream_init(utf_ofstream_t * ofstream);

void utf_ofstream_free(utf_ofstream_t * ofstream);

utf_error_t utf_ofstream_open(utf_ofstream_t * ofstream, const char * path);

#endif /* LIBUTF_IFSTREAM_H */


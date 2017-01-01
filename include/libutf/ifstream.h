#ifndef LIBUTF_IFSTREAM_H
#define LIBUTF_IFSTREAM_H

#include <libutf/istream.h>

typedef struct utf_ifstream {
	utf_istream_t istream;
} utf_ifstream_t;

void utf_ifstream_init(utf_ifstream_t * ifstream);

void utf_ifstream_free(utf_ifstream_t * ifstream);

utf_error_t utf_ifstream_open(utf_ifstream_t * ifstream, const char * path);

#endif /* LIBUTF_IFSTREAM_H */


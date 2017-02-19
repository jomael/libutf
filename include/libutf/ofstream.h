#ifndef LIBUTF_OFSTREAM_H
#define LIBUTF_OFSTREAM_H

#include <libutf/ostream.h>

typedef struct utf_ofstream {
	utf_ostream_t ostream;
} utf_ofstream_t;

void utf_ofstream_init(utf_ofstream_t * ofstream);

void utf_ofstream_free(utf_ofstream_t * ofstream);

utf_error_t utf_ofstream_open(utf_ofstream_t * ofstream, const char * path);

utf_unit_count_t utf_ofstream_write(utf_ofstream_t * ofstream, const utf_string_t * string);

utf_unit_count_t utf_ofstream_write_asciiz(utf_ofstream_t * ofstream, const char * asciiz_str);

/** The UTF stdout equivalent */

extern utf_ofstream_t utf_stdout;

void utf_stdout_init(utf_ofstream_t * ofstream);

/** The UTF stderr equivalent */

extern utf_ofstream_t utf_stderr;

void utf_stderr_init(utf_ofstream_t * ofstream);

#endif /* LIBUTF_OFSTREAM_H */


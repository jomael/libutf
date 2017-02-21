#ifndef LIBUTF_OFSTREAM_H
#define LIBUTF_OFSTREAM_H

#include <libutf/ostream.h>

struct utf_ofstream {
	struct utf_ostream ostream;
};

void utf_ofstream_init(struct utf_ofstream * ofstream);

void utf_ofstream_free(struct utf_ofstream * ofstream);

int utf_ofstream_open(struct utf_ofstream * ofstream, const char * path);

size_t utf_ofstream_write(struct utf_ofstream * ofstream, const struct utf_string * string);

size_t utf_ofstream_write_utf8(struct utf_ofstream * ofstream, const char * string);

size_t utf_ofstream_write_utf16(struct utf_ofstream * ofstream, const char16_t * string);

size_t utf_ofstream_write_utf32(struct utf_ofstream * ofstream, const char32_t * string);

/** The UTF stdout equivalent */

extern struct utf_ofstream utf_stdout;

void utf_stdout_init(struct utf_ofstream * ofstream);

/** The UTF stderr equivalent */

extern struct utf_ofstream utf_stderr;

void utf_stderr_init(struct utf_ofstream * ofstream);

#endif /* LIBUTF_OFSTREAM_H */


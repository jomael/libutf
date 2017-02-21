#ifndef LIBUTF_IFSTREAM_H
#define LIBUTF_IFSTREAM_H

#include <libutf/istream.h>

struct utf_ifstream {
	struct utf_istream istream;
};

void utf_ifstream_init(struct utf_ifstream * ifstream);

void utf_ifstream_free(struct utf_ifstream * ifstream);

utf_codec_t utf_ifstream_get_codec(const struct utf_ifstream * ifstream);

int utf_ifstream_open(struct utf_ifstream * ifstream, const char * path);

size_t utf_ifstream_read_utf8(struct utf_ifstream * ifstream, char * data, size_t data_max);

size_t utf_ifstream_read_utf16(struct utf_ifstream * ifstream, char16_t * data, size_t data_max);

size_t utf_ifstream_read_utf32(struct utf_ifstream * ifstream, char32_t * data, size_t data_max);

void utf_ifstream_set_codec(struct utf_ifstream * ifstream, utf_codec_t codec);

/** The UTF version of the stdin handle.
 */

extern struct utf_ifstream utf_stdin;

/** Initializes a input file stream with an stdin handle.
 * @param ifstream The structure to initialize the stdin handle with.
 *  If this parameter is NULL, it initializes @ref utf_stdin.
 */

void utf_stdin_init(struct utf_ifstream * ifstream);

#endif /* LIBUTF_IFSTREAM_H */


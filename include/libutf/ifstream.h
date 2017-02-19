#ifndef LIBUTF_IFSTREAM_H
#define LIBUTF_IFSTREAM_H

#include <libutf/istream.h>

typedef struct utf_ifstream {
	utf_istream_t istream;
} utf_ifstream_t;

void utf_ifstream_init(utf_ifstream_t * ifstream);

void utf_ifstream_free(utf_ifstream_t * ifstream);

utf_codec_t utf_ifstream_get_codec(const utf_ifstream_t * ifstream);

utf_error_t utf_ifstream_open(utf_ifstream_t * ifstream, const char * path);

utf_unit_count_t utf_ifstream_read_utf8(utf_ifstream_t * ifstream, utf8_t * data, utf_unit_count_t data_max);

utf_unit_count_t utf_ifstream_read_utf16(utf_ifstream_t * ifstream, utf16_t * data, utf_unit_count_t data_max);

utf_unit_count_t utf_ifstream_read_utf32(utf_ifstream_t * ifstream, utf32_t * data, utf_unit_count_t data_max);

void utf_ifstream_set_codec(utf_ifstream_t * ifstream, utf_codec_t codec);

/** The UTF version of the stdin handle.
 */

extern utf_ifstream_t utf_stdin;

/** Initializes a input file stream with an stdin handle.
 * @param ifstream The structure to initialize the stdin handle with.
 *  If this parameter is NULL, it initializes @ref utf_stdin.
 */

void utf_stdin_init(utf_ifstream_t * ifstream);

#endif /* LIBUTF_IFSTREAM_H */


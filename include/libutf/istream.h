#ifndef LIBUTF_ISTREAM_H
#define LIBUTF_ISTREAM_H

/* for char16_t and char32_t */
#include <uchar.h>

#include <libutf/stream.h>
#include <libutf/string.h>

typedef size_t (*utf_read_callback_t)(void * stream_data, void * data, size_t data_max);

struct utf_istream {
	struct utf_stream stream;
	utf_read_callback_t read_cb;
};

void utf_istream_init(struct utf_istream * istream);

void utf_istream_free(struct utf_istream * istream);

utf_codec_t utf_istream_get_codec(const struct utf_istream * istream);

void utf_istream_set_codec(struct utf_istream * istream, utf_codec_t codec);

void utf_istream_set_data(struct utf_istream * istream, void * data);

void utf_istream_set_free(struct utf_istream * istream, utf_free_callback_t free_cb);

void utf_istream_set_seek(struct utf_istream * istream, utf_seek_callback_t seek_cb);

void utf_istream_set_tell(struct utf_istream * istream, utf_tell_callback_t tell_cb);

void utf_istream_set_read(struct utf_istream * istream, utf_read_callback_t read_cb);

size_t utf_istream_read(struct utf_istream * istream, struct utf_string * string);

size_t utf_istream_read_utf8(struct utf_istream * istream, char * data, size_t data_max);

size_t utf_istream_read_utf16(struct utf_istream * istream, char16_t * data, size_t data_max);

size_t utf_istream_read_utf32(struct utf_istream * istream, char32_t * data, size_t data_max);

size_t utf_istream_read_bytes(struct utf_istream * istream, void * data, size_t data_max);

#endif /* LIBUTF_ISTREAM_H */


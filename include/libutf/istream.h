#ifndef LIBUTF_ISTREAM_H
#define LIBUTF_ISTREAM_H

#include <libutf/stream.h>

typedef struct utf_istream utf_istream_t;

typedef utf_byte_count_t (*utf_read_callback_t)(void * stream_data, void * data, utf_byte_count_t data_max);

struct utf_istream {
	utf_stream_t stream;
	utf_read_callback_t read_cb;
};

void utf_istream_init(utf_istream_t * istream);

void utf_istream_free(utf_istream_t * istream);

utf_codec_t utf_istream_get_codec(const utf_istream_t * istream);

void utf_istream_set_codec(utf_istream_t * istream, utf_codec_t codec);

void utf_istream_set_data(utf_istream_t * istream, void * data);

void utf_istream_set_free(utf_istream_t * istream, utf_free_callback_t free_cb);

void utf_istream_set_seek(utf_istream_t * istream, utf_seek_callback_t seek_cb);

void utf_istream_set_tell(utf_istream_t * istream, utf_tell_callback_t tell_cb);

void utf_istream_set_read(utf_istream_t * istream, utf_read_callback_t read_cb);

utf_unit_count_t utf_istream_read_utf8(utf_istream_t * istream, utf8_t * data, utf_unit_count_t data_max);

utf_unit_count_t utf_istream_read_utf16(utf_istream_t * istream, utf16_t * data, utf_unit_count_t data_max);

utf_unit_count_t utf_istream_read_utf32(utf_istream_t * istream, utf32_t * data, utf_unit_count_t data_max);

utf_byte_count_t utf_istream_read_bytes(utf_istream_t * istream, void * data, utf_byte_count_t data_max);

#endif /* LIBUTF_ISTREAM_H */


#ifndef LIBUTF_OSTREAM_H
#define LIBUTF_OSTREAM_H

#include <libutf/stream.h>
#include <libutf/string.h>

typedef struct utf_ostream utf_ostream_t;

typedef utf_byte_count_t (*utf_write_callback_t)(void * file_ptr, const void * data, utf_byte_count_t data_max);

struct utf_ostream {
	utf_stream_t stream;
	utf_write_callback_t write_cb;
};

void utf_ostream_init(utf_ostream_t * ostream);

void utf_ostream_free(utf_ostream_t * ostream);

utf_stream_t * utf_ostream_get_stream(utf_ostream_t * ostream);

const utf_stream_t * utf_ostream_get_stream_const(const utf_ostream_t * ostream);

void utf_ostream_set_data(utf_ostream_t * ostream, void * data);

void utf_ostream_set_free(utf_ostream_t * ostream, utf_free_callback_t free_cb);

void utf_ostream_set_seek(utf_ostream_t * ostream, utf_seek_callback_t seek_cb);

void utf_ostream_set_tell(utf_ostream_t * ostream, utf_tell_callback_t tell_cb);

void utf_ostream_set_write(utf_ostream_t * ostream, utf_write_callback_t read_cb);

utf_unit_count_t utf_ostream_write(utf_ostream_t * ostream, const utf_string_t * string);

utf_unit_count_t utf_ostream_write_asciiz(utf_ostream_t * ostream, const char * asciiz_str);

utf_unit_count_t utf_ostream_write_utf8(utf_ostream_t * ostream, const utf8_t * data, utf_unit_count_t data_max);

utf_unit_count_t utf_ostream_write_utf16(utf_ostream_t * ostream, const utf16_t * data, utf_unit_count_t data_max);

utf_unit_count_t utf_ostream_write_utf32(utf_ostream_t * ostream, const utf32_t * data, utf_unit_count_t data_max);

utf_byte_count_t utf_ostream_write_bytes(utf_ostream_t * ostream, const void * data, utf_byte_count_t data_max);

#endif /* LIBUTF_OSTREAM_H */


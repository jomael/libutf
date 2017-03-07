#ifndef LIBUTF_OSTREAM_H
#define LIBUTF_OSTREAM_H

/* for char16_t and char32_t */
#include <uchar.h>

/* for va_list */
#include <stdarg.h>

#include <libutf/stream.h>
#include <libutf/string.h>

typedef size_t (*utf_write_callback_t)(void * file_ptr, const void * data, size_t data_max);

struct utf_ostream {
	struct utf_stream stream;
	utf_write_callback_t write_cb;
};

void utf_ostream_init(struct utf_ostream * ostream);

void utf_ostream_free(struct utf_ostream * ostream);

struct utf_stream * utf_ostream_get_stream(struct utf_ostream * ostream);

const struct utf_stream * utf_ostream_get_stream_const(const struct utf_ostream * ostream);

size_t utf_ostream_printf(struct utf_ostream * ostream, const char32_t * fmt, ...);

size_t utf_ostrema_vprintf(struct utf_ostream * ostream, const char32_t * fmt, va_list args);

void utf_ostream_set_data(struct utf_ostream * ostream, void * data);

void utf_ostream_set_free(struct utf_ostream * ostream, utf_free_callback_t free_cb);

void utf_ostream_set_seek(struct utf_ostream * ostream, utf_seek_callback_t seek_cb);

void utf_ostream_set_tell(struct utf_ostream * ostream, utf_tell_callback_t tell_cb);

void utf_ostream_set_write(struct utf_ostream * ostream, utf_write_callback_t read_cb);

size_t utf_ostream_write(struct utf_ostream * ostream, const struct utf_string * string);

size_t utf_ostream_write_utf8(struct utf_ostream * ostream, const char * data);

size_t utf_ostream_write_utf16(struct utf_ostream * ostream, const char16_t * data);

size_t utf_ostream_write_utf32(struct utf_ostream * ostream, const char32_t * data);

size_t utf_ostream_write_bytes(struct utf_ostream * ostream, const void * data, size_t data_max);

#endif /* LIBUTF_OSTREAM_H */


#ifndef LIBUTF_STREAM_H
#define LIBUTF_STREAM_H

#include <libutf/error.h>
#include <libutf/types.h>

typedef void (*utf_free_callback_t)(void * data);

typedef utf_error_t (*utf_seek_callback_t)(void * data, utf_byte_index_t index);

typedef utf_error_t (*utf_tell_callback_t)(void * data, utf_byte_index_t * index);

typedef struct utf_stream {
	void * data;
	utf_free_callback_t free_cb;
	utf_seek_callback_t seek_cb;
	utf_tell_callback_t tell_cb;
} utf_stream_t;

void utf_stream_init(utf_stream_t * stream);

void utf_stream_free(utf_stream_t * stream);

void * utf_stream_get_data(utf_stream_t * stream);

const void * utf_stream_get_data_const(const utf_stream_t * stream);

utf_error_t utf_stream_seek(utf_stream_t * stream, utf_byte_index_t index);

utf_error_t utf_stream_tell(utf_stream_t * stream, utf_byte_index_t * index);

void utf_stream_set_data(utf_stream_t * stream, void * data);

void utf_stream_set_free(utf_stream_t * stream, utf_free_callback_t free_cb);

void utf_stream_set_tell(utf_stream_t * stream, utf_tell_callback_t tell_cb);

#endif /* LIBUTF_STREAM_H */


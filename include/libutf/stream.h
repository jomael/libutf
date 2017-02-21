#ifndef LIBUTF_STREAM_H
#define LIBUTF_STREAM_H

/* for size_t */
#include <stdlib.h>

#include <libutf/codec.h>

typedef void (*utf_free_callback_t)(void * data);

typedef int (*utf_seek_callback_t)(void * data, size_t index);

typedef int (*utf_tell_callback_t)(void * data, size_t * index);

struct utf_stream {
	void * data;
	utf_codec_t codec;
	utf_free_callback_t free_cb;
	utf_seek_callback_t seek_cb;
	utf_tell_callback_t tell_cb;
};

void utf_stream_init(struct utf_stream * stream);

void utf_stream_free(struct utf_stream * stream);

utf_codec_t utf_stream_get_codec(const struct utf_stream * stream);

int utf_stream_seek(struct utf_stream * stream, size_t index);

int utf_stream_tell(struct utf_stream * stream, size_t * index);

void utf_stream_set_codec(struct utf_stream * stream, utf_codec_t codec);

void utf_stream_set_data(struct utf_stream * stream, void * data);

void utf_stream_set_free(struct utf_stream * stream, utf_free_callback_t free_cb);

void utf_stream_set_tell(struct utf_stream * stream, utf_tell_callback_t tell_cb);

#endif /* LIBUTF_STREAM_H */


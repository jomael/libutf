#include <libutf/stream.h>

#include <stdlib.h>

void utf_stream_init(struct utf_stream * stream){
	stream->data = NULL;
	stream->codec = UTF_CODEC_UTF8;
	stream->free_cb = NULL;
	stream->seek_cb = NULL;
	stream->tell_cb = NULL;
}

void utf_stream_free(struct utf_stream * stream){
	if (stream != NULL){
		if ((stream->data != NULL)
		 && (stream->free_cb != NULL)){
			stream->free_cb(stream->data);
		}
	}
}

utf_codec_t utf_stream_get_codec(const struct utf_stream * stream){
	return stream->codec;
}

void utf_stream_set_codec(struct utf_stream * stream, utf_codec_t codec){
	stream->codec = codec;
}

void utf_stream_set_data(struct utf_stream * stream, void * data){
	stream->data = data;
}

void utf_stream_set_free(struct utf_stream * stream, utf_free_callback_t free_cb){
	stream->free_cb = free_cb;
}

void utf_stream_set_seek(struct utf_stream * stream, utf_seek_callback_t seek_cb){
	stream->seek_cb = seek_cb;
}

void utf_stream_set_tell(struct utf_stream * stream, utf_tell_callback_t tell_cb){
	stream->tell_cb = tell_cb;
}

int utf_stream_seek(struct utf_stream * stream, size_t index){
	return stream->seek_cb(stream->data, index);
}

int utf_stream_tell(struct utf_stream * stream, size_t * index){
	return stream->tell_cb(stream->data, index);
}


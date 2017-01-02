#include <libutf/stream.h>

#include <stdlib.h>

void utf_stream_init(utf_stream_t * stream){
	stream->data = NULL;
	stream->free_cb = NULL;
	stream->seek_cb = NULL;
	stream->tell_cb = NULL;
}

void utf_stream_free(utf_stream_t * stream){
	if (stream != NULL){
		if ((stream->data != NULL)
		 && (stream->free_cb != NULL)){
			stream->free_cb(stream->data);
		}
	}
}

void * utf_stream_get_data(utf_stream_t * stream){
	return stream->data;
}

const void * utf_stream_get_data_const(const utf_stream_t * stream){
	return stream->data;
}

void utf_stream_set_data(utf_stream_t * stream, void * data){
	stream->data = data;
}

void utf_stream_set_free(utf_stream_t * stream, utf_free_callback_t free_cb){
	stream->free_cb = free_cb;
}

void utf_stream_set_seek(utf_stream_t * stream, utf_seek_callback_t seek_cb){
	stream->seek_cb = seek_cb;
}

void utf_stream_set_tell(utf_stream_t * stream, utf_tell_callback_t tell_cb){
	stream->tell_cb = tell_cb;
}

utf_error_t utf_stream_seek(utf_stream_t * stream, utf_byte_index_t index){
	return stream->seek_cb(stream->data, index);
}

utf_error_t utf_stream_tell(utf_stream_t * stream, utf_byte_index_t * index){
	return stream->tell_cb(stream->data, index);
}


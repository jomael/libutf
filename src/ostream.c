#include <libutf/ostream.h>

#include <libutf/converter.h>

#include <string.h>

static size_t utf_ostream_write_any(struct utf_ostream * ostream, const unsigned char * bytes, size_t data_max, utf_codec_t src_codec);

void utf_ostream_init(struct utf_ostream * ostream){
	utf_stream_init(&ostream->stream);
	ostream->write_cb = NULL;
}

void utf_ostream_free(struct utf_ostream * ostream){
	utf_stream_free(&ostream->stream);
}

utf_codec_t utf_ostream_get_codec(const struct utf_ostream * ostream){
	return utf_stream_get_codec(&ostream->stream);
}

void utf_ostream_set_codec(struct utf_ostream * ostream, utf_codec_t codec){
	utf_stream_set_codec(&ostream->stream, codec);
}

void utf_ostream_set_data(struct utf_ostream * ostream, void * data){
	utf_stream_set_data(&ostream->stream, data);
}

void utf_ostream_set_free(struct utf_ostream * ostream, utf_free_callback_t free_cb){
	utf_stream_set_free(&ostream->stream, free_cb);
}

void utf_ostream_set_write(struct utf_ostream * ostream, utf_write_callback_t write_cb){
	ostream->write_cb = write_cb;
}

size_t utf_ostream_write(struct utf_ostream * ostream, const struct utf_string * string){

	const unsigned char * data;
	size_t data_len;

	data = (const unsigned char *)(string->data);
	data_len = string->data_len * sizeof(char32_t);

	return utf_ostream_write_any(ostream, data, data_len, UTF_CODEC_UTF32);
}

size_t utf_ostream_write_utf8(struct utf_ostream * ostream, const char * data){

	size_t data_max = 0;
	while (data[data_max] != 0){
		data_max++;
	}

	return utf_ostream_write_any(ostream, (const unsigned char *)(data), data_max * sizeof(char), UTF_CODEC_UTF8);
}

size_t utf_ostream_write_utf16(struct utf_ostream * ostream, const char16_t * data){

	size_t data_max = 0;
	while (data[data_max] != 0){
		data_max++;
	}

	return utf_ostream_write_any(ostream, (const unsigned char *)(data), data_max * sizeof(char16_t), UTF_CODEC_UTF16) / 2;
}

size_t utf_ostream_write_utf32(struct utf_ostream * ostream, const char32_t * data){

	size_t data_max = 0;
	while (data[data_max] != 0){
		data_max++;
	}

	return utf_ostream_write_any(ostream, (const unsigned char *)(data), data_max * sizeof(char32_t), UTF_CODEC_UTF32) / 4;
}

static size_t utf_ostream_write_any(struct utf_ostream * ostream, const unsigned char * bytes, size_t data_max, utf_codec_t src_codec){

	size_t i;
	size_t write_count;
	utf_converter_t converter;
	unsigned char byte;

	if (ostream->write_cb == NULL){
		return 0;
	}

	utf_converter_init(&converter);
	utf_converter_set_decoder_codec(&converter, src_codec);
	utf_converter_set_encoder_codec(&converter, utf_ostream_get_codec(ostream));

	write_count = utf_converter_write(&converter, bytes, data_max);
	if (write_count < data_max){
		utf_converter_free(&converter);
		return 0;
	}

	i = 0;

	while (1){
		if (utf_converter_read(&converter, &byte, 1) != 1){
			break;
		}
		if (ostream->write_cb(ostream->stream.data, &byte, 1) != 1){
			break;
		}
		i++;
	}

	utf_converter_free(&converter);

	return i;
}


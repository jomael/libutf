#include <libutf/ostream.h>

#include <libutf/converter.h>

#include <string.h>

static utf_byte_count_t utf_ostream_write_any(utf_ostream_t * ostream,
                                              const unsigned char * bytes,
                                              utf_byte_count_t data_max,
                                              utf_codec_t src_codec);

void utf_ostream_init(utf_ostream_t * ostream){
	utf_stream_init(&ostream->stream);
	ostream->write_cb = NULL;
}

void utf_ostream_free(utf_ostream_t * ostream){
	utf_stream_free(&ostream->stream);
}

utf_codec_t utf_ostream_get_codec(const utf_ostream_t * ostream){
	return utf_stream_get_codec(&ostream->stream);
}

void utf_ostream_set_codec(utf_ostream_t * ostream, utf_codec_t codec){
	utf_stream_set_codec(&ostream->stream, codec);
}

void utf_ostream_set_data(utf_ostream_t * ostream, void * data){
	utf_stream_set_data(&ostream->stream, data);
}

void utf_ostream_set_free(utf_ostream_t * ostream, utf_free_callback_t free_cb){
	utf_stream_set_free(&ostream->stream, free_cb);
}

void utf_ostream_set_write(utf_ostream_t * ostream, utf_write_callback_t write_cb){
	ostream->write_cb = write_cb;
}

utf_unit_count_t utf_ostream_write(utf_ostream_t * ostream, const utf_string_t * string){
	return utf_ostream_write_any(ostream,
	                             string->data_const.u8,
	                             string->count,
	                             string->codec);
}

utf_unit_count_t utf_ostream_write_asciiz(utf_ostream_t * ostream, const char * asciiz_str){
	return utf_ostream_write_any(ostream, (const unsigned char *)(asciiz_str), strlen(asciiz_str), UTF_CODEC_UTF8);
}

utf_unit_count_t utf_ostream_write_utf8(utf_ostream_t * ostream, const utf8_t * data, utf_unit_count_t data_max){
	return utf_ostream_write_any(ostream, (const unsigned char *)(data), data_max * sizeof(utf8_t), UTF_CODEC_UTF8);
}

utf_unit_count_t utf_ostream_write_utf16(utf_ostream_t * ostream, const utf16_t * data, utf_unit_count_t data_max){
	return utf_ostream_write_any(ostream, (const unsigned char *)(data), data_max * sizeof(utf16_t), UTF_CODEC_UTF16) / 2;
}

utf_unit_count_t utf_ostream_write_utf32(utf_ostream_t * ostream, const utf32_t * data, utf_unit_count_t data_max){
	return utf_ostream_write_any(ostream, (const unsigned char *)(data), data_max * sizeof(utf16_t), UTF_CODEC_UTF32) / 4;
}

static utf_byte_count_t utf_ostream_write_any(utf_ostream_t * ostream,
                                              const unsigned char * bytes,
                                              utf_byte_count_t data_max,
                                              utf_codec_t src_codec){
	utf_unit_count_t i;
	utf_byte_count_t write_count;
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


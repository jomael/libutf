#include <libutf/istream.h>
#include <libutf/converter.h>

#include <stdlib.h>

static utf_byte_count_t utf_istream_read_any(utf_istream_t * istream,
                                             unsigned char * bytes,
                                             utf_byte_count_t data_max,
                                             utf_codec_t dst_codec);

void utf_istream_init(utf_istream_t * istream){
	utf_stream_init(&istream->stream);
	istream->read_cb = NULL;
}

void utf_istream_free(utf_istream_t * istream){
	utf_stream_free(&istream->stream);
}

utf_codec_t utf_istream_get_codec(const utf_istream_t * istream){
	return utf_stream_get_codec(&istream->stream);
}

void utf_istream_set_codec(utf_istream_t * istream, utf_codec_t codec){
	utf_stream_set_codec(&istream->stream, codec);
}

void utf_istream_set_data(utf_istream_t * istream, void * data){
	utf_stream_set_data(&istream->stream, data);
}

void utf_istream_set_free(utf_istream_t * istream, utf_free_callback_t free_cb){
	utf_stream_set_free(&istream->stream, free_cb);
}

void utf_istream_set_read(utf_istream_t * istream, utf_read_callback_t read_cb){
	istream->read_cb = read_cb;
}

utf_unit_count_t utf_istream_read_utf8(utf_istream_t * istream, utf8_t * data, utf_unit_count_t data_max){
	return utf_istream_read_any(istream, (unsigned char *)(data), data_max * sizeof(utf8_t), UTF_CODEC_UTF8);
}

utf_unit_count_t utf_istream_read_utf16(utf_istream_t * istream, utf16_t * data, utf_unit_count_t data_max){
	return utf_istream_read_any(istream, (unsigned char *)(data), data_max * sizeof(utf16_t), UTF_CODEC_UTF16) / 2;
}

utf_unit_count_t utf_istream_read_utf32(utf_istream_t * istream, utf32_t * data, utf_unit_count_t data_max){
	return utf_istream_read_any(istream, (unsigned char *)(data), data_max * sizeof(utf16_t), UTF_CODEC_UTF32) / 4;
}

static utf_byte_count_t utf_istream_read_any(utf_istream_t * istream,
                                             unsigned char * bytes,
                                             utf_byte_count_t data_max,
                                             utf_codec_t dst_codec){
	utf_unit_count_t i;
	utf_byte_count_t write_count;
	utf_byte_count_t read_count;
	utf_converter_t converter;
	unsigned char byte;

	utf_converter_init(&converter);
	utf_converter_set_decoder_codec(&converter, utf_istream_get_codec(istream));
	utf_converter_set_encoder_codec(&converter, dst_codec);

	i = 0;
	while (1){
		if (istream->read_cb(istream->stream.data, &byte, 1) != 1){
			break;
		}
		write_count = utf_converter_write(&converter, &byte, 1);
		if (write_count != 1){
			break;
		}
		read_count = utf_converter_read(&converter, &bytes[i], 1);
		if (read_count == 1){
			i++;
			if (i == data_max){
				break;
			}
		}
	}

	utf_converter_free(&converter);

	return i;
}


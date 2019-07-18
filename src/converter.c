#include <libutf/converter.h>

#include <stdlib.h>

static unsigned int utf_converter_transfer(utf_converter_t * converter);

void utf_converter_init(utf_converter_t * converter){

	utf_decoder_t * decoder = 0;
	utf_encoder_t * encoder = 0;

	decoder = utf_converter_get_decoder(converter);
	utf_decoder_init(decoder);

	encoder = utf_converter_get_encoder(converter);
	utf_encoder_init(encoder);
}

void utf_converter_free(utf_converter_t * converter){
	if (converter != NULL){
		utf_decoder_free(&converter->decoder);
		utf_encoder_free(&converter->encoder);
	}
}

utf_decoder_t * utf_converter_get_decoder(utf_converter_t * converter){
	return &converter->decoder;
}

const utf_decoder_t * utf_converter_get_decoder_const(const utf_converter_t * converter){
	return &converter->decoder;
}

utf_codec_t utf_converter_get_decoder_codec(const utf_converter_t * converter){
	const utf_decoder_t * decoder = 0;
	decoder = utf_converter_get_decoder_const(converter);
	return utf_decoder_get_codec(decoder);
}

utf_encoder_t * utf_converter_get_encoder(utf_converter_t * converter){
	return &converter->encoder;
}

const utf_encoder_t * utf_converter_get_encoder_const(const utf_converter_t * converter){
	return &converter->encoder;
}

utf_codec_t utf_converter_get_encoder_codec(const utf_converter_t * converter){
	const utf_encoder_t * encoder = 0;
	encoder = utf_converter_get_encoder_const(converter);
	return utf_encoder_get_codec(encoder);
}

unsigned int utf_converter_read(utf_converter_t * converter, void * dst, unsigned int dst_size){

	utf_encoder_t * encoder = 0;

	encoder = utf_converter_get_encoder(converter);

	return utf_encoder_read(encoder, dst, dst_size);
}

void utf_converter_set_decoder_codec(utf_converter_t * converter, utf_codec_t decoder_codec){
	utf_decoder_t * decoder = 0;
	decoder = utf_converter_get_decoder(converter);
	utf_decoder_set_codec(decoder, decoder_codec);
}

void utf_converter_set_encoder_codec(utf_converter_t * converter, utf_codec_t encoder_codec){
	utf_encoder_t * encoder = 0;
	encoder = utf_converter_get_encoder(converter);
	utf_encoder_set_codec(encoder, encoder_codec);
}

unsigned int utf_converter_write(utf_converter_t * converter, const void * src, unsigned int src_size){

	utf_decoder_t * decoder = 0;
	unsigned int write_count = 0;

	decoder = utf_converter_get_decoder(converter);

	write_count = utf_decoder_write(decoder, src, src_size);

	utf_converter_transfer(converter);

	return write_count;
}

utf_bool_t utf_converter_needs_data(const utf_converter_t * converter) {

	const utf_decoder_t *decoder = 0;

	decoder = utf_converter_get_decoder_const(converter);

	return utf_decoder_needs_data(decoder);
}

static unsigned int utf_converter_transfer(utf_converter_t * converter){

	utf32_t c;
	unsigned int read_count = 0;
	utf_encoder_t * encoder;
	utf_decoder_t * decoder;

	encoder = utf_converter_get_encoder(converter);
	decoder = utf_converter_get_decoder(converter);

	if (utf_decoder_flush(decoder) != UTF_ERROR_NONE){
		return 0;
	}

	while (utf_decoder_avail(decoder) > 0){
		if ((utf_decoder_read(decoder, &c, 1) != UTF_ERROR_NONE)
		 || (utf_encoder_write(encoder, c) != UTF_ERROR_NONE)){
			break;
		}
		read_count++;
	}

	return read_count;
}


#include <libutf/decoder.h>
#include <libutf/utf8.h>
#include <libutf/utf16.h>
#include <libutf/utf32.h>

#include <stdlib.h>
#include <string.h>

static utf_error_t add_output_char(utf_decoder_t * decoder, char32_t output);

static utf_error_t decode(utf_decoder_t * decoder);

static utf_error_t decode_utf8(utf_decoder_t * decoder);

static utf_error_t decode_utf16be(utf_decoder_t * decoder);

static utf_error_t decode_utf16le(utf_decoder_t * decoder);

static utf_error_t decode_utf32be(utf_decoder_t * decoder);

static utf_error_t decode_utf32le(utf_decoder_t * decoder);

static utf_error_t write_byte(utf_decoder_t * decoder, unsigned char byte);

void utf_decoder_init(utf_decoder_t * decoder){
	decoder->input_byte_array[0] = 0;
	decoder->input_byte_array[1] = 0;
	decoder->input_byte_array[2] = 0;
	decoder->input_byte_array[3] = 0;
	decoder->input_byte_count = 0;
	decoder->codec = UTF_CODEC_UTF8;
	decoder->output_array = NULL;
	decoder->output_count = 0;
	decoder->output_count_res = 0;
}

void utf_decoder_free(utf_decoder_t * decoder){
	if (decoder != NULL){
		free(decoder->output_array);
	}
}

unsigned int utf_decoder_avail(const utf_decoder_t * decoder){
	return decoder->output_count;
}

utf_error_t utf_decoder_flush(utf_decoder_t * decoder){

	size_t i = 0;

	for (i = decoder->input_byte_count; i < 4; i++){
		decoder->input_byte_array[i] = 0;
	}

	while ((decoder->input_byte_count > 0)
	    && (decode(decoder) == UTF_ERROR_NONE));

	return UTF_ERROR_NONE;
}

utf_codec_t utf_decoder_get_codec(const utf_decoder_t * decoder){
	return decoder->codec;
}

utf_error_t utf_decoder_read(utf_decoder_t * decoder, char32_t * dst, unsigned long int dst_count){

	unsigned long int read_count;

	if (dst_count > decoder->output_count){
		read_count = decoder->output_count;
	} else {
		read_count = dst_count;
	}

	memcpy(dst, decoder->output_array, read_count * sizeof(char32_t));

	memmove(decoder->output_array,
	        &decoder->output_array[read_count],
	        (decoder->output_count - read_count) * sizeof(char32_t));

	decoder->output_count -= read_count;

	return UTF_ERROR_NONE;
}

utf_error_t utf_decoder_reserve(utf_decoder_t * decoder, unsigned long int count){
	char32_t * tmp;
	tmp = realloc(decoder->output_array, count * sizeof(char32_t));
	if ((tmp == NULL) && (count > 0)){
		return UTF_ERROR_MALLOC;
	}
	decoder->output_array = tmp;
	decoder->output_count_res = count;
	if (count < decoder->output_count){
		decoder->output_count = count;
	}
	return UTF_ERROR_NONE;
}

void utf_decoder_set_codec(utf_decoder_t * decoder, utf_codec_t codec){
	decoder->codec = codec;
}

unsigned int utf_decoder_write(utf_decoder_t * decoder, const void * src, unsigned int src_size){

	utf_error_t error = UTF_ERROR_NONE;

	unsigned int i = 0;

	const unsigned char * src8 = (const unsigned char *)(src);

	for (i = 0; i < src_size; i++){
		error = write_byte(decoder, src8[i]);
		if (error != UTF_ERROR_NONE){
			break;
		}
	}

	return i;
}

utf_bool_t utf_decoder_needs_data(const utf_decoder_t * decoder) {

	if (decoder->input_byte_count == 0)
		return LIBUTF_TRUE;

	if (decoder->codec == UTF_CODEC_UTF8) {

		if (utf8_decode_length(decoder->input_byte_array[0]) > decoder->input_byte_count) {
			return LIBUTF_TRUE;
		}

	} else if ((decoder->codec == UTF_CODEC_UTF16_LE)
	        || (decoder->codec == UTF_CODEC_UTF16_BE)) {

		if (decoder->input_byte_count < 2)
			return LIBUTF_TRUE;

		char16_t c16 = 0;

		if (decoder->codec == UTF_CODEC_UTF16_LE) {
			c16 |= ((char16_t) decoder->input_byte_array[0]) << 0;
			c16 |= ((char16_t) decoder->input_byte_array[1]) << 8;
		} else {
			c16 |= ((char16_t) decoder->input_byte_array[0]) << 8;
			c16 |= ((char16_t) decoder->input_byte_array[1]) << 0;
		}

		if ((utf16_decode_length(c16) * 2) > decoder->input_byte_count) {
			return LIBUTF_TRUE;
		}

	} else if (decoder->input_byte_count < 4) {
			return LIBUTF_TRUE;
	}

	return LIBUTF_FALSE;
}

static utf_error_t add_output_char(utf_decoder_t * decoder, char32_t output){
	utf_error_t error;
	if (decoder->output_count >= decoder->output_count_res){
		error = utf_decoder_reserve(decoder, decoder->output_count_res + 32);
		if (error){
			return error;
		}
	}
	decoder->output_array[decoder->output_count] = output;
	decoder->output_count++;
	return UTF_ERROR_NONE;
}

static utf_error_t decode(utf_decoder_t * decoder){

	utf_error_t error = UTF_ERROR_NONE;

	switch (decoder->codec){
		case UTF_CODEC_UTF8:
			error = decode_utf8(decoder);
			break;
		case UTF_CODEC_UTF16_LE:
			error = decode_utf16le(decoder);
			break;
		case UTF_CODEC_UTF16_BE:
			error = decode_utf16be(decoder);
			break;
		case UTF_CODEC_UTF32_LE:
			error = decode_utf32le(decoder);
			break;
		case UTF_CODEC_UTF32_BE:
			error = decode_utf32be(decoder);
			break;
		default:
			break;
	}

	return error;
}

static utf_error_t decode_utf8(utf_decoder_t * decoder){

	utf_error_t error;
	unsigned int decode_length = 0;
	char32_t out32;

	decode_length = utf8_decode((const char *)(decoder->input_byte_array), &out32);

	if (decode_length == 0){
		return UTF_ERROR_INVALID_SEQUENCE;
	} else if (decode_length > decoder->input_byte_count) {
		return UTF_ERROR_EOF;
	}

	memmove(decoder->input_byte_array,
	       &decoder->input_byte_array[decode_length],
	       4 - decode_length);
	
	decoder->input_byte_count -= decode_length;

	error = add_output_char(decoder, out32);
	if (error){
		return error;
	}

	return UTF_ERROR_NONE;
}

static utf_error_t decode_utf16be(utf_decoder_t * decoder){

	utf_error_t error;
	char16_t out16[2] = { 0, 0 };
	char32_t out32;
	unsigned int decode_length = 0;

	out16[0] = utf16be(&decoder->input_byte_array[0]);
	out16[1] = utf16be(&decoder->input_byte_array[2]);

	decode_length = utf16_decode(out16, &out32);
	if (decode_length == 0){
		return UTF_ERROR_INVALID_SEQUENCE;
	} else if (decode_length == 1){
		decoder->input_byte_array[0] = decoder->input_byte_array[2];
		decoder->input_byte_array[1] = decoder->input_byte_array[3];
		decoder->input_byte_count = 2;
	} else if (decode_length == 2){
		decoder->input_byte_count = 0;
	}

	error = add_output_char(decoder, out32);
	if (error){
		return error;
	}

	return UTF_ERROR_NONE;
}

static utf_error_t decode_utf16le(utf_decoder_t * decoder){

	utf_error_t error;
	char16_t out16[2] = { 0, 0 };
	char32_t out32;
	unsigned int decode_length = 0;

	out16[0] = utf16le(decoder->input_byte_array);
	out16[1] = utf16le(&decoder->input_byte_array[2]);

	decode_length = utf16_decode(out16, &out32);
	if (decode_length == 0){
		return UTF_ERROR_INVALID_SEQUENCE;
	} else if (decode_length == 1){
		decoder->input_byte_array[0] = decoder->input_byte_array[2];
		decoder->input_byte_array[1] = decoder->input_byte_array[3];
		decoder->input_byte_count = 2;
	} else if (decode_length == 2){
		decoder->input_byte_count = 0;
	}

	error = add_output_char(decoder, out32);
	if (error){
		return error;
	}

	return UTF_ERROR_NONE;
}

static utf_error_t decode_utf32be(utf_decoder_t * decoder){
	utf_error_t error;
	error = add_output_char(decoder, utf32be(decoder->input_byte_array));
	if (error){
		return error;
	}
	decoder->input_byte_count = 0;
	return UTF_ERROR_NONE;
}

static utf_error_t decode_utf32le(utf_decoder_t * decoder){
	utf_error_t error;
	error = add_output_char(decoder, utf32le(decoder->input_byte_array));
	if (error){
		return error;
	}
	decoder->input_byte_count = 0;
	return UTF_ERROR_NONE;
}

static utf_error_t write_byte(utf_decoder_t * decoder, unsigned char byte){

	decoder->input_byte_count %= 4;

	switch (decoder->input_byte_count){
		case 0:
			decoder->input_byte_array[0] = byte;
			decoder->input_byte_count = 1;
			break;
		case 1:
			decoder->input_byte_array[1] = byte;
			decoder->input_byte_count = 2;
			break;
		case 2:
			decoder->input_byte_array[2] = byte;
			decoder->input_byte_count = 3;
			break;
		case 3:
			decoder->input_byte_array[3] = byte;
			decoder->input_byte_count = 4;
			break;
		default:
			/* should be unreachable */
			return UTF_ERROR_OVERFLOW;
	}

	if (decoder->input_byte_count >= 4){
		return decode(decoder);
	}
	
	return UTF_ERROR_NONE;
}


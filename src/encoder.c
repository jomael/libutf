#include <libutf/encoder.h>
#include <libutf/utf8.h>
#include <libutf/utf16.h>

#include <stdlib.h>
#include <string.h>

void utf_encoder_init(utf_encoder_t * encoder){
	encoder->codec = UTF_CODEC_UTF8;
	encoder->byte_array = NULL;
	encoder->byte_count = 0;
	encoder->byte_count_res = 0;
}

void utf_encoder_free(utf_encoder_t * encoder){
	if (encoder != NULL){
		free(encoder->byte_array);
	}
}

utf_codec_t utf_encoder_get_codec(const utf_encoder_t * encoder){
	return encoder->codec;
}

unsigned long int utf_encoder_read(utf_encoder_t * encoder, void * dst, unsigned long int dst_size){

	unsigned long int read_size = 0;

	if (dst_size < encoder->byte_count){
		read_size = dst_size;
	} else {
		read_size = encoder->byte_count;
	}

	memcpy(dst, encoder->byte_array, read_size);

	memmove(encoder->byte_array,
	       &encoder->byte_array[dst_size],
	        encoder->byte_count - read_size);

	encoder->byte_count -= read_size;

	return read_size;
}

void utf_encoder_set_codec(utf_encoder_t * encoder, utf_codec_t codec){
	encoder->codec = codec;
}

utf_error_t utf_encoder_write(utf_encoder_t * encoder, char32_t input_char){

	utf_error_t error = UTF_ERROR_NONE;
	size_t index = 0;

	if ((encoder->byte_count + 4) > encoder->byte_count_res){
		error = utf_encoder_reserve(encoder, encoder->byte_count_res + 32);
		if (error){
			return error;
		}
	}

	index = encoder->byte_count;

	if (encoder->codec == UTF_CODEC_UTF8){

		size_t result = utf8_encode(input_char, (char *)(&encoder->byte_array[index]));
		if (!result){
			return UTF_ERROR_INVALID_SEQUENCE;
		} else {
			encoder->byte_count += result;
		}

	} else if (encoder->codec == UTF_CODEC_UTF16_LE){

		char16_t output_char[2] = { 0, 0 };

		size_t result = utf16_encode(input_char, output_char);
		if (!result){
			return UTF_ERROR_INVALID_SEQUENCE;
		} else {
			encoder->byte_count += result * 2;
		}

		encoder->byte_array[index + 0] = (output_char[0] >> 0) & 0xff;
		encoder->byte_array[index + 1] = (output_char[0] >> 8) & 0xff;
		encoder->byte_array[index + 2] = (output_char[1] >> 0) & 0xff;
		encoder->byte_array[index + 3] = (output_char[1] >> 8) & 0xff;

	} else if (encoder->codec == UTF_CODEC_UTF16_BE){

		char16_t output_char[2] = { 0, 0 };

		size_t result = utf16_encode(input_char, output_char);
		if (!result){
			return UTF_ERROR_INVALID_SEQUENCE;
		} else {
			encoder->byte_count += result * 2;
		}

		encoder->byte_array[index + 0] = (output_char[0] >> 8) & 0xff;
		encoder->byte_array[index + 1] = (output_char[0] >> 0) & 0xff;
		encoder->byte_array[index + 2] = (output_char[1] >> 8) & 0xff;
		encoder->byte_array[index + 3] = (output_char[1] >> 0) & 0xff;

	} else if (encoder->codec == UTF_CODEC_UTF32_LE){
		encoder->byte_array[index + 0] = (input_char >> 0x00) & 0xff;
		encoder->byte_array[index + 1] = (input_char >> 0x08) & 0xff;
		encoder->byte_array[index + 2] = (input_char >> 0x10) & 0xff;
		encoder->byte_array[index + 3] = (input_char >> 0x18) & 0xff;
		encoder->byte_count += 4;
	} else if (encoder->codec == UTF_CODEC_UTF32_BE){
		encoder->byte_array[index + 0] = (input_char >> 0x18) & 0xff;
		encoder->byte_array[index + 1] = (input_char >> 0x10) & 0xff;
		encoder->byte_array[index + 2] = (input_char >> 0x08) & 0xff;
		encoder->byte_array[index + 3] = (input_char >> 0x00) & 0xff;
		encoder->byte_count += 4;
	}

	return UTF_ERROR_NONE;
}

utf_error_t utf_encoder_reserve(utf_encoder_t * encoder, unsigned long int size){
	unsigned char * tmp;
	tmp = realloc(encoder->byte_array, size);
	if ((tmp == NULL) && (size > 0)){
		return UTF_ERROR_MALLOC;
	}
	encoder->byte_array = tmp;
	encoder->byte_count_res = size;
	if (size < encoder->byte_count){
		encoder->byte_count = size;
	}
	return UTF_ERROR_NONE;
}


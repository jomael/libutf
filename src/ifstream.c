#include <libutf/ifstream.h>

#include <stdio.h>
#include <errno.h>

static void ifstream_free(void * data){
	fclose((FILE *)(data));
}

static utf_byte_count_t ifstream_read(void * stream_data, void * data, utf_byte_count_t data_max){
	return fread(data, 1, data_max, (FILE *)(stream_data));
}

void utf_ifstream_init(utf_ifstream_t * ifstream){
	utf_istream_init(&ifstream->istream);
	utf_istream_set_free(&ifstream->istream, ifstream_free);
	utf_istream_set_read(&ifstream->istream, ifstream_read);
}

void utf_ifstream_free(utf_ifstream_t * ifstream){
	utf_istream_free(&ifstream->istream);
}

utf_error_t utf_ifstream_open(utf_ifstream_t * ifstream, const char * path){

	FILE * file;

	/* utf_ifstream_open may be called as a constructor */
	/* must initialize members, in case they haven't already */
	utf_ifstream_init(ifstream);

	file = fopen(path, "rb");
	if (file == NULL){
		return utf_errno(errno);
	}

	utf_istream_set_data(&ifstream->istream, file);
	return UTF_ERROR_NONE;
}

utf_unit_count_t utf_ifstream_read_utf8(utf_ifstream_t * ifstream, utf8_t * data, utf_unit_count_t data_max){
	return utf_istream_read_utf8(&ifstream->istream, data, data_max);
}

utf_unit_count_t utf_ifstream_read_utf16(utf_ifstream_t * ifstream, utf16_t * data, utf_unit_count_t data_max){
	return utf_istream_read_utf16(&ifstream->istream, data, data_max);
}

utf_unit_count_t utf_ifstream_read_utf32(utf_ifstream_t * ifstream, utf32_t * data, utf_unit_count_t data_max){
	return utf_istream_read_utf32(&ifstream->istream, data, data_max);
}


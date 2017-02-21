#include <libutf/ofstream.h>

#include <stdio.h>

static size_t ofstream_write(void * file_ptr, const void * data, size_t data_max){
	return fwrite(data, 1, data_max, (FILE *)(file_ptr));
}

void utf_ofstream_init(struct utf_ofstream * ofstream){
	utf_ostream_init(&ofstream->ostream);
	utf_ostream_set_write(&ofstream->ostream, ofstream_write);
}

void utf_ofstream_free(struct utf_ofstream * ofstream){
	utf_ostream_free(&ofstream->ostream);
}

size_t utf_ofstream_write(struct utf_ofstream * ofstream, const struct utf_string * string){
	return utf_ostream_write(&ofstream->ostream, string);
}

size_t utf_ofstream_write_utf8(struct utf_ofstream * ofstream, const char * src){
	return utf_ostream_write_utf8(&ofstream->ostream, src);
}

size_t utf_ofstream_write_utf16(struct utf_ofstream * ofstream, const char16_t * src){
	return utf_ostream_write_utf16(&ofstream->ostream, src);
}

size_t utf_ofstream_write_utf32(struct utf_ofstream * ofstream, const char32_t * src){
	return utf_ostream_write_utf32(&ofstream->ostream, src);
}

struct utf_ofstream utf_stdout;

void utf_stdout_init(struct utf_ofstream * ofstream){
	if (ofstream == NULL){
		ofstream = &utf_stdout;
	}
	utf_ofstream_init(ofstream);
	utf_ostream_set_data(&ofstream->ostream, stdout);
}

struct utf_ofstream utf_stderr;

void utf_stderr_init(struct utf_ofstream * ofstream){
	if (ofstream == NULL){
		ofstream = &utf_stderr;
	}
	utf_ofstream_init(ofstream);
	utf_ostream_set_data(&ofstream->ostream, stderr);
}


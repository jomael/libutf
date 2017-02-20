#include <libutf/ofstream.h>

#include <stdio.h>

static utf_byte_count_t ofstream_write(void * file_ptr, const void * data, utf_byte_count_t data_max){
	return fwrite(data, 1, data_max, (FILE *)(file_ptr));
}

void utf_ofstream_init(utf_ofstream_t * ofstream){
	utf_ostream_init(&ofstream->ostream);
	utf_ostream_set_write(&ofstream->ostream, ofstream_write);
}

void utf_ofstream_free(utf_ofstream_t * ofstream){
	utf_ostream_free(&ofstream->ostream);
}

utf_unit_count_t utf_ofstream_write(utf_ofstream_t * ofstream, const struct utf_string * string){
	return utf_ostream_write(&ofstream->ostream, string);
}

utf_unit_count_t utf_ofstream_write_asciiz(utf_ofstream_t * ofstream, const char * asciiz_str){
	return utf_ostream_write_asciiz(&ofstream->ostream, asciiz_str);
}

utf_ofstream_t utf_stdout;

void utf_stdout_init(utf_ofstream_t * ofstream){
	if (ofstream == NULL){
		ofstream = &utf_stdout;
	}
	utf_ofstream_init(ofstream);
	utf_ostream_set_data(&ofstream->ostream, stdout);
}

utf_ofstream_t utf_stderr;

void utf_stderr_init(utf_ofstream_t * ofstream){
	if (ofstream == NULL){
		ofstream = &utf_stderr;
	}
	utf_ofstream_init(ofstream);
	utf_ostream_set_data(&ofstream->ostream, stderr);
}


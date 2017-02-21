#include <libutf/ifstream.h>

#include <stdio.h>
#include <errno.h>

static void ifstream_free(void * data){
	fclose((FILE *)(data));
}

static size_t ifstream_read(void * stream_data, void * data, size_t data_max){
	return fread(data, 1, data_max, (FILE *)(stream_data));
}

struct utf_ifstream utf_stdin;

void utf_stdin_init(struct utf_ifstream * ifstream){
	if (ifstream == NULL){
		ifstream = &utf_stdin;
	}
	utf_ifstream_init(ifstream);
	utf_istream_set_data(&ifstream->istream, stdin);
}

void utf_ifstream_init(struct utf_ifstream * ifstream){
	utf_istream_init(&ifstream->istream);
	utf_istream_set_free(&ifstream->istream, ifstream_free);
	utf_istream_set_read(&ifstream->istream, ifstream_read);
}

void utf_ifstream_free(struct utf_ifstream * ifstream){
	utf_istream_free(&ifstream->istream);
}

int utf_ifstream_open(struct utf_ifstream * ifstream, const char * path){

	FILE * file;
#ifdef _MSC_VER
	errno_t err;
#endif /* _MSC_VER */

	/* utf_ifstream_open may be called as a constructor */
	/* must initialize members, in case they haven't already */
	utf_ifstream_init(ifstream);

#ifdef _MSC_VER
	err = fopen_s(&file, path, "rb");
	if (err != 0){
		return err;
	}
#else /* _MSC_VER */
	file = fopen(path, "rb");
	if (file == NULL){
		return errno;
	}
#endif /* _MSC_VER */

	utf_istream_set_data(&ifstream->istream, file);

	return 0;
}

size_t utf_ifstream_read(struct utf_ifstream * ifstream, struct utf_string * string){
	(void) string;
	(void) ifstream;
	return 0;
}

size_t utf_ifstream_read_utf8(struct utf_ifstream * ifstream, utf8_t * data, size_t data_max){
	return utf_istream_read_utf8(&ifstream->istream, data, data_max);
}

size_t utf_ifstream_read_utf16(struct utf_ifstream * ifstream, utf16_t * data, size_t data_max){
	return utf_istream_read_utf16(&ifstream->istream, data, data_max);
}

size_t utf_ifstream_read_utf32(struct utf_ifstream * ifstream, utf32_t * data, size_t data_max){
	return utf_istream_read_utf32(&ifstream->istream, data, data_max);
}


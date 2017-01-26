#include <libutf/ifstream.h>
#include <assert.h>

void test_utf8(void);

int main(void){
	test_utf8();
	return 0;
}

void test_utf8(void){

	utf_error_t error;
	utf_ifstream_t ifstream;
	utf32_t ch;
	utf_unit_count_t read_count;

	utf_ifstream_init(&ifstream);

	error = utf_ifstream_open(&ifstream, "../testing/arabic/UTF-8.txt");
	assert(error == UTF_ERROR_NONE);

	read_count = utf_ifstream_read_utf32(&ifstream, &ch, 1);
	assert(read_count == 1);

	utf_ifstream_free(&ifstream);
}


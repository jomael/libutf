#include <libutf/ostream.h>

#include <assert.h>
#include <stdlib.h>

struct ostream_data {
	const char * expected_str;
	size_t i;
};

static utf_unit_count_t write_cb(void * stream_data_ptr, const void * chars_ptr, size_t chars_len){

	struct ostream_data * data;
	const utf8_t * chars;
	size_t j;

	data = (struct ostream_data *)(stream_data_ptr);
	chars = (const utf8_t *)(chars_ptr);

	for (j = 0; j < chars_len; j++){
		assert(data->expected_str[data->i] == chars[j]);
		data->i++;
	}

	return chars_len;
}

static void test_write(void){

	struct utf_string string;
	utf_ostream_t ostream;
	struct ostream_data data;

	data.expected_str = "hello, world!";
	data.i = 0;

	utf_ostream_init(&ostream);
	utf_ostream_set_data(&ostream, &data);
	utf_ostream_set_write(&ostream, write_cb);

	string.data = U"hello, world!";
	string.data_len = 13;
	string.data_res = 13;

	assert(utf_ostream_write(&ostream, &string) == 13);
}

int main(void){
	test_write();
	return EXIT_SUCCESS;
}


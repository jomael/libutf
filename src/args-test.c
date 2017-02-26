#include <libutf/args.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(void){

	struct utf_args args;
	const char * argv[] = { u8"¿Cómo", u8"estás?", NULL };
	int argc = 3;

	assert(utf_args_init(&args, argc, argv) == 0);
	assert(args.argc == 2);
	assert(args.argv[2] == NULL);

	assert(utf_args_cmp_utf32(&args, 0, U"¿Cóma") == 1);
	assert(utf_args_cmp_utf32(&args, 0, U"¿Cómo") == 0);
	assert(utf_args_cmp_utf32(&args, 0, U"¿Cómz") == -1);

	utf_args_free(&args);

	return 0;
}


#include <libutf/args.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main(void){

	struct utf_args args;
	const char * argv[] = { "¿Cómo", "estás?", NULL };
	int argc = 3;

	assert(utf_args_init(&args, argc, argv) == 0);
	assert(args.argc == 2);
	assert(args.argv[2] == NULL);

	utf_args_free(&args);

	return 0;
}


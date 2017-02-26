#include <libutf/args.h>

#include <libutf/utf8.h>

#include <errno.h>

int utf_args_init(struct utf_args * args, int argc, const char ** argv){

	int i;
	size_t argv_size;

	/* the + 1 is for the NULL terminator */
	args->argv = calloc(sizeof(args->argv[0]), argc + 1);
	if (args->argv == NULL){
		return ENOMEM;
	}

	for (i = 0; (argv[i] != NULL) && (i < argc); i++){
		args->argv[i] = utf8_to_utf32(argv[i]);
		if (args->argv[i] == NULL){
			utf_args_free(args);
			return ENOMEM;
		}
	}

	args->argv[i] = NULL;
	args->argc = (size_t) i;

	return 0;
}

void utf_args_free(struct utf_args * args){

	size_t i;

	for (i = 0; i < args->argc; i++){
		free(args->argv[i]);
	}

	free(args->argv);

	args->argv = NULL;
	args->argc = 0;
}


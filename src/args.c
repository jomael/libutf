#include <libutf/args.h>

#include <libutf/utf8.h>
#include <libutf/utf32.h>

#include <errno.h>

int utf_args_init(struct utf_args * args, int argc, const char ** argv){

	int i;

	/* the + 1 is for the NULL terminator */
	args->argv = calloc(sizeof(args->argv[0]), argc + 1);
	if (args->argv == NULL){
		return ENOMEM;
	}

	i = 0;

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

size_t utf_args_count(const struct utf_args * args){
	return args->argc;
}

int utf_args_cmp_utf32(const struct utf_args * args, size_t index, const char32_t * arg){
	return utf32_cmp(args->argv[index], arg);
}

int utf_args_cmp_opt_utf32(const struct utf_args * args, size_t index, char32_t s_opt, const char32_t * l_opt){

	if ((args->argv[index][0] == U'-')
	 && (args->argv[index][1] != 0)
	 && (args->argv[index][1] != U'-')
	 && (args->argv[index][2] == 0)){
		if (args->argv[index][1] > s_opt){
			return 1;
		} else if (args->argv[index][1] < s_opt){
			return -1;
		}
		return 0;
	}

	if ((args->argv[index][0] == '-')
	 && (args->argv[index][1] == '-')){
		return utf32_cmp(&args->argv[index][2], l_opt);
	}

	/* does not contain a '-' or a '--' */

	return -1;
}


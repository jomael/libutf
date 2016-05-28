#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char ** argv){

	int i = 0;

	const char * input_format = 0;

	const char * output_format = 0;

	const char * output_file_path = 0;

	const char * input_file_path = 0;

	FILE * input_file = stdin;

	FILE * output_file = stdout;

	if (argc >= 2){
		if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--list") == 0){
			fprintf(stderr, "%s: list of supported formats\n", argv[0]);
			fprintf(stderr, "\tUTF8\n");
			fprintf(stderr, "\tUTF16_LE\n");
			fprintf(stderr, "\tUTF16_BE\n");
			fprintf(stderr, "\tUTF32_LE\n");
			fprintf(stderr, "\tUTF32_BE\n");
			return EXIT_FAILURE;
		}
	}

	for (i = 1; i < argc; i++){
		if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--to-code") == 0){
			i++;
			if (i < argc){
				output_format = argv[i];
			}
		} else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--from-code") == 0){
			i++;
			if (i < argc){
				output_format = argv[i];
			}
		} else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0){
			i++;
			if (i < argc){
				output_file_path = argv[i];
			}
		} else if (argv[i][0] != '-'){
			i++;
			if (i < argc){
				input_file_path = argv[i];
			}
		} else {
			fprintf(stderr, "unknown option: %s\n", argv[i]);
			return EXIT_FAILURE;
		}
	}

	if (!input_format){
		fprintf(stderr, "%s: no input format specified\n", argv[0]);
		fprintf(stderr, "%s: run using -l or --list for a list of supported formats\n", argv[0]);
		return EXIT_FAILURE;
	}

	if (!output_format){
		fprintf(stderr, "%s: no output format specified\n", argv[0]);
		fprintf(stderr, "%s: run using -l or --list for a list of supported formats\n", argv[0]);
		return EXIT_FAILURE;
	}

	if (input_file_path){
#ifdef _MSC_VER
		if (fopen_s(&input_file, input_file_path, "rb") != 0){
			input_file = 0;
		}
#else /* _MSC_VER */
		input_file = fopen(input_file_path, "rb");
#endif /* _MSC_VER */
		if (!input_file){
			fprintf(stderr, "%s: failed to open %s\n", argv[0], input_file_path);
			return EXIT_FAILURE;
		}
	}

	if (output_file_path){
#ifdef _MSC_VER
		if (fopen_s(&output_file, output_file_path, "wb") != 0){
			output_file = 0;
		}
#else /* _MSC_VER */
		output_file = fopen(output_file_path, "wb");
#endif /* _MSC_VER */
		if (!output_file){
			fprintf(stderr, "%s: failed to open %s\n", argv[0], output_file_path);
			if (input_file != stdin){
				fclose(input_file);
			}
			return EXIT_FAILURE;
		}
	}

	/* encode here */

	if (input_file != stdin){
		fclose(input_file);
	}

	if (output_file != stdout){
		fclose(output_file);
	}

	return EXIT_SUCCESS;
}


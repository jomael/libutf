#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
/* on /Wall, it warns that fprintf is not inlined */
/* so, it's basically pointless */
#pragma warning(disable : 4710)
#endif /* _MSC_VER */

#include <libutf/libutf.h>

static void iconv_list_codecs(utf_ofstream_t * file);

static utf_codec_t parse_codec(const char * codec);

struct iconv {
	FILE * input_file;
	FILE * output_file;
	utf_converter_t * converter;
}; /* struct iconv_opts */

static int iconv(struct iconv * iconv_opts); 

int main(int argc, const char ** argv){

	int i = 0;

	int err = 0;

	int exit_code = EXIT_SUCCESS;

	FILE * input_file = stdin;
	const char * input_codec = 0;
	const char * input_file_path = 0;

	FILE * output_file = stdout;
	const char * output_codec = 0;
	const char * output_file_path = 0;

	utf_converter_t converter;
	utf_codec_t encoder_codec = UTF_CODEC_UTF8;
	utf_codec_t decoder_codec = UTF_CODEC_UTF8;

	struct iconv iconv_opts;

	utf_stdin_init(NULL);
	utf_stdout_init(NULL);
	utf_stderr_init(NULL);

	if (argc >= 2){
		if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--list") == 0){
			iconv_list_codecs(&utf_stderr);
			return EXIT_FAILURE;
		} else if (strcmp(argv[1], "--version") == 0){
			fprintf(stderr, "%s (written by Taylor Holberton for the libutf project) %s\n", argv[0], LIBUTF_VERSION_STRING);
			return EXIT_FAILURE;
		} else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0){
			fprintf(stderr, "usage:\n");
			fprintf(stderr, "\t%s <--to-code CODEC> <--from-code CODEC> [input-file] [-o | --output output-file]\n", argv[0]);
			fprintf(stderr, "run using -l or --list for a list of supported codecs\n");
			return EXIT_FAILURE;
		}
	}

	for (i = 1; i < argc; i++){
		if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--to-code") == 0){
			i++;
			if (i < argc){
				output_codec = argv[i];
			}
		} else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--from-code") == 0){
			i++;
			if (i < argc){
				input_codec = argv[i];
			}
		} else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0){
			i++;
			if (i < argc){
				output_file_path = argv[i];
			}
		} else if (argv[i][0] != '-'){
			input_file_path = argv[i];
		} else {
			fprintf(stderr, "unknown option: %s\n", argv[i]);
			return EXIT_FAILURE;
		}
	}

	if (!input_codec){
		fprintf(stderr, "%s: no input codec specified\n", argv[0]);
		fprintf(stderr, "%s: run using -l or --list for a list of supported codecs\n", argv[0]);
		return EXIT_FAILURE;
	}

	if (!output_codec){
		fprintf(stderr, "%s: no output codec specified\n", argv[0]);
		fprintf(stderr, "%s: run using -l or --list for a list of supported codecs\n", argv[0]);
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

	utf_converter_init(&converter);

	decoder_codec = parse_codec(input_codec);
	utf_converter_set_decoder_codec(&converter, decoder_codec);

	encoder_codec = parse_codec(output_codec);
	utf_converter_set_encoder_codec(&converter, encoder_codec);

	iconv_opts.input_file = input_file;
	iconv_opts.output_file = output_file;
	iconv_opts.converter = &converter;

	err = iconv(&iconv_opts);
	if (err){
		exit_code = EXIT_FAILURE;
	}

	if (input_file != stdin){
		fclose(input_file);
	}

	if (output_file != stdout){
		fclose(output_file);
	}

	return exit_code;
}

static void iconv_list_codecs(utf_ofstream_t * file){

	utf_codec_t codec;
	const utf_string_t * name;

	utf_ofstream_write_asciiz(file, "iconv: supported codecs:\n");

	for (codec = UTF_CODEC_FIRST; codec <= UTF_CODEC_LAST; codec++){
		name = utf_codec_to_string(codec);
		if (name == NULL){
			continue;
		}
		utf_ofstream_write(file, name);
	}
}

static utf_codec_t parse_codec(const char * codec){
	if (strcmp(codec, "UTF8") == 0){
		return UTF_CODEC_UTF8;
	} else if (strcmp(codec, "UTF16") == 0){
		return UTF_CODEC_UTF16;
	} else if (strcmp(codec, "UTF16_LE") == 0){
		return UTF_CODEC_UTF16_LE;
	} else if (strcmp(codec, "UTF16_BE") == 0){
		return UTF_CODEC_UTF16_BE;
	} else if (strcmp(codec, "UTF32") == 0){
		return UTF_CODEC_UTF32;
	} else if (strcmp(codec, "UTF32_LE") == 0){
		return UTF_CODEC_UTF32_LE;
	} else if (strcmp(codec, "UTF32_BE") == 0){
		return UTF_CODEC_UTF32_BE;
	}
	/* unknown codec */
	return UTF_CODEC_UTF8;
}

static int iconv(struct iconv * iconv_opts){

	int input = 0;
	unsigned char input_byte = 0;
	unsigned char output_byte = 0;

	unsigned int read_count = 0;
	unsigned int write_count = 0;

	while (!feof(iconv_opts->input_file)){
		input = fgetc(iconv_opts->input_file);
		if (input == EOF){
			break;
		} else {
			input_byte = input & 0xff;
		}
		utf_converter_write(iconv_opts->converter, &input_byte, 1);
	}

	while (1){
		read_count = utf_converter_read(iconv_opts->converter, &output_byte, 1);
		if (read_count == 0){
			break;
		} else {
			write_count = fwrite(&output_byte, 1, 1, iconv_opts->output_file);
			if (write_count != 1){
				fprintf(stderr, "error: failed to write byte to file\n");
				return EXIT_FAILURE;
			}
		}
	}

	return EXIT_SUCCESS;
}


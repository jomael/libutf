#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
/* on /Wall, it warns that fprintf is not inlined */
/* so, it's basically pointless */
#pragma warning(disable : 4710)
#endif /* _MSC_VER */

#include "converter.h"
#include "version.h"

static int parse_codec(const char * codec);

struct iconv {
	FILE * input_file;
	FILE * output_file;
	utfx_converter_t * converter;
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

	utfx_converter_t converter;
	utfx_encoder_mode_t encoder_mode = UTFX_ENCODER_MODE_UTF8;
	utfx_decoder_mode_t decoder_mode = UTFX_DECODER_MODE_UTF8;

	struct iconv iconv_opts;

	if (argc >= 2){
		if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--list") == 0){
			fprintf(stderr, "%s: list of supported codecs\n", argv[0]);
			fprintf(stderr, "\tUTF8\n");
			fprintf(stderr, "\tUTF16_LE\n");
			fprintf(stderr, "\tUTF16_BE\n");
			fprintf(stderr, "\tUTF32_LE\n");
			fprintf(stderr, "\tUTF32_BE\n");
			return EXIT_FAILURE;
		} else if (strcmp(argv[1], "--version") == 0){
			fprintf(stderr, "%s (written by Taylor Holberton for the utfx project) %s\n", argv[0], UTFX_VERSION_STRING);
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

	utfx_converter_init(&converter);

	decoder_mode = parse_codec(input_codec);
	utfx_converter_set_decoder_mode(&converter, decoder_mode);

	encoder_mode = parse_codec(output_codec);
	utfx_converter_set_encoder_mode(&converter, encoder_mode);

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

static int parse_codec(const char * codec){
	if (strcmp(codec, "UTF8") == 0){
		return UTFX_ENCODER_MODE_UTF8;
	} else if (strcmp(codec, "UTF16") == 0 || strcmp(codec, "UTF16_LE") == 0){
		return UTFX_ENCODER_MODE_UTF16_LE;
	} else if (strcmp(codec, "UTF16_BE") == 0){
		return UTFX_ENCODER_MODE_UTF16_BE;
	} else if (strcmp(codec, "UTF32") == 0 || strcmp(codec, "UTF32_LE") == 0){
		return UTFX_ENCODER_MODE_UTF32_BE;
	} else if (strcmp(codec, "UTF32_BE") == 0){
		return UTFX_ENCODER_MODE_UTF32_BE;
	}
	/* unknown codec */
	return UTFX_ENCODER_MODE_UTF8;
}

static int iconv(struct iconv * iconv_opts){

	int input = 0;
	unsigned char input_byte = 0;
	unsigned char output_byte = 0;

	unsigned int read_count = 0;
	unsigned int write_count = 0;

	utfx_converter_state_t state = UTFX_CONVERTER_STATE_READING;

	while (!feof(iconv_opts->input_file)){

		state = utfx_converter_get_state(iconv_opts->converter);
		if (state == UTFX_CONVERTER_STATE_READING){
			input = fgetc(iconv_opts->input_file);
			if (input == EOF){
				break;
			} else {
				input_byte = input & 0xff;
			}
			utfx_converter_write(iconv_opts->converter, &input_byte, 1);
		} else {
			read_count = utfx_converter_read(iconv_opts->converter, &output_byte, 1);
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
	}

	return EXIT_SUCCESS;
}


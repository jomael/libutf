#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
/* on /Wall, it warns that fprintf is not inlined */
/* so, it's basically pointless */
#pragma warning(disable : 4710)
#endif /* _MSC_VER */

#include "encoder.h"
#include "decoder.h"

static int parse_codec(const char * codec);

struct iconv {
	FILE * input_file;
	FILE * output_file;
	utfx_encoder_t * encoder;
	utfx_decoder_t * decoder;
}; /* struct iconv_opts */

static int iconv(struct iconv * iconv_opts); 

int main(int argc, const char ** argv){

	int i = 0;

	int err = 0;

	int exit_code = EXIT_SUCCESS;

	const char * input_codec = 0;

	const char * output_codec = 0;

	const char * output_file_path = 0;

	const char * input_file_path = 0;

	FILE * input_file = stdin;

	FILE * output_file = stdout;

	utfx_encoder_t encoder;

	utfx_decoder_t decoder;

	utfx_encoder_mode_t encoder_mode = UTFX_ENCODER_MODE_NONE;

	int decoder_mode = 0;

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
			/* TODO */
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

	utfx_encoder_init(&encoder);

	encoder_mode = parse_codec(input_codec);
	if (encoder_mode == UTFX_ENCODER_MODE_UNKNOWN){
		fprintf(stderr, "%s: unknown input codec '%s'\n", argv[0], input_codec);
		return EXIT_FAILURE;
	} else {
		utfx_encoder_set_mode(&encoder, encoder_mode);
	}

	utfx_decoder_init(&decoder);

	decoder_mode = parse_codec(output_codec);
	if (decoder_mode == UTFX_DECODER_MODE_UNKNOWN){
		fprintf(stderr, "%s: unknown output codec '%s'\n", argv[0], output_codec);
		return EXIT_FAILURE;
	} else {
		utfx_decoder_set_mode(&decoder, decoder_mode);
	}

	iconv_opts.input_file = input_file;
	iconv_opts.output_file = output_file;
	iconv_opts.encoder = &encoder;
	iconv_opts.decoder = &decoder;

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
	return UTFX_ENCODER_MODE_UNKNOWN;
}

static int iconv(struct iconv * iconv_opts){

	utfx_error_t error = UTFX_ERROR_NONE;

	int result = 0;

	utf32_t decoded_char = 0;

	unsigned int input_byte_count = 0;

	unsigned char input_byte_array[4] = { 0, 0, 0, 0 };

	unsigned int output_byte_count = 0;

	unsigned char output_byte_array[4] = { 0, 0, 0, 0 };

	unsigned int write_count = 0;

	while (!feof(iconv_opts->input_file)){

		input_byte_count += fread(&input_byte_array[input_byte_count], 1, sizeof(input_byte_array) - input_byte_count, iconv_opts->input_file);

		result = utfx_decoder_put_input_char_safely(iconv_opts->decoder, input_byte_array, input_byte_count);
		if (result < 0){
			return -1;
		} else if (result == 1){
			input_byte_array[0] = input_byte_array[1];
			input_byte_array[1] = input_byte_array[2];
			input_byte_array[2] = input_byte_array[3];
		} else if (result == 2){
			input_byte_array[0] = input_byte_array[3];
			input_byte_array[1] = input_byte_array[4];
		} else if (result == 3){
			input_byte_array[0] = input_byte_array[4];
		}

		/* put left over bytes to beginning of buffer */
		input_byte_count -= result;

		result = utfx_decoder_get_output_char(iconv_opts->decoder, &decoded_char);
		if (result < 0){
			return -1;
		}

		error = utfx_encoder_put_input_char(iconv_opts->encoder, decoded_char);
		if (error != UTFX_ERROR_NONE){
			return -1;
		}

		error = utfx_encoder_get_output_char_safely(iconv_opts->encoder, output_byte_array, sizeof(output_byte_array));
		if (error != UTFX_ERROR_NONE){
			return -1;
		}

		output_byte_count = utfx_encoder_get_output_size(iconv_opts->encoder);

		write_count = fwrite(output_byte_array, 1, output_byte_count, iconv_opts->output_file);
		if (write_count != output_byte_count){
			return -1;
		}
	}

	return 0;
}


Utfx
====

Utfx is a C89 library for decoding and encoding UTF8, UTF16, and UTF32 text.

It is meant to be stable, lightweight, fast, and portable.

It is meant to compile on a wide variety of compilers (including MSVC) and operating systems.

It also does not rely on the standard library, so it can even be used in kernel development.

Here's a code snippet that uses an encoder structure to display the greek character sigma:

```
#include <stdio.h>

#include <utfx/encoder.h>
#include <utfx/utf8.h>

int main(void){

	unsigned int output_length = 0;

	utfx_encoder_t encoder;

	utf32_t input_char = 0x03A3;

	utf8_t output_char[4];

	utfx_encoder_init(&encoder);

	utfx_encoder_set_mode(&encoder, UTFX_ENCODER_MODE_UTF8);

	utfx_encoder_put_input_char(&encoder, input_char);

	output_length = utfx_encoder_get_output_char(&encoder, output_char);
	if (output_length > 0){
		fprintf(stdout, "sigma: %.*s\n", output_length, output_char);
	}

	return 0;
}
```

Here's a code snippet that uses the lower level functions to encode sigma:

```
#include <stdio.h>

#include <utfx/utf8.h>

int main(void){

	unsigned int output_length = 0;

	uint8_t output_char[4];

	output_length = utf8_encode(output_char, 0x03A3);
	if (output_length > 0){
		fprintf(stdout, "sigma: %.*s\n", output_length, output_char);
	}

	return 0;
}
```

Note that to run these examples, your terminal should be using UTF8 encoding.

Microsoft's command prompt uses UTF16 by default.

You'll have to change it to UTF8 before running the example, to get meaningful output.

```
chcp 65001
```

If you're using a different terminal, make sure it's using UTF8 to run the examples.

Otherwise you'll get garbage.

# Building

CMake is used as the build system.

To build any CMake project, do this:

```
mkdir build && cd build
cmake ..
cmake --build .
```

To test it, do this:

```
ctest --output-on-failure
```

And to install:

```
cmake --build . --target install
```

But if you're using Make, CMake generates a Makefile containing all the standard targets:

```
make clean
make all
make test
make install
```


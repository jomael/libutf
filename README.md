Utfx
====

[![Build Status](https://travis-ci.org/tholberton/utfx.svg?branch=master)](https://travis-ci.org/tholberton/utfx)

Utfx is a UTF-8, UTF-16, and UTF-32 decoding and encoding library for C89 and C++11.

It is meant to be stable, lightweight, fast, and portable across platforms and compilers.

It conforms with [RFC2279](https://www.ietf.org/rfc/rfc2781.txt) and [RFC2781](https://www.ietf.org/rfc/rfc2279.txt), which are distributed with the source code.

It is meant to compile on a wide variety of compilers (including MSVC) and operating systems.

It also does not rely on the standard library, so it can even be used in kernel development.

Here's a code snippet that uses an encoder structure to display the greek character sigma:

```
#include <stdio.h>

#include <utfx/encoder.h>

int main(void){

	utfx_encoder_t encoder;
	utf32_t input = 0x03A3;
	unsigned char output[4];
	unsigned int output_size = 0;

	utfx_encoder_init(&encoder);
	utfx_encoder_set_mode(&encoder, UTFX_ENCODER_MODE_UTF8);

	utfx_encoder_write(&encoder, input);

	output_size = utfx_encoder_read(&encoder, &output);
	if (output_size > 0){
		fprintf(stdout, "sigma: %.*s\n", output_size, output);
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

Here's a code snippet that uses the C++ API to encode upper case phi into a UTF-8 sequence:

```
#include <utfx/encoder.hpp>
#include <utfx/stl.hpp>

int main(void){

	utfx::Encoder encoder;

	// UTF-8 is actually set by default, but use this function to change it.
	encoder.SetMode(utfx::Encoder::Mode::UTF8);

	// encodes a UTF-32 sequence
	encoder << 0x03a6;

	// included with utfx/stl.hpp
	// This writes all the encoded data to standard output
	std::cout << encoder;

	return 0;
}
```

Note that to run these examples, your terminal should be using UTF-8 encoding.

Microsoft's command prompt uses UTF-16 by default.

You'll have to change it to UTF-8 before running the example, to get meaningful output.

```
chcp 65001
```

If you're using a different terminal, make sure it's using UTF-8 to run the examples.

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

You can choose to omit the C++11 interface, by building the project like this:

```
mkdir build && cd build
cmake .. -DUTFX_LANGUAGE_BINDING_CXX=OFF
cmake --build .
```

# Documentation

Documentation is generated with Doxygen.

On Windows, the documentation is installed as HTML in a `documentation` directory.

On Unix, the documentation is installed as man pages.

Viewing the man pages are done like this:

```
man utfx-lowlevel
man utfx
```

For C++11 classes, do this:

```
man utfx_Decoder
man utfx_Encoder
man utfx_Converter
```

If Doxygen is not installed during the build process, the documentation can be viewed in the header files.


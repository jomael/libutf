libutf
======

[![Travis Badge](https://travis-ci.org/tholberton/libutf.svg?branch=master)](https://travis-ci.org/tholberton/libutf)
[![AppVeyor Badge](https://ci.appveyor.com/api/projects/status/xjbjhuxn3wsc0k61?svg=true)](https://ci.appveyor.com/project/tholberton/libutf)

libutf is a UTF-8, UTF-16, and UTF-32 decoding and encoding library for C89.

It is meant to be stable, lightweight, fast, and portable across platforms and compilers.

It conforms with [RFC2279](https://www.ietf.org/rfc/rfc2781.txt) and [RFC2781](https://www.ietf.org/rfc/rfc2279.txt), which are distributed with the source code.

It is meant to compile on a wide variety of compilers (including MSVC) and operating systems.

# Installing

On Ubuntu, you can install the project using `apt-add-repository`, like this:

```
sudo apt-add-repository ppa:taylorcholberton/libutf
sudo apt-get update
sudo apt-get install libutf
```

# Building

CMake is used as the primary build system, but GNU Make and NMake are also available.

To build the project using CMake, do this:

```
mkdir build && cd build
cmake ..
cmake --build .
ctest --verbose --output-on-failure
cmake --build . --target install
```

With GNU Make, do this:

```
make
make test
make install
```

With NMake, do this:

```
nmake -f NMakefile
nmake -f NMakefile install
```

# Documentation

Documentation is generated with Doxygen.

On Windows, the documentation is installed as HTML in a `documentation` directory.

On Unix, the documentation is installed as man pages.

Viewing the man pages are done like this:

```
man libutf-procedural
man libutf
```

If Doxygen is not installed during the build process, the documentation can be viewed in the header files.


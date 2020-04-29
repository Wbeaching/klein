# Simple KLEIN (lighweight block cipher) implementation

This repository contains simple implementation (written in C) of KLEIN block cipher. More information about this cipher can be found in authors' paper: [KLEIN: A New Family of Lightweight Block Ciphers](https://research.utwente.nl/files/5095831/The_KLEIN_Block_Cipher.pdf).

## Library compilation and usage

KLEIN implementation can be compiled to both static and dynamic library. To build both libraries call:

```shell
make library
```

Header file (*sklein.h*) and two versions of library (*libsklein.a* and *libsklein.so*) will be placed in output directory (*./build*).

## Demo app compilation

Simple demo application that shows how to use this implementation can be found in *./demo/demo.c*. To build demo application call:

```bash
make demo
```

Executable file will be stored in *./build/sklein-demo*. Currently demo presents only usage of *KLEIN-64*.

## Tests and test vectors

To validate implemented encryption and decryption test vectors from KLEIN specification (Appendix A.) are used. All test related files are stored in *./test* directory. Test vectors are declared and defined in *test-vectors.h* and *test-vectors.c* respectively. Simple "test engine" implementation can be found in *main.c*.

To build and launch tests one has to call:

```bash
make tests
```

Test binary will be created in *./build/sklein-tests* directory and executed.

## Disclaimer

This implementation has been written "just for fun" and is published "AS IS". It is not optimized neither analyzed for security weakness.

Code form this repository can be included in other projects in parts or as a whole but it is not recommended to use it in production environment.

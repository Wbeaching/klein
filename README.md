# SKLEIN - a Simple KLEIN implementation

This repository contains an implementation of KLEIN lightweight block cipher block cipher written in C language. For information about this cipher please read authors' paper: [KLEIN: A New Family of Lightweight Block Ciphers](https://research.utwente.nl/files/5095831/The_KLEIN_Block_Cipher.pdf).

## Source code compilation

### Library compilation

KLEIN implementation can be compiled into both static and dynamic library. To build (S)KLEIN libraries call:

```shell
make library
```

Header file (*sklein.h*) and two versions of library (*libsklein.a* and *libsklein.so*) will be placed in output directory (*./build*).

### Demo app compilation

Simple demo application that shows how to use this implementation can be found in *./demo/demo.c*. To build demo application call:

```bash
make demo
```

Executable file will be stored in *./build/sklein-demo*. Currently demo presents only usage of *KLEIN-64*.

### Tests compilation and launching

To validate implemented encryption and decryption test vectors from KLEIN specification (Appendix A.) are used. All test related files are stored in *./test* directory. Test vectors are declared and defined in *test-vectors.h* and *test-vectors.c* respectively. Simple "test engine" implementation can be found in *main.c*.

To build and launch tests one has to call:

```bash
make tests
```

Test binary will be created in *./build/sklein-tests* directory and executed.

## SKLEIN library usage

### Header file and API

All necessary SKLEIN data types and functions are defined in *sklein.h" header file. SKLEIN API is mainly composed of following 5 functions:

```C
sklein_t sklein_create(int km);

int sklein_set_key(sklein_t crypter, const uint8_t *mkey, uint8\_t k\_length);

int sklein\_encrypt\_block(sklein\_t crypter, uint8\_t *block);

int sklein_decrypt_block(sklein_t crypter, uint8_t *block);

void sklein\_destroy(sklein\_t crypter);
```

Please see mentioned header for more details.

### Examples

This library provides only implementation of KLEIN block cipher with support of one block only encryption/decryption based on algorith specification. To encrypt 8B (one block) of data using KLEIN-64 following steps are needed:

```C
    sklein_t crypter = sklein_create(KLEIN_MODE_64);
    if (crypter == NULL)
    {
        printf("ERROR: Failed to create KLEIN-64\n");
        return 1;
    }

    uint8_t data64[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    uint8_t key64[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef};

    int result = 0;
    result = sklein_set_key(crypter, key64, sizeof(key64));
    if (result != KLEIN_RESULT_OK)
    {
        printf("ERROR: Failed to set key: %d\n", result);
        return 1;
    }

    result = sklein_encrypt_block(crypter, data64);
    if (result != KLEIN_RESULT_OK)
    {
        printf("ERROR: Failed to crypt\n");
        return 1;
    }
```

In similar way encrypted data can be decrypted with use of provided implementation:

```C
    sklein_t crypter = sklein_create(KLEIN_MODE_64);
    if (crypter == NULL)
    {
        printf("ERROR: Failed to create KLEIN-64\n");
        return 1;
    }

    uint8_t data64[] = {0x59, 0x23, 0x56, 0xC4, 0x99, 0x71, 0x76, 0xC8};
    uint8_t key64[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef};

    int result = 0;
    result = sklein_set_key(crypter, key64, sizeof(key64));
    if (result != KLEIN_RESULT_OK)
    {
        printf("ERROR: Failed to set key: %d\n", result);
        return 1;
    }

    result = sklein_decrypt_block(crypter, data64);
    if (result != KLEIN_RESULT_OK)
    {
        printf("ERROR: Failed to decrypt\n");
        return 1;
    }

```

Please see provided *demo/demo.c* file for full encryption/decryption example.

### KLEIN in CBC (Cipher BLock Chaining) mode

For encrypting data sets larger than one block (8B) KLEIN cipher has been enclosed in Cipher Block Chaining algorithm. It uses 8B Initialization Vector and encrypts blocks of N*8B length.

Functions below have been added specificaly for CBC mode:

```C
int sklein_set_iv(sklein_t crypter, const uint8_t *iv);

int sklein_cbc_encrypt_data(sklein_t crypter, uint8_t *data, size_t len);

int sklein_cbc_decrypt_data(sklein_t crypter, uint8_t *data, size_t len);
```

Both *encrypt* and *decrypt* functions are placing encryption result in input data buffer.

## Disclaimer

This implementation has been written "just for fun" and is published "AS IS". It is not optimized neither analyzed for security weakness.

Code form this repository can be included in other projects in parts or as a whole but it is not recommended to use it in production environment.

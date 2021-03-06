#include <sklein.h>
#include "test-vectors.h"

struct test_case test_klein64_1;
struct test_case test_klein64_2;
struct test_case test_klein64_3;
struct test_case test_klein64_4;

struct test_case test_klein80_1;
struct test_case test_klein80_2;
struct test_case test_klein80_3;
struct test_case test_klein80_4;

struct test_case test_klein96_1;
struct test_case test_klein96_2;
struct test_case test_klein96_3;
struct test_case test_klein96_4;

int klein_test_count = 12;
struct test_case *klein_test_data[12] = {
    &test_klein64_1, &test_klein64_2, &test_klein64_3, &test_klein64_4,
    &test_klein80_1, &test_klein80_2, &test_klein80_3, &test_klein80_4,
    &test_klein96_1, &test_klein96_2, &test_klein96_3, &test_klein96_4};

// KLEIN-64 test vectors
uint8_t key64_1[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t data64_1[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t result64_1[] = {0xCD, 0xC0, 0xB5, 0x1F, 0x14, 0x72, 0x2B, 0xBE};

uint8_t key64_2[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t data64_2[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t result64_2[] = {0x64, 0x56, 0x76, 0x4E, 0x86, 0x02, 0xE1, 0x54};

uint8_t data64_3[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t key64_3[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
uint8_t result64_3[] = {0x59, 0x23, 0x56, 0xC4, 0x99, 0x71, 0x76, 0xC8};

uint8_t data64_4[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
uint8_t key64_4[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t result64_4[] = {0x62, 0x9F, 0x9D, 0x6D, 0xFF, 0x95, 0x80, 0x0E};

struct test_case test_klein64_1 = {
    .mode = KLEIN_MODE_64,
    .data = data64_1,
    .data_len = 8,
    .key = key64_1,
    .key_len = 8,
    .result = result64_1,
};

struct test_case test_klein64_2 = {
    .mode = KLEIN_MODE_64,
    .data = data64_2,
    .data_len = 8,
    .key = key64_2,
    .key_len = 8,
    .result = result64_2,
};

struct test_case test_klein64_3 = {
    .mode = KLEIN_MODE_64,
    .data = data64_3,
    .data_len = 8,
    .key = key64_3,
    .key_len = 8,
    .result = result64_3,
};

struct test_case test_klein64_4 = {
    .mode = KLEIN_MODE_64,
    .data = data64_4,
    .data_len = 8,
    .key = key64_4,
    .key_len = 8,
    .result = result64_4,
};

// KLEIN-80 test vectors
uint8_t key80_1[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t data80_1[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t result80_1[] = {0x66, 0x77, 0xE2, 0x0D, 0x1A, 0x53, 0xA4, 0x31};

uint8_t key80_2[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t data80_2[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t result80_2[] = {0x82, 0x24, 0x75, 0x02, 0x27, 0x3D, 0xCC, 0x5F};

uint8_t key80_3[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF, 0x12, 0x34};
uint8_t data80_3[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t result80_3[] = {0x3F, 0x21, 0x0F, 0x67, 0xCB, 0x23, 0x68, 0x7A};

uint8_t key80_4[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t data80_4[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
uint8_t result80_4[] = {0xBA, 0x52, 0x39, 0xE9, 0x3E, 0x78, 0x43, 0x66};

struct test_case test_klein80_1 = {
    .mode = KLEIN_MODE_80,
    .data = data80_1,
    .data_len = 8,
    .key = key80_1,
    .key_len = 10,
    .result = result80_1,
};

struct test_case test_klein80_2 = {
    .mode = KLEIN_MODE_80,
    .data = data80_2,
    .data_len = 8,
    .key = key80_2,
    .key_len = 10,
    .result = result80_2,
};

struct test_case test_klein80_3 = {
    .mode = KLEIN_MODE_80,
    .data = data80_3,
    .data_len = 8,
    .key = key80_3,
    .key_len = 10,
    .result = result80_3,
};

struct test_case test_klein80_4 = {
    .mode = KLEIN_MODE_80,
    .data = data80_4,
    .data_len = 8,
    .key = key80_4,
    .key_len = 10,
    .result = result80_4,
};

// KLEIN-96 test vectors
uint8_t key96_1[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t data96_1[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t result96_1[] = {0xDB, 0x9F, 0xA7, 0xD3, 0x3D, 0x8E, 0x8E, 0x36};

uint8_t key96_2[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t data96_2[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t result96_2[] = {0x15, 0xA3, 0xA0, 0x33, 0x86, 0xA7, 0xFE, 0xC6};

uint8_t key96_3[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56, 0x78};
uint8_t data96_3[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t result96_3[] = {0x79, 0x68, 0x77, 0x98, 0xAF, 0xDA, 0x0B, 0xC3};

uint8_t key96_4[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t data96_4[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
uint8_t result96_4[] = {0x50, 0x06, 0xA9, 0x87, 0xA5, 0x00, 0xBF, 0xDD};

struct test_case test_klein96_1 = {
    .mode = KLEIN_MODE_96,
    .data = data96_1,
    .data_len = 8,
    .key = key96_1,
    .key_len = 12,
    .result = result96_1,
};

struct test_case test_klein96_2 = {
    .mode = KLEIN_MODE_96,
    .data = data96_2,
    .data_len = 8,
    .key = key96_2,
    .key_len = 12,
    .result = result96_2,
};

struct test_case test_klein96_3 = {
    .mode = KLEIN_MODE_96,
    .data = data96_3,
    .data_len = 8,
    .key = key96_3,
    .key_len = 12,
    .result = result96_3,
};

struct test_case test_klein96_4 = {
    .mode = KLEIN_MODE_96,
    .data = data96_4,
    .data_len = 8,
    .key = key96_4,
    .key_len = 12,
    .result = result96_4,
};

// test data for KLEIN-CBC
size_t klein_test_cbc_1_len = 24;
uint8_t klein_test_cbc_1_data[24] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                     0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t klein_test_cbc_1_iv[8] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
uint8_t klein_test_cbc_1_key[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

size_t klein_test_cbc_2_len = 48;
uint8_t klein_test_cbc_2_data[48] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF,
                                     0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF,
                                     0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF,
                                     0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF,
                                     0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF,
                                     0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
uint8_t klein_test_cbc_2_iv[8] = {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t klein_test_cbc_2_key[8] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};

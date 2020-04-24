#include <simple-klein.h>
#include "test-vectors.h"

struct test_case test_klein64_1;
struct test_case test_klein64_2;
struct test_case test_klein64_3;
struct test_case test_klein64_4;

int klein_test_count = 4;
struct test_case *klein_test_data[4] = {&test_klein64_1, &test_klein64_2, &test_klein64_3, &test_klein64_4};

uint8_t key64_1[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t data64_1[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t result_64_1[] = {0xCD, 0xC0, 0xB5, 0x1F, 0x14, 0x72, 0x2B, 0xBE};

uint8_t key64_2[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t data64_2[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t result_64_2[] = {0x64, 0x56, 0x76, 0x4E, 0x86, 0x02, 0xE1, 0x54};

uint8_t data64_3[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t key64_3[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
uint8_t result_64_3[] = {0x59, 0x23, 0x56, 0xC4, 0x99, 0x71, 0x76, 0xC8};

uint8_t data64_4[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
uint8_t key64_4[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t result_64_4[] = {0x62, 0x9F, 0x9D, 0x6D, 0xFF, 0x95, 0x80, 0x0E};

struct test_case test_klein64_1 = {
    .mode = KLEIN_MODE_64,
    .data = data64_1,
    .data_len = 8,
    .key = key64_1,
    .key_len = 8,
    .result = result_64_1,
};

struct test_case test_klein64_2 = {
    .mode = KLEIN_MODE_64,
    .data = data64_2,
    .data_len = 8,
    .key = key64_2,
    .key_len = 8,
    .result = result_64_2,
};

struct test_case test_klein64_3 = {
    .mode = KLEIN_MODE_64,
    .data = data64_3,
    .data_len = 8,
    .key = key64_3,
    .key_len = 8,
    .result = result_64_3,
};

struct test_case test_klein64_4 = {
    .mode = KLEIN_MODE_64,
    .data = data64_4,
    .data_len = 8,
    .key = key64_4,
    .key_len = 8,
    .result = result_64_4,
};

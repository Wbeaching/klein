#ifndef __TEST_VECTORS_H__
#define __TEST_VECTORS_H__

#include <stdint.h>
#include <stdlib.h>

struct test_case
{
    int mode;
    uint8_t *data;
    size_t data_len; // currently ignored as only one-block (8B) supported
    uint8_t *key;
    size_t key_len;  // has to match length defined by KLEIN mode
    uint8_t *result; // len same as in data
};

int klein_test_count;
struct test_case *klein_test_data[12];

// data for CBC tests
size_t klein_test_cbc_1_len;
uint8_t klein_test_cbc_1_data[24];
uint8_t klein_test_cbc_1_iv[8];
uint8_t klein_test_cbc_1_key[8];

size_t klein_test_cbc_2_len;
uint8_t klein_test_cbc_2_data[48];
uint8_t klein_test_cbc_2_iv[8];
uint8_t klein_test_cbc_2_key[8];

#endif // __TEST_VECTORS_H__

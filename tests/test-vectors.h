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
struct test_case *klein_test_data[4];

#endif // __TEST_VECTORS_H__

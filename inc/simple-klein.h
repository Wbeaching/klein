#ifndef __SIMPLE_KLEIN_H__
#define __SIMPLE_KLEIN_H__

#include <stdint.h>

typedef struct simple_klein *sklein_t;

enum klein_mode
{
    KLEIN_MODE_64 = 0,
    KLEIN_MODE_80,
    KLEIN_MODE_96,
};

enum klein_result
{
    KLEIN_RESULT_OK = 0,
    KLEIN_RESULT_FAIL,
    KLEIN_RESULT_INVALID_PARAM,
    KLEIN_RESULT_INVALID_LENGTH,
};

sklein_t sklein_init(int km);

int sklein_set_key(sklein_t crypter, const uint8_t *mkey, uint8_t k_length);

// simple function for crypting one single block
// allocated array length has to match selected block size
int sklein_crypt_block(sklein_t crypter, uint8_t *block);

int sklein_decrypt_block(sklein_t crypter, uint8_t *block);

void sklein_destroy(sklein_t crypter);

#endif

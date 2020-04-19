#include <stdlib.h>
#include <string.h>

#include "internals.h"

// number of rounds for KLEIN_MODE_64, _80 and 96 respectively
static const uint8_t ROUND_COUNT[3] = {12, 16, 20};
// key length for KLEIN_MODE_64, _80 and 96 respectively
static const uint8_t KEY_SIZE[3] = {8, 10, 12};

sklein_t sklein_init(int km)
{
    if (km < KLEIN_MODE_64 || km > KLEIN_MODE_96)
    {
        return NULL;
    }
    sklein_t result = malloc(sizeof(struct simple_klein));
    memset(result, 0x0, sizeof(struct simple_klein));
    result->mode = km;
}

int sklein_set_key(sklein_t crypter, const uint8_t *mkey, uint8_t k_length)
{
    if (!crypter || !mkey)
    {
        return KLEIN_RESULT_INVALID_PARAM;
    }
    if (k_length != KEY_SIZE[crypter->mode])
    {
        return KLEIN_RESULT_INVALID_LENGTH;
    }
    memcpy(crypter->mkey, mkey, k_length);

    return KLEIN_RESULT_OK;
}

int sklein_crypt_block(sklein_t crypter, uint8_t *block)
{
    return KLEIN_RESULT_OK;
}

int sklein_decrypt_block(sklein_t crypter, uint8_t *block)
{
    return KLEIN_RESULT_OK;
}

void sklein_destroy(sklein_t crypter)
{
    if (crypter == NULL)
    {
        return;
    }
}

#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#include "internals.h"

sklein_t sklein_create(int km)
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
    // prepare necessary data/variables
    uint8_t state[BLOCK_SIZE];       // state as N 8-bit words
    uint8_t nibbles[BLOCK_SIZE * 2]; // state as 2N 4-bit words (stored in 8-bit vars)
    uint8_t subkey[12];              // prepare space for longest supported key
    uint8_t key_len = KEY_SIZE[crypter->mode];
    uint8_t rounds = ROUND_COUNT[crypter->mode];
    // copy input data
    memcpy(state, block, BLOCK_SIZE);
    memcpy(subkey, crypter->mkey, key_len);
    // start KLEIN rounds
    for (int i = 1; i <= rounds; ++i)
    {
#ifdef DEBUG
        printf("[round number: %d]\n", i);
#endif
        add_round_key(state, subkey);
        // operations with 4-bit nibbles start
        split_nibbles(state, nibbles);
        sub_nibbles(nibbles);
        // operations with 4-bit nibbles end
        merge_nibbles(state, nibbles);
        rotate_nibbles(state);
        mix_nibbles(state);
        key_schedule(subkey, key_len, i);
    }
    add_round_key(state, subkey); // subkey for round Nr+1
    memcpy(block, state, BLOCK_SIZE);
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

const char *klein_mode_to_string(int mode)
{
    switch (mode)
    {
    case KLEIN_MODE_64:
        return "KLEIN_MODE_64";
        break;
    case KLEIN_MODE_80:
        return "KLEIN_MODE_80";
        break;
    case KLEIN_MODE_96:
        return "KLEIN_MODE_96";
        break;
    default:
        return "unknown";
        break;
    }
}

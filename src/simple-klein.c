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

int sklein_encrypt_block(sklein_t crypter, uint8_t *block)
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
        rotate_nibbles_enc(state);
        mix_nibbles_enc(state);
        key_schedule_enc(subkey, key_len, i);
    }
    add_round_key(state, subkey); // subkey for round Nr+1
    memcpy(block, state, BLOCK_SIZE);
    return KLEIN_RESULT_OK;
}

int sklein_decrypt_block(sklein_t crypter, uint8_t *block)
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

    // schedule key to last encryption round
    for (int i = 1; i <= rounds; ++i)
    {
        key_schedule_enc(subkey, key_len, i);
    }
    add_round_key(state, subkey); // subkey for round 13 (last used on ecryption)

    // start KLEIN decrypion rounds
    for (int i = rounds; i >= 1; --i)
    {
#ifdef DEBUG
        printf("[round number: %d]\n", i);
#endif
        key_schedule_dec(subkey, key_len, i);
        mix_nibbles_dec(state);
        rotate_nibbles_dec(state);
        // operations with 4-bit nibbles start
        split_nibbles(state, nibbles);
        sub_nibbles(nibbles);
        merge_nibbles(state, nibbles);
        // operations with 4-bit nibbles end
        add_round_key(state, subkey);
    }
    memcpy(block, state, BLOCK_SIZE);
    return KLEIN_RESULT_OK;
}

void sklein_destroy(sklein_t crypter)
{
    if (crypter == NULL)
    {
        return;
    }
    // let's not leave any information about KLEIN settings (ex. key) in memory
    memset(crypter, 0xff, sizeof(struct simple_klein));
    free(crypter);
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

int sklein_set_iv(sklein_t crypter, const uint8_t *iv)
{
    if (!crypter || !iv)
    {
        return KLEIN_RESULT_INVALID_PARAM;
    }
    memcpy(crypter->iv, iv, BLOCK_SIZE);
    return KLEIN_RESULT_FAIL;
}

int sklein_cbc_encrypt_data(sklein_t crypter, uint8_t *data, size_t len)
{
    if (!crypter || !data)
    {
        return KLEIN_RESULT_INVALID_PARAM;
    }
    if (len == 0 || len & 0x07)
    {
        // not a multiply of 8
        return KLEIN_RESULT_INVALID_LENGTH;
    }

    for (int i = 0; i < (len >> 3); ++i)
    {
        // first XOR input block with IV (same operation as done by add_round_key() )
        add_round_key(data, crypter->iv);
        // use standard KLEIN encryption for one block
        sklein_encrypt_block(crypter, data);
        // copy current output as next IV
        memcpy(crypter->iv, data, BLOCK_SIZE);
        // move data pointer
        data += BLOCK_SIZE;
    }
    return KLEIN_RESULT_OK;
}

int sklein_cbc_decrypt_data(sklein_t crypter, uint8_t *data, size_t len)
{
    if (!crypter || !data)
    {
        return KLEIN_RESULT_INVALID_PARAM;
    }
    if (len == 0 || len & 0x07)
    {
        // not a multiply of 8
        return KLEIN_RESULT_INVALID_LENGTH;
    }

    // buffer for storing input to used later as old IV
    uint8_t iv_buffer[BLOCK_SIZE];

    for (int i = 0; i < (len >> 3); ++i)
    {
        // save input block as future IV backup
        memcpy(iv_buffer, data, BLOCK_SIZE);
        // use standard KLEIN decryption for one block
        sklein_decrypt_block(crypter, data);
        // XOR decrypted block with IV (same operation as done by add_round_key() )
        add_round_key(data, crypter->iv);
        // copy input backup as next IV
        memcpy(crypter->iv, iv_buffer, BLOCK_SIZE);
        // move data pointer
        data += BLOCK_SIZE;
    }
    return KLEIN_RESULT_OK;
}

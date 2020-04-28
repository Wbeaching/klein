#include <string.h>
// for debug prints only
#include <stdio.h>

#include "internals.h"

// number of rounds for KLEIN_MODE_64, _80 and 96 respectively
const uint8_t ROUND_COUNT[3] = {12, 16, 20};
// key length for KLEIN_MODE_64, _80 and 96 respectively
const uint8_t KEY_SIZE[3] = {8, 10, 12};

void add_round_key(uint8_t *state, uint8_t *subkey)
{
    for (int i = 0; i < BLOCK_SIZE; ++i)
    {
        state[i] ^= subkey[i];
    }
    print_named_buffer("add_round_key result", state, BLOCK_SIZE);
}

uint8_t sbox(uint8_t input)
{
    static uint8_t _sbox_transform[16] = {
        0x07, 0x04, 0x0a, 0x09,
        0x01, 0x0f, 0x0b, 0x00,
        0x0c, 0x03, 0x02, 0x06,
        0x08, 0x0e, 0x0d, 0x05};
    return _sbox_transform[input];
}

uint8_t gal_x4_1(uint8_t input)
{
    return ((input & 0xff) ^ (input >> 4)) & 0x0f;
}

void sub_nibbles(uint8_t *nibbles)
{
    uint8_t *input = nibbles;
    for (int i = 0; i < 2 * BLOCK_SIZE; ++i, input++)
    {
        *input = sbox(*input);
    }
    print_named_buffer("sub_nibbles result", nibbles, 2 * BLOCK_SIZE);
}

void rotate_nibbles_enc(uint8_t *state)
{
    static uint8_t temp[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; ++i)
    {
        temp[i] = state[(i + 2) % 8];
    }
    memcpy(state, temp, BLOCK_SIZE);
    print_named_buffer("rotate_nibbles result", state, BLOCK_SIZE);
}

void rotate_nibbles_dec(uint8_t *state)
{
    static uint8_t temp[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; ++i)
    {
        temp[(i + 2) % 8] = state[i];
    }
    memcpy(state, temp, BLOCK_SIZE);
    print_named_buffer("rotate_nibbles_dec result", state, BLOCK_SIZE);
}

static uint8_t gmult(uint8_t value1, uint8_t value2)
{
    uint8_t p = 0;
    uint8_t hi_bit_set;
    for (uint8_t counter = 0; counter < 8; counter++)
    {
        if ((value2 & 1) == 1)
            p ^= value1;
        hi_bit_set = (value1 & 0x80);
        value1 <<= 1;
        if (hi_bit_set == 0x80)
            value1 ^= 0x1b;
        value2 >>= 1;
    }
    return p;
}

static void mix_column_enc(uint8_t *cols)
{
    uint8_t result[4];

    result[0] = gmult(cols[0], 2) ^ gmult(cols[1], 3) ^ gmult(cols[2], 1) ^ gmult(cols[3], 1);
    result[1] = gmult(cols[0], 1) ^ gmult(cols[1], 2) ^ gmult(cols[2], 3) ^ gmult(cols[3], 1);
    result[2] = gmult(cols[0], 1) ^ gmult(cols[1], 1) ^ gmult(cols[2], 2) ^ gmult(cols[3], 3);
    result[3] = gmult(cols[0], 3) ^ gmult(cols[1], 1) ^ gmult(cols[2], 1) ^ gmult(cols[3], 2);

    memcpy(cols, result, 4);
}

static void mix_column_dec(uint8_t *cols)
{
    uint8_t result[4];

    result[0] = gmult(cols[0], 0x0e) ^ gmult(cols[1], 0x0b) ^ gmult(cols[2], 0x0d) ^ gmult(cols[3], 0x09);
    result[1] = gmult(cols[0], 0x09) ^ gmult(cols[1], 0x0e) ^ gmult(cols[2], 0x0b) ^ gmult(cols[3], 0x0d);
    result[2] = gmult(cols[0], 0x0d) ^ gmult(cols[1], 0x09) ^ gmult(cols[2], 0x0e) ^ gmult(cols[3], 0x0b);
    result[3] = gmult(cols[0], 0x0b) ^ gmult(cols[1], 0x0d) ^ gmult(cols[2], 0x09) ^ gmult(cols[3], 0x0e);

    memcpy(cols, result, 4);
}

void mix_nibbles_enc(uint8_t *state)
{
    mix_column_enc(state);
    mix_column_enc(state + 4);
    print_named_buffer("mix_nibbles result", state, BLOCK_SIZE);
}

void mix_nibbles_dec(uint8_t *state)
{
    mix_column_dec(state);
    mix_column_dec(state + 4);
    print_named_buffer("mix_nibbles_dec result", state, BLOCK_SIZE);
}

void key_schedule_enc(uint8_t *subkey, uint8_t keylen, uint8_t round)
{
    uint8_t half_key = keylen / 2; // value used multiple times
    // prepare for longest key size + 1 (used in rotation)
    uint8_t part_a[KEY_SIZE[KLEIN_MODE_96] / 2];
    uint8_t part_b[KEY_SIZE[KLEIN_MODE_96] / 2];
    uint8_t temp[KEY_SIZE[KLEIN_MODE_96] / 2];

    // copy two halfes (with rotation)
    for (int i = 0; i < half_key - 1; ++i)
    {
        part_a[i] = subkey[i + 1];
        part_b[i] = subkey[i + 1 + half_key];
    }
    // finish rotation
    part_a[half_key - 1] = subkey[0];
    part_b[half_key - 1] = subkey[half_key];

    memcpy(temp, part_b, half_key);
    // WARNING: be carefull when changing this loop!
    // order of operations inside is crucial!
    for (int i = 0; i < half_key; ++i)
    {
        part_b[i] = part_a[i] ^ part_b[i];
        part_a[i] = temp[i];
    }
    // ========

    // update part_a
    part_a[2] ^= round;

    // update part_b
    temp[0] = sbox(part_b[1] >> 4);
    temp[1] = sbox(part_b[1] & 0x0f);
    temp[2] = sbox(part_b[2] >> 4);
    temp[3] = sbox(part_b[2] & 0x0f);
    part_b[1] = temp[0] << 4 | temp[1];
    part_b[2] = temp[2] << 4 | temp[3];

    // merge both parts back to the key
    for (int i = 0; i < half_key; ++i)
    {
        subkey[i] = part_a[i];
        subkey[i + half_key] = part_b[i];
    }
    print_named_buffer("key_schedule:key after", subkey, keylen);
}

void key_schedule_dec(uint8_t *subkey, uint8_t keylen, uint8_t round)
{
    uint8_t half_key = keylen / 2; // value used multiple times
    // prepare for longest key size + 1 (used in rotation)
    uint8_t part_a[KEY_SIZE[KLEIN_MODE_96] / 2];
    uint8_t part_b[KEY_SIZE[KLEIN_MODE_96] / 2];
    uint8_t temp[KEY_SIZE[KLEIN_MODE_96] / 2];

    // copy two halfes
    for (int i = 0; i < half_key; ++i)
    {
        part_a[i] = subkey[i];
        part_b[i] = subkey[i + half_key];
    }

    // update part_a
    part_a[2] ^= round;

    // update part_b
    temp[0] = sbox(part_b[1] >> 4);
    temp[1] = sbox(part_b[1] & 0x0f);
    temp[2] = sbox(part_b[2] >> 4);
    temp[3] = sbox(part_b[2] & 0x0f);
    part_b[1] = temp[0] << 4 | temp[1];
    part_b[2] = temp[2] << 4 | temp[3];

    memcpy(temp, part_a, half_key);
    // WARNING: be carefull when changing this loop!
    // order of operations inside is crucial!
    for (int i = 0; i < half_key; ++i)
    {
        part_a[i] = part_a[i] ^ part_b[i];
        part_b[i] = temp[i];
    }
    // ========

    // merge (with rotation) both parts back to the key
    for (int i = 0; i < half_key - 1; ++i)
    {
        subkey[i + 1] = part_a[i];
        subkey[i + half_key + 1] = part_b[i];
    }
    // finish rotation
    subkey[0] = part_a[half_key - 1];
    subkey[half_key] = part_b[half_key - 1];

    print_named_buffer("key_schedule:key after", subkey, keylen);
}

// utility function for switching between 8*8b <-> 16*4b
void split_nibbles(uint8_t *state, uint8_t *nibbles)
{
    uint8_t *input = state;
    uint8_t *output = nibbles;
    for (int i = 0; i < BLOCK_SIZE; ++i)
    {
        *output = (*input & 0xf0) >> 4;
        output++;
        *output = (*input & 0x0f);
        output++;
        input++;
    }
}

void merge_nibbles(uint8_t *state, uint8_t *nibbles)
{
    uint8_t *input = nibbles;
    uint8_t *output = state;
    for (int i = 0; i < BLOCK_SIZE; ++i)
    {
        *output = *input << 4 | *(input + 1);
        output++;
        input += 2;
    }
}
// =====

#ifdef DEBUG
void print_named_buffer(const char *name, uint8_t *buffer, uint8_t len)
{
    if (!name || !buffer || len == 0)
    {
        return;
    }
    printf(">> %s: ", name);
    for (int i = 0; i < len; ++i)
    {
        printf("%02X ", buffer[i]);
    }
    printf("\n");
}
#endif

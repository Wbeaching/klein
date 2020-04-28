#ifndef __KLEIN_INTERNALS_H__
#define __KLEIN_INTERNALS_H__

#include <stdint.h>

#include <simple-klein.h>

// block size is always 8B
#define BLOCK_SIZE 8
// masks for sub_nibbles() operations
#define HIGHER 0xf0
#define LOWER 0x0f

const uint8_t ROUND_COUNT[3];
const uint8_t KEY_SIZE[3];

struct simple_klein
{
    enum klein_mode mode;
    uint8_t mkey[12];  // prepare structure for longest key (KLEIN-96)
    int8_t nr;         // number of rounds (defined by mode)
    int8_t curr_round; // current round number
};

// in this function only 8B (64b) of key are used in any supported mode
void add_round_key(uint8_t *state, uint8_t *subkey);

void sub_nibbles(uint8_t *state);

void rotate_nibbles_enc(uint8_t *state);

void rotate_nibbles_dec(uint8_t *state);

void mix_nibbles_enc(uint8_t *state);

void mix_nibbles_dec(uint8_t *state);

void key_schedule_enc(uint8_t *subkey, uint8_t keylen, uint8_t round);

void key_schedule_dec(uint8_t *subkey, uint8_t keylen, uint8_t round);

void split_nibbles(uint8_t *state, uint8_t *nibbles);

void merge_nibbles(uint8_t *state, uint8_t *nibbles);

// utility (debug only) function
#ifdef DEBUG
void print_named_buffer(const char *name, uint8_t *buffer, uint8_t len);
#else
#define print_named_buffer(x, y, z)
#endif

#endif // __KLEIN_INTERNALS_H__

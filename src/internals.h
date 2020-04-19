#ifndef __KLEIN_INTERNALS_H__
#define __KLEIN_INTERNALS_H__

#include <stdint.h>

#include <simple-klein.h>

struct simple_klein
{
    enum klein_mode mode;
    uint8_t mkey[12];  // prepare structure for longest key (KLEIN-96)
    int8_t nr;         // number of rounds (defined by mode)
    int8_t curr_round; // current round number
};

#endif // __KLEIN_INTERNALS_H__

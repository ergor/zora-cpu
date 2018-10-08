
#include <stdio.h>
#include <stdint.h>
#include <endian.h>

#include "mcode.h"
#include "ctrl_lines.h"

// flip all bits, then reflip only active high bits
void convert_active_lo(uint64_t *buf, int len)
{
    uint8_t active_hi[] = { ACTV_HIS };
    uint64_t act_hi_fields = 0;

    for (int i = 0; i < sizeof(active_hi); i++)
        act_hi_fields |= 1UL << active_hi[i];

    for (int i = 0; i < len; i++) {
        buf[i] = ~buf[i];
        buf[i] ^= act_hi_fields;
    }
}

void convert_big_endian(uint64_t *buf, int len)
{
    for (int i = 0; i < len; i++)
        buf[i] = htobe64(buf[i]);
}

int main(int argc, char** argv)
{
    uint64_t mcode_store[ROM_A_SPACE] = { 0 };

    mcode_store[0x000] = FETCH;

    mcode_store[0x10e] = FETCH;

    REPEAT(MOV, 8*8, 0100, mcode_store);
    convert_active_lo(mcode_store, ROM_A_SPACE);
    convert_big_endian(mcode_store, ROM_A_SPACE);

    fwrite(mcode_store, sizeof(uint64_t), ROM_A_SPACE, stdout);

    return 0;
}

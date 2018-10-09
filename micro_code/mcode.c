
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

    /* 0x0__ : opcode entries (T0 of all opcodes are here) */
    mcode_store[NOP] = NEXT(SEL_ENC);                   // NOP
    mcode_store[CALL] = CALL_T0;                // CALL a16
    mcode_store[RET] = RET_T0;                  // RET
    mcode_store[JMP] = JMP_T0;                  // JMP
    AREA(JMP_COND, 5, 2, JMP_C_BASE, mcode_store);
    REPEAT(LD_D8, 8, LD_D8_BASE, mcode_store);  // LD d8, rx
    REPEAT(MOV, 8*8, MOV_BASE, mcode_store);        // MOV rs, rd
    AREA(ALU_LD_TMP, 5, 8, ALU_DB_BASE, mcode_store);   // ALUOP rx, no carry
    AREA(ALU_LD_TMP, 2, 16, ALU_DB_BASE, mcode_store);  // ALUOP rx, w/ carry
    AREA(SHFT, 2, 8, SHFT_BASE, mcode_store);       // SHL/SHR

    /* 0x1__ : special micro ops and opcode cycles T1..N */
    mcode_store[FETCH_POS] = FETCH;
    mcode_store[BRANCH_MISS    ] = BRA_MISS_0;
    mcode_store[BRANCH_MISS + 1] = BRA_MISS_1;
    mcode_store[BRANCH_HIT] = JMP_T0;

    mcode_store[PC_LOAD_AR_POS] = PC_LOAD_AR;
    mcode_store[CALL_T1_POS] = CALL_T1;
    mcode_store[CALL_T1_POS+1] = CALL_T2;
    mcode_store[CALL_T1_POS+2] = CALL_T3;
    mcode_store[RET_T1_POS] = RET_T1;
    mcode_store[JMP_T1_POS] = JMP_T1;
    mcode_store[ALU_RESULT_POS] = ALU_RESULT;

    /* post processing */
    convert_active_lo(mcode_store, ROM_A_SPACE);
    convert_big_endian(mcode_store, ROM_A_SPACE);

    fwrite(mcode_store, sizeof(uint64_t), ROM_A_SPACE, stdout);

    return 0;
}

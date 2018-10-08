
#ifndef MCODE_H
#define MCODE_H

#include "ctrl_lines.h"

#define ACTV_LO   0
#define ACTV_HI   1

/** 
 * STEP ROM: ROMs containing next micro address data
 * CTRL ROM: ROMs containing control line data
 **/
#define ROM_A_SPACE     512
#define ROM_BIT_WIDTH   8
#define ROM_CNT         5
#define ROM_CTRL_CNT    4
#define ROM_STEP_CNT    ROM_CNT - ROM_CTRL_CNT
#define DATA_LN_CNT     ROM_CNT * ROM_BIT_WIDTH

#define SEL_OP  0xff    // inputs op-code as index to mcode
#define SEL_ENC 0x00    // op done, new machine cycle (pri-encoder as index)

#define EVAL(pos, val)  val << pos
#define REPEAT(val, n, start, arr)     for (int i = start; i < n+start; i++) arr[i] = val;

#define SP_D_CK         EVAL(_SP_D_CK,      1UL)
#define SP_U_CK         EVAL(_SP_U_CK,      1UL)
#define SP_P_CK         EVAL(_SP_P_CK,      1UL)
#define SP_A_EN         EVAL(_SP_A_CK,      1UL)
#define SP_L_EN         EVAL(_SP_L_CK,      1UL)
#define SP_H_EN         EVAL(_SP_H_CK,      1UL)
#define PC_CK           EVAL(_PC_CK,        1UL)
#define PC_P            EVAL(_PC_P,         1UL)
#define PC_A_EN         EVAL(_PC_A_EN,      1UL)
#define PC_L_EN         EVAL(_PC_L_EN,      1UL)
#define PC_H_EN         EVAL(_PC_H_EN,      1UL)
#define AR_CK           EVAL(_AR_CK,        1UL)
#define AR_OE           EVAL(_AR_OE,        1UL)
#define DECD_OE         EVAL(_DECD_OE,      1UL)
#define DECD_IE         EVAL(_DECD_IE,      1UL)
#define DECD_IMPLCT     EVAL(_DECD_IMPLCT,  1UL)
#define IR_CK           EVAL(_IR_CK,        1UL)
#define TMP_CK          EVAL(_TMP_CK,       1UL)
#define SH_R            EVAL(_SH_R,         1UL)
#define SH_EN           EVAL(_SH_EN,        1UL)
#define FLAG_CK         EVAL(_FLAG_CK,      1UL)
#define FLAG_D_OE       EVAL(_FLAG_D_OE,    1UL)
#define FLAG_D_IE       EVAL(_FLAG_D_IE,    1UL)
#define ALU_EN          EVAL(_ALU_EN,       1UL)
#define IO_MEM_IO       EVAL(_IO_MEM_IO,    1UL)
#define IO_MEM_WE       EVAL(_IO_MEM_WE,    1UL)
#define IO_MEM_D_CK     EVAL(_IO_MEM_D_CK,  1UL)
#define IO_MEM_RE       EVAL(_IO_MEM_RE,    1UL)
#define INT_SEI         EVAL(_INT_SEI,      1UL)
#define INT_CLI         EVAL(_INT_CLI,      1UL)
#define FLOW_HLT        EVAL(_FLOW_HLT,     1UL)
#define FLOW_BRA        EVAL(_FLOW_BRA,     1UL)

#define NEXT(val)   EVAL(0, val)
#define FETCH       PC_CK | PC_A_EN | IO_MEM_RE | IR_CK | NEXT(SEL_OP)
/**/
#define NOP         FETCH
/* REG-REG MOVS*/
#define MOV         DECD_IE | DECD_OE | NEXT(SEL_ENC)
/* REGULAR ALU OPS */
#define ALU_LD_TMP  TMP_CK | DECD_OE | NEXT(ALU_RESULT)
#define ALU_RESULT  DECD_IMPLCT | _ALU_EN | NEXT(SEL_ENC)

#endif


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

#define SEL_OP  0xff    /* inputs op-code as index to mcode */
#define SEL_ENC 0x00    /* op done, new machine cycle (pri-encoder as index) 
                            will fall through to either INT_POS, JMP_COND_POS
                            or FETCH_POS, depending on flags/IRQs */

#define EVAL(pos, val)  val << pos
#define NEXT(val)       EVAL(0, ((val) & 0xFF))
#define REPEAT(val, n, start, arr)  for (int i = start; i < n+start; i++) {arr[i] = val;}
#define AREA(val, cols, rows, start, arr)   for (int row = 0; row < rows; row++) \
                                                { REPEAT(val, cols, start+row*8, arr) }

/* LINE VALUES */
#define SP_D_CK         EVAL(_SP_D_CK,      1UL)
#define SP_U_CK         EVAL(_SP_U_CK,      1UL)
#define SP_P_CK         EVAL(_SP_P_CK,      1UL)
#define SP_A_EN         EVAL(_SP_A_EN,      1UL)
#define SP_L_EN         EVAL(_SP_L_EN,      1UL)
#define SP_H_EN         EVAL(_SP_H_EN,      1UL)
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
#define BRA_RST         EVAL(_BRA_RST,      1UL)
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

/* COMMON LINE COMBINATIONS */
#define READ_IMM    PC_CK | IO_MEM_RE | PC_A_EN
#define R0_IE       DECD_IMPLCT | DECD_IE
#define SP_PUSH_EN  SP_D_CK | SP_A_EN | IO_MEM_WE
#define SP_POP_EN   SP_U_CK | SP_A_EN | IO_MEM_RE
#define PC_LOAD     PC_CK | PC_P

/*** OPCODE VALUES ***/
#define NOP         0000
#define JMP_C_BASE  0010
#define CALL        0015
#define RET         0016
#define JMP         0017
#define LD_D8_BASE  0040
#define MOV_BASE    0100
#define ALU_DB_BASE 0202
#define SHFT_BASE   0304

/*** MICRO OP DEFINITIONS ***/
/** ADDRESSES OF SPECIAL MICRO OPS AND OPCODE T-STATE EXTENSIONS **/
#define INT_POS         0x000
#define BRANCH_HIT      0x106
#define BRANCH_MISS     0x10A
#define FETCH_POS       0x10F
#define PC_LOAD_AR_POS  FETCH_POS+1
#define CALL_T1_POS     PC_LOAD_AR_POS+1
#define RET_T1_POS      CALL_T1_POS+4
#define JMP_T1_POS      RET_T1_POS+1
#define ALU_RESULT_POS  JMP_T1_POS+1
/** MICRO CODE VALUES **/
/* HIDDEN */
#define FETCH       PC_CK | PC_A_EN | IO_MEM_RE | IR_CK | NEXT(SEL_OP)
/* FLOW */
#define PC_LOAD_AR  AR_OE | PC_LOAD      | NEXT(SEL_ENC)
#define CALL_T0     AR_CK | READ_IMM     | NEXT(CALL_T1_POS)
#define CALL_T1     AR_CK | READ_IMM     | NEXT(CALL_T1_POS+1)
#define CALL_T2     SP_PUSH_EN | PC_H_EN | NEXT(CALL_T1_POS+2)
#define CALL_T3     SP_PUSH_EN | PC_L_EN | NEXT(PC_LOAD_AR_POS)
#define RET_T0      AR_CK | SP_POP_EN | NEXT(RET_T1_POS)
#define RET_T1      AR_CK | SP_POP_EN | NEXT(PC_LOAD_AR_POS)
#define JMP_T0      AR_CK | READ_IMM | NEXT(JMP_T1_POS)
#define JMP_T1      AR_CK | READ_IMM | BRA_RST | NEXT(PC_LOAD_AR_POS)
#define JMP_COND    FLOW_BRA | NEXT(SEL_ENC)
#define BRA_MISS_0  PC_CK | NEXT(BRANCH_MISS + 1)
#define BRA_MISS_1  PC_CK | BRA_RST | NEXT(SEL_ENC)
/* LOAD/STORE */
#define LD_D8       DECD_IE | READ_IMM | NEXT(SEL_ENC)
/* REG-REG MOVS */
#define MOV         DECD_IE | DECD_OE | NEXT(SEL_ENC)
/* ARITHMETIC AND LOGIC */
#define ALU_LD_TMP  TMP_CK | DECD_OE | NEXT(ALU_RESULT_POS)
#define ALU_RESULT  R0_IE | FLAG_CK | ALU_EN | NEXT(SEL_ENC)
#define SHFT        R0_IE | DECD_OE | SH_EN | NEXT(SEL_ENC)

#endif

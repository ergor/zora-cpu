
#include <stdint.h>

#define ACTV_LO   0
#define ACTV_HI   1


#define TEST 1,2,3


/** 
 * STEP ROM: ROMs containing next micro address data
 * CTRL ROM: ROMs containing control line data
 **/
#define ROM_BIT_WIDTH   8
#define ROM_CNT         5
#define ROM_CTRL_CNT    4
#define ROM_STEP_CNT    ROM_CNT - ROM_CTRL_CNT
#define DATA_LN_CNT     ROM_CNT * ROM_BIT_WIDTH

#define STEP_BASE   0x0
#define CTRL_BASE   ROM_STEP_CNT * ROM_BIT_WIDTH


#define SP_BASE     CTRL_BASE
#define SP_LEN      6
#define SP_D_CK     0x0
#define SP_U_CK     0x1
#define SP_P_CK     0x2
#define SP_A_EN     0x3
#define SP_L_EN     0x4
#define SP_H_EN     0x5
#define SP_POL      ACTV_LO, ACTV_LO, ACTV_LO, ACTV_LO, ACTV_LO, ACTV_LO

#define PC_BASE     SP_BASE + SP_LEN
#define PC_LEN      5
#define PC_CK       0x0
#define PC_P        0x1
#define PC_Ae       0x2
#define PC_Le       0x3
#define PC_He       0x4
#define PC_POL      ACTV_HI, ACTV_LO, ACTV_LO, ACTV_LO, ACTV_LO

#define AR_BASE     PC_BASE + PC_LEN
#define AR_LEN      2
#define AR_CK       0x0
#define AR_OE       0x1
#define AR_POL      ACTV_HI, ACTV_LO

#define DECD_BASE   AR_BASE + AR_LEN
#define DECD_LEN    3
#define DECD_OE     0x0
#define DECD_IE     0x1
#define DECD_IMPLCT 0x2
#define DECD_POL    ACTV_HI, ACTV_HI, ACTV_LO

#define IR_BASE     DECD_BASE + DECD_LEN
#define IR_LEN      1
#define IR_CK       0x0
#define IR_POL      ACTV_HI

#define TMP_BASE    IR_BASE + IR_LEN
#define TMP_LEN     1
#define TMP_CK      0x0
#define TMP_POL     ACTV_HI

#define SH_BASE     TMP_BASE + TMP_LEN
#define SH_LEN      2
#define SH_R        0x0
#define SH_EN       0x1
#define SH_POL      ACTV_HI, ACTV_HI

#define FLAG_BASE   SH_BASE + SH_LEN
#define FLAG_LEN    3
#define FLAG_CK     0x0
#define FLAG_D_OE   0x1
#define FLAG_D_IE   0x2
#define FLAG_POL    ACTV_HI, ACTV_LO, ACTV_LO

#define ALU_BASE    FLAG_BASE + FLAG_LEN
#define ALU_LEN     1
#define ALU_EN      0x0
#define ALU_POL     ACTV_LO

#define IO_MEM_BASE ALU_BASE + ALU_LEN
#define IO_MEM_LEN  4
#define IO_MEM_IO   0x0
#define IO_MEM_WE   0x1
#define IO_MEM_D_CK 0x2
#define IO_MEM_RE   0x3
#define IO_MEM_POL  ACTV_LO, ACTV_HI, ACTV_HI, ACTV_HI

#define INT_BASE    IO_MEM_BASE + IO_MEM_LEN
#define INT_LEN     2
#define INT_SEI     0x0
#define INT_CLI     0x1
#define INT_POL     ACTV_LO, ACTV_LO

#define FLOW_BASE   INT_BASE + INT_LEN
#define FLOW_LEN    2
#define FLOW_HLT    0x0
#define FLOW_BRA    0x1
#define FLOW_POL    ACTV_LO, ACTV_LO

uint8_t pols[DATA_LN_CNT] = { SP_POL, PC_POL, AR_POL, DECD_POL };



// def OP1 OP(next, lines,)
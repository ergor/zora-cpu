
#ifndef CTRL_LINES_H
#define CTRL_LINES_H

#define _NEXT_0     0UL
#define _NEXT_1     1UL
#define _NEXT_2     2UL
#define _NEXT_3     3UL
#define _NEXT_4     4UL
#define _NEXT_5     5UL
#define _NEXT_6     6UL
#define _NEXT_7     7UL

#define _SP_D_CK     8UL
#define _SP_U_CK     9UL
#define _SP_P_CK     10UL
#define _SP_A_EN     11UL
#define _SP_L_EN     12UL
#define _SP_H_EN     13UL

#define _PC_CK       14UL
#define _PC_P        15UL
#define _PC_A_EN     16UL
#define _PC_L_EN     17UL
#define _PC_H_EN     18UL

#define _AR_CK       19UL
#define _AR_OE       20UL

#define _DECD_OE     21UL
#define _DECD_IE     22UL
#define _DECD_IMPLCT 23UL

#define _IR_CK       24UL

#define _TMP_CK      25UL

#define _BRA_RST     26UL

#define _SH_EN       27UL

#define _FLAG_CK     28UL
#define _FLAG_D_OE   29UL
#define _FLAG_D_IE   30UL

#define _ALU_EN      31UL

#define _IO_MEM_IO   32UL
#define _IO_MEM_WE   33UL
#define _IO_MEM_D_CK 34UL
#define _IO_MEM_RE   35UL

#define _INT_SEI     36UL
#define _INT_CLI     37UL

#define _FLOW_HLT    38UL
#define _FLOW_BRA    39UL

#define ACTV_HIS    _PC_CK, _AR_CK, _DECD_IE, _DECD_OE, _IR_CK, _TMP_CK, \
                    _FLAG_CK, _IO_MEM_D_CK, _IO_MEM_RE, _IO_MEM_WE, \
                    _NEXT_0, _NEXT_1, _NEXT_2, _NEXT_3, _NEXT_4, _NEXT_5, _NEXT_6, _NEXT_7


#endif


// def OP1 OP(next, lines,)

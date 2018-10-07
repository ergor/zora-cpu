
ACT_LO = 0
ACT_HI = 1

# use this until ordered dicts are in the spec (py ver >= 3.7)
line_grps = [
    {
        "SP_D_CK": (0x0, ACT_LO),
        "SP_U_CK": (0x1, ACT_LO),
        "SP_P_CK": (0x2, ACT_LO),
        "SP_A_EN": (0x3, ACT_LO),
        "SP_L_EN": (0x4, ACT_LO),
        "SP_H_EN": (0x5, ACT_LO),
    },
    {
        "PC_CK": (0x0, ACT_HI),
        "PC_P":  (0x1, ACT_LO),
        "PC_Ae": (0x2, ACT_LO),
        "PC_Le": (0x3, ACT_LO),
        "PC_He": (0x4, ACT_LO),
    },
    {
        "AR_CK": (0x0, ACT_HI),
        "AR_OE": (0x1, ACT_LO),
    },
    {
        "DECD_OE":     (0x0, ACT_HI),
        "DECD_IE":     (0x1, ACT_HI),
        "DECD_IMPLCT": (0x2, ACT_LO),
    }
]

def ln(tpl):
    return tpl[0]
def pol(tpl):
    return tpl[1]

def cmpile(lst):
    compiled = {}
    offset = 0
    for d in lst:
        new = {}
        for key, val in d.items():
            new[key] = (ln(val) + offset, pol(val))
        offset += len(d)
        compiled.update(new)
    return compiled
         
def main():
    
    print(cmpile(line_grps))
    #print(line_grps)

main()


import re

# MOV r0, r1

def src_parser():
    pass

REGS = {
    "r0" : 0,
    "r1" : 1,
    "r2" : 2,
    "r3" : 3,
    "r4" : 4,
    "r5" : 5,
    "r6" : 6,
    "r7" : 7,
}

ARG = {
    # "name" : (shift_amount, parser)
    "src" : (3, REGS),
    "dst" : (0, REGS),
    "alu" : 0,
    "cnd" : 0,
}

OPS = {
    # "name" : (opval, arg_regex, (arg_type (in order),))
    "MOV" : (0o100, r"([rR][0-7])\s*,\s*([rR][0-7])", ("src", "dst"))
}

# val(MOV) = OPS("MOV") + REGS(rs)<<3 + REGS(rd)


def main():
    line = input()
    line = line.split(None, 1)

    op = line[0]
    args = line[1]
    print(op)
    print(args)

    m = re.search(OPS[op][1], args)
    if m is None:
        print(op + ": invalid operand format")
        exit(1)
    print(m.groups())

    opval = OPS[op][0]
    for arg, typ in zip(m.groups(), OPS[op][2]):
        opval += ARG[typ][1][arg] << ARG[typ][0]
        print("arg: " + str(arg) + ", typ: " + typ)
    print(opval)


main()

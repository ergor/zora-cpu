
import sys
import string

keywords_defs = ["lines", "clocks", "meta", "define", "instructions"]


def contains_whitespace(s):
    return True in [c in s for c in string.whitespace]

def splitBlocks(code):
    for c in code:
        if (not contains_whitespace(c)):
            print(c)


## BEGIN PROGRAM ##
if len(sys.argv) < 2:
    print("usage: python microasm.py inputfile")
    exit()

code = open(str(sys.argv[1]), "r").read()
splitBlocks(code)


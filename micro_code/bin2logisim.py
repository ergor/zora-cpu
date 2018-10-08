
### Script to generate logisim ROM images from microcode binaries ###
# assumes the binary file is big endian uint64's
# --------------

import sys

def main():
    if len(sys.argv) < 2:
        print("please specify microcode binary file")
        exit(1)
    if len(sys.argv) < 3:
        print("please select ROM bank to print out")
        exit(1)

    with open(sys.argv[1], "rb") as fin:
        mcode = fin.read()
        banks = [mcode[i::8] for i in range(8)]
        banks.reverse() # big endian means MSB is in [0]; reverse it
        bank = banks[int(sys.argv[2])]

        print("v2.0 raw")
        byte_lst = [bank[i:i+1] for i in range(len(bank))]
        for byte in byte_lst:
            print(byte.hex())

main()

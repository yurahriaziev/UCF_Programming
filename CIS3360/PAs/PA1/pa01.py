# *============================================================================
# | Assignment: pa01 - Calculate the checksum of an input file given:
# | -> the name of the input file,
# | -> the checksum size of either 8, 16, or 32 bits
# | Author: Yurii Hriaziev
# | Language: Python
# | To Compile: javac pa01.java
# | gcc -o pa01 pa01.c
# | g++ -o pa01 pa01.cpp
# | go build pa01.go
# | rustc pa01.rs
# | To Execute: java -> java pa01 inputFilename.txt checksumSize
# | or c++ -> ./pa01 inputFilename.txt checksumSize
# | or c -> ./pa01 inputFilename.txt checksumSize
# | or go -> ./pa01 inputFilename.txt checksumSize
# | or rust -> ./pa01 inputFilename.txt checksumSize
# | or python -> python3 pa01.py inputFilename.txt checksumSize
# | where inputFilename.txt is the input file
# | and checksumSize is either 8, 16, or 32
# | Note:
# | All input files are simple 8 bit ASCII input
# | All execute commands above have been tested on Eustis
# | Class: CIS3360 - Security in Computing - Spring 2026
# | Instructor: McAlpin
# | Due Date: 02/15/2026 11:59PM
# +===========================================================================*

import sys

def error_on_invalid_size() -> None:
    print("Valid checksum sizes are 8, 16, or 32", file=sys.stderr)
    sys.exit(1)

def pad_data(data: bytearray, checksum_size: int) -> None:
    if checksum_size == 16:
        while len(data) % 2 != 0:
            data.append(0x58)
    elif checksum_size == 32:
        while len(data) % 4 != 0:
            data.append(0x58)

def get_checksum(data: bytearray, checksum_size: int) -> int:
    checksum = 0

    if checksum_size == 8:
        for byte in data:
            checksum += byte
        checksum &= 0xff
    elif checksum_size == 16:
        for i in range(0, len(data), 2):
            word = int.from_bytes(data[i:i+2], 'big')
            checksum += word
        checksum &= 0xFFFF
    elif checksum_size == 32:
        for i in range(0, len(data), 4):
            word = int.from_bytes(data[i:i+4], 'big')
            checksum += word
        checksum &= 0xFFFFFFFF
    else:
        error_on_invalid_size()

    return checksum

def print_80_output(data: bytearray) -> None:
    col = 0
    out = sys.stdout.buffer

    for byte in data:
        out.write(bytes([byte]))

        if byte == 0x0A:
            col = 0
        else:
            col += 1
            if col == 80:
                out.write(b"\n")
                col=0

def main() -> None:
    if len(sys.argv) != 3:
        print('Bad input, try again!')
        sys.exit(1)

    input_filename = sys.argv[1]

    try:
        checksum_size = int(sys.argv[2])
    except ValueError:
        error_on_invalid_size()

    if checksum_size not in (8, 16, 32):
        error_on_invalid_size()

    try:
        with open(input_filename, 'rb') as f:
            data = bytearray(f.read())
    except OSError as e:
        print(f'Error opening file: {e}', file=sys.stderr)
        sys.exit(1)

    pad_data(data, checksum_size)
    character_count = len(data)
    sys.stdout.buffer.write(b"\n")
    print_80_output(data)
    print()
    checksum = get_checksum(data, checksum_size)

    print(f'{checksum_size:2d} bit checksum is {checksum:8x} for all {character_count:4d} chars')

if __name__ == "__main__":
    main()

# *=============================================================================
# | I Yurii Hriaziev 290201 affirm that this program is
# | entirely my own work and that I have neither developed my code together with
# | any another person, nor copied any code from any other person, nor permitted
# | my code to be copied or otherwise used by any other person, nor have I
# | copied, modified, or otherwise used programs created by others. I acknowledge
# | that any violation of the above terms will be treated as academic dishonesty.
# +=============================================================================*
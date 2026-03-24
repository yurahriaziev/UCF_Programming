# *============================================================================
# | Assignment: pa02 - Encrypting a plaintext file using the Hill cipher
# |
# | Author: Yurii Hriaziev
# | Language: Python
# | To Compile: javac pa02.java
# | gcc -o pa02 pa02.c
# | g++ -o pa02 pa02.cpp
# | go build pa02.go
# | rustc pa02.rs
# | To Execute: java -> java pa02 kX.txt pX.txt
# | or c++ -> ./pa02 kX.txt pX.txt
# | or c -> ./pa02 kX.txt pX.txt
# | or go -> ./pa02 kX.txt pX.txt
# | or rust -> ./pa02 kX.txt pX.txt
# | or python -> python3 pa02.py kX.txt pX.txt <----
# | where kX.txt is the keytext file
# | and pX.txt is plaintext file
# | Note:
# | All input files are simple 8 bit ASCII input
# | All execute commands above have been tested on Eustis
# | Class: CIS3360 - Security in Computing - Spring 2026
# | Instructor: McAlpin
# | Due Date: 03/15/2026 11:59PM
# +===========================================================================*

import sys

def read_key_matrix(filename):
    with open(filename) as f:
        n = int(f.readline().strip())
        matrix = []

        for _ in range(n):
            row = list(map(int, f.readline().split()))
            matrix.append(row)

    return matrix, n

def read_plaintext(filename):
    letters = []

    with open(filename) as f:
        for line in f:
            for c in line:
                if c.isalpha():
                    letters.append(c.lower())

    return "".join(letters)

def pad_plaintext(text, n):
    while len(text) % n != 0:
        text += "x"

    return text

def encrypt(plaintext, key, n):
    cipertext = []

    for i in range(0, len(plaintext), n):
        block = plaintext[i:i+n]
        vector = [ord(c) - ord('a') for c in block]

        for j in range(n):
            value = 0
            for k in range(n):
                value += key[j][k] * vector[k]

            value %= 26
            cipertext.append(chr(value + ord('a')))

    return "".join(cipertext)

def print80(text):
    for i in range(0, len(text), 80):
        print(text[i:i+80])

def main():
    if len(sys.argv) != 3:
        sys.exit(1)

    key_file = sys.argv[1]
    plaintext_file = sys.argv[2]

    matrix, n = read_key_matrix(key_file)

    plaintext = read_plaintext(plaintext_file)
    plaintext = pad_plaintext(plaintext, n)

    ciphertext = encrypt(plaintext, matrix, n)

    print("\nKey matrix:")
    for row in matrix:
        for num in row:
            print(f"{num:4d}", end="")
        print()

    print("\nPlaintext:")
    print80(plaintext)

    print("\nCiphertext:")
    print80(ciphertext)

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
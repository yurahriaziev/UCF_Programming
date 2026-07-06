#!/bin/bash

javac Main.java

for folder in 2 4 6 25
do
    for infile in $folder/*.in
    do
        outfile="${infile%.in}.out"
        temp="my_output.txt"

        java Main < "$infile" > "$temp"

        if diff -q "$temp" "$outfile" > /dev/null
        then
            echo "PASS: $infile"
        else
            echo "FAIL: $infile"
            echo "Expected:"
            cat "$outfile"
            echo "Got:"
            cat "$temp"
            echo
        fi
    done
done

rm -f my_output.txt
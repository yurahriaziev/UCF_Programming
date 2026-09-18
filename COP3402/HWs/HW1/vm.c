/*
Assignment:
vm - HW1 PM/0 virtual machine
Author: Yurii Hriaziev
Language: C only
To Compile:
    gcc -Wall -Wextra -std=c11 -O2 vm.c -o vm
To Execute (on Eustis):
    ./vm <input_file>
where:
    <input_file> is the path to a text file holding one PM/0 instruction
                per line, as three integers OP L M
Notes:
    - Implements the PM/0 virtual machine described in the homework
    instructions.
    - No heap allocation and no function-like macros. The PAS array is
    indexed, not walked with a pointer.
    - Does not implement any VM instruction as a separate function; the
    fetch-execute cycle runs directly in main.
    - Defines at most three functions: main, base, and one print function.
    - Exits with status 0 after a normal halt and with a non-zero status
    after any error.
    - Tested on Eustis.
Class: COP 3402 - Systems Software
Instructor: Jie Lin, Ph.D.
Due Date: See Webcourses
*/

#include <stdio.h>

// initializing the memory for the machine
    static int pas[1000]; // pas -> Process Address Space

int base(int bp, int L) {
    int arb = bp;
    while (L > 0) {
        arb = pas[arb];
        L--;
    }
    return arb;
}

void print_output(int OP, int L, int M, int PC, int BP, int SP) {
    switch (OP) {
        case 1:
            printf("LIT\t");
            break;

        case 2:
            switch (M) {
                case 0:
                    printf("RTN\t");
                    break;
                case 1:
                    printf("ADD\t");
                    break;
                case 2:
                    printf("SUB\t");
                    break;
                case 3:
                    printf("MUL\t");
                    break;
                case 4:
                    printf("DIV\t");
                    break;
                case 5:
                    printf("EQL\t");
                    break;
                case 6:
                    printf("NEQ\t");
                    break;
                case 7:
                    printf("LSS\t");
                    break;
                case 8:
                    printf("LEQ\t");
                    break;
                case 9:
                    printf("GTR\t");
                    break;
                case 10:
                    printf("GEQ\t");
                    break;
            }
            break;

        case 3:
            printf("LOD\t");
            break;

        case 4:
            printf("STO\t");
            break;

        case 5:
            printf("CAL\t");
            break;

        case 6:
            printf("INC\t");
            break;

        case 7:
            printf("JMP\t");
            break;

        case 8:
            printf("JPC\t");
            break;

        case 9:
            printf("SYS\t");
            break;
    }

    printf("%d\t%d\t%d\t%d\t%d\t", L, M, PC, BP, SP);

    int bases[1000];
    int count = 0;
    int cur = BP;

    while (cur != 999) {
        bases[count] = cur;
        count++;

        cur = pas[cur - 1];
    }

    int bar_index = count - 1;

    for (int i=999; i>=SP; i--) {
        if (bar_index >= 0 && i == bases[bar_index]) {
            printf("| ");
            bar_index--;
        }

        printf("%d ", pas[i]);
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./vm <input file>\n");
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        printf("Error: cannot open %s\n", argv[1]);
        return 1;
    }

    int mem_index_start = 200;

    int OP, L, M;
    int PC = 200;
    int SP = 1000;
    int BP = 999;

    // while loop to scan instructions until the amount of instructions does not equal 3 -> OP, L, M
    while (fscanf(input_file, "%d %d %d", &OP, &L, &M) == 3) {
        if (mem_index_start + 2 > 999) {
            printf("\nError: program too large for the text segment\n");
            fclose(input_file);
            return 1;
        }

        pas[mem_index_start] = OP;
        pas[mem_index_start+1] = L;
        pas[mem_index_start+2] = M;

        mem_index_start += 3;
    }

    fclose(input_file);
    int last_code_address = mem_index_start - 1;

    int run = 1;
    while (run == 1) {
        if (PC < 200 || PC + 2 > last_code_address) {
            printf("\nError: program counter left the text segment\n");
            return 1;
        }
        OP = pas[PC];
        L = pas[PC+1];
        M = pas[PC+2];

        PC += 3;

        switch(OP) {
            case 1:
                if (SP - 1 <= last_code_address) {
                    printf("\nError: stack overflow\n");
                    return 1;   
                }

                SP -= 1;
                pas[SP] = M;
                break;
            case 2:
                switch(M) {
                    case 0:
                        SP = BP + 1;
                        BP = pas[SP-2];
                        PC = pas[SP-3];
                        break;
                    case 1:
                        pas[SP+1] = pas[SP+1] + pas[SP];
                        SP += 1;
                        break;
                    case 2:
                        pas[SP+1] = pas[SP+1] - pas[SP];
                        SP += 1;
                        break;
                    case 3:
                        pas[SP+1] = pas[SP+1] * pas[SP];
                        SP += 1;
                        break;
                    case 4:
                        if (pas[SP] == 0) {
                            printf("\nError: division by zero\n");
                            return 1;
                        }

                        pas[SP+1] = pas[SP+1] / pas[SP];
                        SP += 1;
                        break;
                    case 5:
                        if (pas[SP+1] == pas[SP]) {
                            pas[SP+1] = 1;
                        } else {
                            pas[SP+1] = 0;
                        }

                        SP += 1;
                        break;
                    case 6:
                        if (pas[SP+1] != pas[SP]) {
                            pas[SP+1] = 1;
                        } else {
                            pas[SP+1] = 0;
                        }

                        SP += 1;
                        break;
                    case 7:
                        if (pas[SP+1] < pas[SP]) {
                            pas[SP+1] = 1;
                        } else {
                            pas[SP+1] = 0;
                        }

                        SP += 1;
                        break;
                    case 8:
                        if (pas[SP+1] <= pas[SP]) {
                            pas[SP+1] = 1;
                        } else {
                            pas[SP+1] = 0;
                        }

                        SP += 1;
                        break;
                    case 9:
                        if (pas[SP+1] > pas[SP]) {
                            pas[SP+1] = 1;
                        } else {
                            pas[SP+1] = 0;
                        }

                        SP += 1;
                        break;
                    case 10:
                        if (pas[SP+1] >= pas[SP]) {
                            pas[SP+1] = 1;
                        } else {
                            pas[SP+1] = 0;
                        }

                        SP += 1;
                        break;
                    default:
                        printf("\nError: unknown OPR sub-operation\n");
                        return 1;
                }
                break;
                case 3: {
                    int address = base(BP, L) - M;
                    if (address <= last_code_address || address > 999) {
                        printf("\nError: data address out of range\n");
                        return 1;
                    }

                    if (SP - 1 <= last_code_address) {
                        printf("\nError: stack overflow\n");
                        return 1;   
                    }

                    SP-=1;
                    pas[SP] = pas[address];
                    break;
                }
                case 4: {
                    int address = base(BP, L) - M;
                    if (address <= last_code_address || address > 999) {
                        printf("\nError: data address out of range\n");
                        return 1;
                    }

                    pas[address] = pas[SP];
                    SP+=1;
                    break;
                }
                case 5:
                    pas[SP-1] = base(BP, L);
                    pas[SP-2] = BP;
                    pas[SP-3] = PC;
                    BP = SP - 1;
                    PC = M;
                    break;
                case 6:
                    if (SP - M <= last_code_address) {
                        printf("\nError: stack overflow\n");
                        return 1;   
                    }
                    SP -= M;
                    break;
                case 7:
                    PC = M;
                    break;
                case 8:
                    if (pas[SP] == 0) {
                        PC = M;
                    }
                    SP+=1;
                    break;
                case 9:
                    switch (M) {
                        case 1:
                            printf("Output result is: %d\n", pas[SP]);
                            SP+=1;
                            break;
                        case 2: {
                            int a;
                            if (SP - 1 <= last_code_address) {
                                printf("\nError: stack overflow\n");
                                return 1;   
                            }
                            
                            printf("Please Enter an Integer: ");
                            scanf("%d", &a);
                            printf("%d\n", a);
                            SP-=1;
                            pas[SP] = a;
                            break;
                        }
                        case 3:
                            run = 0;
                            break;
                        default:
                            printf("\nError: unknown SYS operation\n");
                            return 1;
                    }
                    break;
                default:
                    printf("\nError: unknown opcode\n");
                    return 1;
        }
    }
}
/*
Homework:
lex - HW2 PL/0 lexical analyzer

Author(s): Yurii Hriaziev

Language: C only

To Compile:
  gcc -Wall -Wextra -std=c11 -O2 lex.c -o lex

To Execute (on Eustis):
  ./lex <input_file>

where:
  <input_file> is the path to a text file holding a PL/0 source program

Notes:
  - Implements the lexical analyzer described in the homework
    instructions.
  - Prints four sections to standard output: Source Program, Lexeme
    Table, Name Table and Token List.
  - Writes two files into the working directory: tokens.txt and
    nametable.txt.
  - Stops at the first lexical error, prints everything scanned before
    it, reports the error with its line and column, and exits with a
    non-zero status.
  - Exits with status 0 when the whole program scans without an error.
  - Tested on Eustis.

Class: COP 3402 - Systems Software

Instructor: Jie Lin, Ph.D.

Due Date: See Webcourses
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// some helper functions for words and numbers
int is_letter(int c) {
    if ((c >= 'A' && c <='Z') || (c >= 'a' && c <= 'z')) {
        return 1;
    }
    return 0;
}
int is_digit(int c) {
    if (c >= '0' && c <= '9') {
        return 1;
    }
    return 0;
}
int reserved_word(char *word) {
    char *reserved_words[] = {
        "begin", "end", "if", "fi", "then", "while", "elihw", "do", "od", "odd",
        "call", "const", "var", "procedure", "write", "read", "else"
    };
    
    for (int i=0; i<17; i++) {
        if (strcmp(word, reserved_words[i]) == 0) {
            return 20 + i;
        }
    }

    return 1;
}

// struct NameTableRow to store a unique identifier
struct NameTableRow {
    char name[13];
    int line;
    int column;
};

// struct Token to store a token and print it later
struct Token {
    int code;
    size_t name_index;
    char number[7];
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./lex <input file>\n");
        return 1;
    }

    FILE *input_file = fopen(argv[1], "rb");

    if (input_file == NULL) {
        printf("Error: unable to open input file '%s'\n", argv[1]);
        return 1;
    }

    printf("Source Program:\n\n");

    int cur_char;
    int last_char = '\n';
    size_t source_length = 0;

    cur_char = fgetc(input_file);
    while (cur_char != EOF) {
        printf("%c", cur_char);
        last_char = cur_char;
        cur_char = fgetc(input_file);
        source_length += 1;
    }

    if (last_char != '\n') {
        printf("\n");
    }

    printf("\n");

    rewind(input_file);
    char *lexeme = malloc(source_length + 1);
    if (lexeme == NULL) {
        printf("Memory allocation for 'lexeme' failed\n");
        fclose(input_file);
        return 1;
    }
    struct NameTableRow *names = malloc((source_length + 1) * sizeof(struct NameTableRow));
    if (names == NULL) {
        printf("Memory allocation for 'names' failed\n");
        free(lexeme);
        fclose(input_file);
        return 1;
    }
    struct Token *tokens = malloc((source_length + 1) * sizeof(struct Token));
    if (tokens == NULL) {
        printf("Memory allocation for 'tokens' failed\n");
        free(lexeme);
        free(names);
        fclose(input_file);
        return 1;
    }
    
    size_t token_count = 0;
    size_t name_count = 0;
    int line = 1;
    int column = 1;

    printf("Lexeme Table:\n\n");
    printf("lexeme\ttoken\n");

    int token;
    int error = 0;
    int error_line = 1;
    int error_column = 1;

    cur_char = fgetc(input_file);
    while (cur_char != EOF) {
        if (cur_char == ' ' || cur_char == '\t') {
            column += 1;
        } else if (cur_char == '\n') {
            line += 1;
            column = 1;
        } else if (cur_char == '\r') {
            // do nothing per instructions
        } else if (is_letter(cur_char)) {
            size_t len = 0;

            error_line = line;
            error_column = column;
            while (is_letter(cur_char) || is_digit(cur_char)) {
                lexeme[len] = cur_char;
                len += 1;
                column += 1;

                cur_char = fgetc(input_file);
            }
            lexeme[len] = '\0';

            if (len > 12) {
                error = 2;
                break;
            }

            token = reserved_word(lexeme);
            tokens[token_count].code = token;
            if (token == 1) {
                size_t index = 0;

                while (index < name_count) {
                    if (strcmp(lexeme, names[index].name) == 0) {
                        break;
                    }

                    index += 1;
                }

                if (index == name_count) {
                    strcpy(names[index].name, lexeme);
                    names[index].line = error_line;
                    names[index].column = error_column;
                    name_count += 1;
                }
                tokens[token_count].name_index = index;
            }
            token_count += 1;
            
            printf("%s\t%d\n", lexeme, token);
            continue;
        } else if (is_digit(cur_char)) {
            size_t len = 0;

            error_line = line;
            error_column = column;

            while (is_digit(cur_char)) {
                lexeme[len] = cur_char;
                len += 1;
                column += 1;
                cur_char = fgetc(input_file);
            }

            if (is_letter(cur_char)) {
                while (is_letter(cur_char) || is_digit(cur_char)) {
                    lexeme[len] = cur_char;
                    len += 1;
                    column += 1;
                    cur_char = fgetc(input_file);
                }

                lexeme[len] = '\0';
                error = 6;
                break;
            }

            lexeme[len] = '\0';
            if (len > 6) {
                error = 3;
                break;
            }

            token = 2;

            tokens[token_count].code = token;
            strcpy(tokens[token_count].number, lexeme);
            token_count += 1;
            printf("%s\t%d\n", lexeme, token);
            continue;
        } else {
            token = 0;
            int second_char = 0;
            int skipped_comment = 0;
            error_line = line;
            error_column = column;

            switch (cur_char) {
                case '+':
                    token = 3;
                    break;
                case '-':
                    token = 4;
                    break;
                case '(':
                    token = 13;
                    break;
                case ')':
                    token = 14;
                    break;
                case ',':
                    token = 15;
                    break;
                case ';':
                    token = 16;
                    break;
                case '.':
                    token = 17;
                    break;
                case '=': {
                    int next_char = fgetc(input_file);
                    if (next_char == '=') {
                        token = 7;
                        second_char = '=';
                        column += 1;
                    } else {
                        token = 18;
                        if (next_char != EOF) {
                            ungetc(next_char, input_file);
                        }
                    }
                    break;
                }
                case '<': {
                    int next_char = fgetc(input_file);
                    if (next_char == '=') {
                        token = 10;
                        second_char = '=';
                        column += 1;
                    } else {
                        token = 9;
                        if (next_char != EOF) {
                            ungetc(next_char, input_file);
                        }
                    }
                    break;
                }
                case '>': {
                    int next_char = fgetc(input_file);
                    if (next_char == '=') {
                        token = 12;
                        second_char = '=';
                        column += 1;
                    } else {
                        token = 11;
                        if (next_char != EOF) {
                            ungetc(next_char, input_file);
                        }
                    }
                    break;
                }
                case '!': {
                    int next_char = fgetc(input_file);
                    if (next_char == '=') {
                        token = 8;
                        second_char = '=';
                        column += 1;
                    } else {
                        error = 5;
                        if (next_char != EOF) {
                            ungetc(next_char, input_file);
                        }
                    }
                    break;
                }
                case '*': {
                    int next_char = fgetc(input_file);
                    if (next_char == '/') {
                        error = 8;
                    } else {
                        token = 5;
                        if (next_char != EOF) {
                            ungetc(next_char, input_file);
                        }
                    }
                    break;
                }
                case ':': {
                    int next_char = fgetc(input_file);
                    if (next_char == '=') {
                        token = 19;
                        second_char = '=';
                        column += 1;
                    } else {
                        error = 4;
                        if (next_char != EOF) {
                            ungetc(next_char, input_file);
                        }
                    }
                    break;
                }
                case '/': {
                    int next_char = fgetc(input_file);
                    if (next_char == '*') {
                        int comment_line = line;
                        int comment_column = column;
                        int closed = 0;

                        column += 2;
                        cur_char = fgetc(input_file);
                        while (cur_char != EOF) {
                            if (cur_char == '*' || cur_char == '/') {
                                next_char = fgetc(input_file);

                                if (cur_char == '*' && next_char == '/') {
                                    column += 2;
                                    closed = 1;
                                    break;
                                }

                                if (cur_char == '/' && next_char == '*') {
                                    error = 9;
                                    error_line = line;
                                    error_column = column;
                                    break;
                                }

                                if (next_char != EOF) {
                                    ungetc(next_char, input_file);
                                }
                            }
                            if (cur_char == '\n') {
                                line += 1;
                                column = 1;
                            } else if (cur_char != '\r') {
                                column += 1;
                            }

                            cur_char = fgetc(input_file);
                        }

                        if (closed == 0 && error == 0) {
                            error = 7;
                            error_line = comment_line;
                            error_column = comment_column;
                        }
                        skipped_comment = 1;
                    } else {
                        token = 6;
                        if (next_char != EOF) {
                            ungetc(next_char, input_file);
                        }
                    }
                    break;
                }
                default:
                    if (cur_char >= 0x20 && cur_char <= 0x7E) {
                        error = 1;
                    } else {
                        error = 10;
                    }
                    break;
            }

            if (error != 0) {
                break;
            }
            if (skipped_comment == 1) {
                cur_char = fgetc(input_file);
                continue;
            }

            if (token == 0) {
                break;
            }

            tokens[token_count].code = token;
            token_count += 1;

            printf("%c", cur_char);
            if (second_char != 0) {
                printf("%c", second_char);
            }
            printf("\t%d\n", token);
            column += 1;
        }

        cur_char = fgetc(input_file);
    }

    if (error == 0 && token_count == 0) {
        error = 11;
        error_line = 1;
        error_column = 1;
    }

    // printing the name table
    printf("\nName Table:\n\n");
    printf("index\tname\tline\tcolumn\n");

    for (size_t i=0; i<name_count; i++) {
        printf("%zu\t%s\t%d\t%d\n", i, names[i].name, names[i].line, names[i].column);
    }

    // printing the token list
    printf("\nToken List:\n\n");

    for (size_t i=0; i<token_count; i++) {
        printf("%d", tokens[i].code);

        if (tokens[i].code == 1) {
            printf(" %zu", tokens[i].name_index);
        } else if (tokens[i].code == 2) {
            printf(" %s", tokens[i].number);
        }
        printf(" ");
    }
    printf("\n");

    // writing to tokens.txt and nametable.txt
    FILE *tokens_file = fopen("tokens.txt", "w");
    if (tokens_file == NULL) {
        printf("Failed to create 'tokens.txt' file\n");
        free(names);
        free(tokens);
        free(lexeme);
        fclose(input_file);
        return 1;
    }

    FILE *nametable_file = fopen("nametable.txt", "w");
    if (nametable_file == NULL) {
        printf("Failed to create 'nametable.txt' file\n");
        fclose(tokens_file);
        free(names);
        free(tokens);
        free(lexeme);
        fclose(input_file);
        return 1;
    }

    for (size_t i=0; i<token_count; i++) {
        fprintf(tokens_file, "%d", tokens[i].code);

        if (tokens[i].code == 1) {
            fprintf(tokens_file, " %zu", tokens[i].name_index);
        } else if (tokens[i].code == 2) {
            fprintf(tokens_file, " %s", tokens[i].number);
        }
        fprintf(tokens_file, "\n");
    }

    for (size_t i=0; i<name_count; i++) {
        fprintf(nametable_file, "%zu %s %d %d\n", i, names[i].name, names[i].line, names[i].column);
    }

    fclose(tokens_file);
    fclose(nametable_file);

    // error display
    if (error != 0) {
        printf("\nError %d at line %d, column %d: ", error, error_line, error_column);
        switch (error) {
            case 1:
				printf("invalid character '%c'\n", cur_char);
				break;
			case 2:
				printf("identifier too long '%s'\n", lexeme);
				break;
			case 3:
				printf("number too long '%s'\n", lexeme);
				break;
			case 4:
				printf("':' must be followed by '='\n");
				break;
			case 5:
				printf("'!' must be followed by '='\n");
				break;
			case 6:
				printf("number followed by a letter '%s'\n", lexeme);
				break;
			case 7:
				printf("comment is not closed before end of file\n");
				break;
			case 8:
				printf("'*/' without a matching '/*'\n");
				break;
			case 9:
				printf("'/*' inside a comment\n");
				break;
			case 10:
				printf("byte 0x%02X is not part of this language\n",
					(unsigned int)cur_char);
				break;
			case 11:
				printf("no tokens in the source program\n");
				break;
        }
    }
    
    free(names);
    free(tokens);
    free(lexeme);
    fclose(input_file);
    
    if (error != 0) {
        return 1;
    }
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

struct SymbolTableEntry {
    int kind;
    size_t name_index;
    int value;
    int level;
    int address;
    int mark;
};

struct Instruction {
    int op;
    int l;
    int m;
};

static struct NameTableRow names[200];
static struct Token tokens[5000];
static struct SymbolTableEntry symbols[100];
static struct Instruction code[200];
static size_t name_count = 0;
static size_t code_count = 0;
static size_t token_count = 0;
static size_t symbol_count = 0;
static size_t token_pos = 0;
static int next_var_address = 3;

// helpder to get the current token
int current_token(void) {
    if (token_pos >= token_count) {
        return 0;
    }

    return tokens[token_pos].code;
}

// helper to convert token codes to text
const char *token_text(size_t pos) {
    if (pos >= token_count) {
        return "";
    }

    switch (tokens[pos].code) {
        case 1:
            return names[tokens[pos].name_index].name;
        case 2:
            return tokens[pos].number;
        case 3:
            return "+";
        case 4:
            return "-";
        case 5:
            return "*";
        case 6:
            return "/";
        case 7:
            return "==";
        case 8:
            return "!=";
        case 9:
            return "<";
        case 10:
            return "<=";
        case 11:
            return ">";
        case 12:
            return ">=";
        case 13:
            return "(";
        case 14:
            return ")";
        case 15:
            return ",";
        case 16:
            return ";";
        case 17:
            return ".";
        case 18:
            return "=";
        case 19:
            return ":=";
        case 20:
            return "begin";
        case 21:
            return "end";
        case 22:
            return "if";
        case 23:
            return "fi";
        case 24:
            return "then";
        case 25:
            return "while";
        case 26:
            return "elihw";
        case 27:
            return "do";
        case 28:
            return "od";
        case 29:
            return "odd";
        case 30:
            return "call";
        case 31:
            return "const";
        case 32:
            return "var";
        case 33:
            return "procedure";
        case 34:
            return "write";
        case 35:
            return "read";
        case 36:
            return "else";
        default:
            return "";
    }
}

// function to print the current token and move to the next token
void get_next_token(void) {
    if (token_pos >= token_count) {
        return;
    }

    token_pos++;
}

int emit(int op, int l, int m) {
    if (code_count >= 200) {
        printf("Generated Code:\n\n");
        printf("Symbol Table:\n\n");
        printf("Result:\n\n");
        printf("Error 20: generated code exceeds 200 instructions\n");
        exit(1);
    }
    int index = (int) code_count;

    code[code_count].op = op;
    code[code_count].l = l;
    code[code_count].m = m;
    code_count++;

    return index;
}

// function to print the symbol table
void print_symbol_table(void) {
    printf("Symbol Table:\n\n");

    if (symbol_count > 0) {
        printf("entry\tkind\tname\tvalue\tlevel\taddress\tmark\n");
        for (size_t i=0; i<symbol_count; i++) {
            if (symbols[i].kind == 1) {
                printf("%zu\tconstant\t%s\t%d\t%d\t-\t%d\n", 
                    i, names[symbols[i].name_index].name, symbols[i].value, symbols[i].level, symbols[i].mark
                );
            } else if (symbols[i].kind == 2) {
                printf("%zu\tvariable\t%s\t-\t%d\t%d\t%d\n",
                    i, names[symbols[i].name_index].name, symbols[i].level, symbols[i].address, symbols[i].mark
                );
            } else {
                printf("%zu\tprocedure\t%s\t-\t%d\t%d\t%d\n",
                    i, names[symbols[i].name_index].name, symbols[i].level, symbols[i].address, symbols[i].mark
                );
            }
        }
    }

    printf("\n");
}

//function  to handle errors and display them
void display_error(int error_code, size_t error_pos) {
    printf("Generated Code:\n\n");
    printf("Symbol Table:\n\n");
    printf("Result:\n\n");

    if (error_pos < token_count) {
        printf("Error %d at token %zu '%s': ", error_code, error_pos+1, token_text(error_pos));
    } else {
        printf("Error %d at end of tokens: ", error_code);
    }

    switch (error_code) {
        case 1:
            printf("the program must end with a period, and nothing may follow it\n");
            break;
        case 2:
            printf("const, var, procedure, call, and read must be followed by an identifier\n");
            break;
        case 3:
            printf("a constant must be declared as name := number\n");
            break;
        case 4:
            printf("declarations must be separated by , and end with ;\n");
            break;
        case 5:
            printf("an identifier that starts a statement must be followed by =\n");
            break;
        case 6:
            printf("begin must be closed with end\n");
            break;
        case 7:
            printf("a condition after if or while must be followed by then\n");
            break;
        case 8:
            printf("if must be closed with fi, and while with elihw\n");
            break;
        case 9:
            printf("a condition must contain one of == != < <= > >=\n");
            break;
        case 10:
            printf("a left parenthesis must be closed with a right parenthesis\n");
            break;
        case 11:
            printf("a factor must be an identifier, a number, or (\n");
            break;
        case 12:
            printf("a procedure name and a procedure block must each be followed by ;\n");
            break;
        case 13:
            printf("call must name a procedure\n");
            break;
        case 14:
            printf("identifier already declared in this block\n");
            break;
        case 15:
            printf("undeclared identifier\n");
            break;
        case 16:
            printf("only a variable may be assigned or read\n");
            break;
        case 17:
            printf("symbol table is full\n");
            break;
        case 19:
            printf("a procedure name cannot be used in an expression\n");
            break;
    }

    exit(1);
}

// function to find an available symbol for an identifier
int find_symbol(size_t name_index) {
    for (size_t i=symbol_count; i>0; i--) {
        if (symbols[i-1].name_index == name_index && symbols[i-1].mark == 0) {
            return (int) i-1;
        }
    }

    return -1;
}

// this function will check if a declaration is duplicate or the symbol table is full
void check_declaration(size_t name_index, int level) {
    for (size_t i=0; i<symbol_count; i++) {
        if (symbols[i].name_index == name_index && symbols[i].level == level && symbols[i].mark == 0) {
            display_error(14, token_pos-1);
        }
    }
    if (symbol_count >= 100) {
        display_error(17, token_pos-1);
    }
}

// function to insert a variable into the symbol table
void insert_variable(size_t name_index, int level) {
    symbols[symbol_count].kind = 2;
    symbols[symbol_count].name_index = name_index;
    symbols[symbol_count].value = 0;
    symbols[symbol_count].level = level;
    symbols[symbol_count].address = next_var_address;
    symbols[symbol_count].mark = 0;

    symbol_count++;
    next_var_address++;
}

// function to insert a declared constant into the symbol table
void insert_constant(size_t name_index, int value, int level) {
    symbols[symbol_count].kind = 1;
    symbols[symbol_count].name_index = name_index;
    symbols[symbol_count].value = value;
    symbols[symbol_count].level = level;
    symbols[symbol_count].address = 0;
    symbols[symbol_count].mark = 0;

    symbol_count++;
}

// function to look up an identifier and check if it is a variable
void check_identifier(size_t name_index, int variable) {
    int entry = find_symbol(name_index);
    if (entry == -1) {
        display_error(15, token_pos-1);
    }

    if (variable == 1 && symbols[entry].kind != 2) {
        display_error(16, token_pos-1);
    }

    if (variable == 0 && symbols[entry].kind == 3) {
        display_error(19, token_pos-1);
    }
}

// function to mark all symbol entries when the program block ends
void mark_symbols(int level, size_t first) {
    for (size_t i=first; i<symbol_count; i++) {
        if (symbols[i].level == level && symbols[i].mark == 0) {
            symbols[i].mark = 1;
        }
    }
}

void parse_const_declaration(int level) {
    get_next_token();

    while (1) {
        if (current_token() != 1) {
            display_error(2, token_pos);
        }

        size_t name_index = tokens[token_pos].name_index;
        get_next_token();
        check_declaration(name_index, level);

        if (current_token() != 19) {
            display_error(3, token_pos);
        }
        get_next_token();

        if (current_token() != 2) {
            display_error(3, token_pos);
        }

        int value = atoi(tokens[token_pos].number);
        get_next_token();
        insert_constant(name_index, value, level);

        if (current_token() != 15) {
            break;
        }

        get_next_token();
    }

    if (current_token() != 16) {
        display_error(4, token_pos);
    }
    get_next_token();
}

// function to parse variable declaration
void parse_var_declaration(int level) {
    get_next_token();

    while (1) {
        if (current_token() != 1) {
            display_error(2, token_pos);
        }

        size_t name_index = tokens[token_pos].name_index;
        get_next_token();
        check_declaration(name_index, level);
        insert_variable(name_index, level);

        if (current_token() != 15) {
            break;
        }

        get_next_token();
    }

    if (current_token() != 16) {
        display_error(4, token_pos);
    }
    get_next_token();
}

void parse_expression(int level);

void parse_factor(int level) {
    if (current_token() == 1) {
        size_t name_index = tokens[token_pos].name_index;
        get_next_token();
        check_identifier(name_index, 0);

        int entry = find_symbol(name_index);
        if (symbols[entry].kind == 1) {
            emit(1, 0, symbols[entry].value);
        } else if (symbols[entry].kind == 2) {
            emit(3, level-symbols[entry].level, symbols[entry].address);
        }
    } else if (current_token() == 2) {
        int value = atoi(tokens[token_pos].number);
        emit(1, 0, value);
        get_next_token();
    } else if (current_token() == 13) {
        get_next_token();
        parse_expression(level);

        if (current_token() != 14) {
            display_error(10, token_pos);
        }
        get_next_token();
    } else {
        display_error(11, token_pos);
    }
}

void parse_term(int level) {
    parse_factor(level);

    while (current_token() == 5 || current_token() == 6) {
        int operator = current_token();
        get_next_token();
        parse_factor(level);

        if (operator == 5) {
            emit(2, 0, 3);
        } else {
            emit(2, 0, 4);
        }
    }
}

void parse_expression(int level) {
    if (current_token() == 3 || current_token() == 4) {
        get_next_token();
    }

    parse_term(level);

    while (current_token() == 3 || current_token() == 4) {
        get_next_token();
        parse_term(level);
    }
}

void parse_condition(int level) {
    parse_expression(level);

    int t = current_token();
    if (t < 7 || t > 12) {
        display_error(9, token_pos);
    }

    get_next_token();
    parse_expression(level);
}

void parse_statement(int level);

// function to parse statements separated by semicolons
void parse_statement_list(int level) {
    parse_statement(level);

    while (current_token() == 16) {
        get_next_token();
        parse_statement(level);
    }
}

// function to parse statements
void parse_statement(int level) {
    if (current_token() == 30) {
        get_next_token();
        if (current_token() != 1) {
            display_error(2, token_pos);
        }

        size_t name_index = tokens[token_pos].name_index;
        get_next_token();
        int symbol_entry = find_symbol(name_index);

        if (symbol_entry == -1) {
            display_error(15, token_pos-1);
        }

        if (symbols[symbol_entry].kind != 3) {
            display_error(13, token_pos-1);
        }
        return;
    }
    if (current_token() == 1) {
        size_t name_index = tokens[token_pos].name_index;
        get_next_token();
        check_identifier(name_index, 1);

        if (current_token() != 18) {
            display_error(5, token_pos);
        }

        get_next_token();
        parse_expression(level);
        return;
    }

    if (current_token() == 20) {
        get_next_token();
        parse_statement_list(level);
        if (current_token() != 21) {
            display_error(6, token_pos);
        }

        get_next_token();
        return;
    }

    if (current_token() == 22) {
        get_next_token();
        parse_condition(level);

        if (current_token() != 24) {
            display_error(7, token_pos);
        }

        get_next_token();
        parse_statement_list(level);

        if (current_token() == 36) {
            get_next_token();
            parse_statement_list(level);
        }

        if (current_token() != 23) {
            display_error(8, token_pos);
        }

        get_next_token();
        return;
    }

    if (current_token() == 25) {
        get_next_token();
        parse_condition(level);

        if (current_token() != 24) {
            display_error(7, token_pos);
        }

        get_next_token();
        parse_statement_list(level);

        if (current_token() != 26) {
            display_error(8, token_pos);
        }

        get_next_token();
        return;
    }

    if (current_token() == 35) {
        get_next_token();

        if (current_token() != 1) {
            display_error(2, token_pos);
        }

        size_t name_index = tokens[token_pos].name_index;
        get_next_token();
        check_identifier(name_index, 1);
        return;
    }

    if (current_token() == 34) {
        get_next_token();
        parse_expression(level);
        return;
    }

}

void parse_block(int level) {
    size_t first = symbol_count;
    next_var_address = 3;
    if (current_token() == 31) {
        parse_const_declaration(level);
    }
    if (current_token() == 32) {
        parse_var_declaration(level);
    }

    while (current_token() == 33) {
        get_next_token();
        if (current_token() != 1) {
            display_error(2, token_pos);
        }

        size_t name_index = tokens[token_pos].name_index;
        get_next_token();
        check_declaration(name_index, level);
        symbols[symbol_count].kind = 3;
        symbols[symbol_count].name_index = name_index;
        symbols[symbol_count].value = 0;
        symbols[symbol_count].level = level;
        symbols[symbol_count].address = 0;
        symbols[symbol_count].mark = 0;

        symbol_count++;

        if (current_token() != 16) {
            display_error(12, token_pos);
        }
        get_next_token();

        parse_block(level + 1);
        if (current_token() != 16) {
            display_error(12, token_pos);
        }

        get_next_token();
    }

    parse_statement(level);
    mark_symbols(level, first);
}

void parse_program(void) {
    parse_block(0);

    if (current_token() != 17) {
        display_error(1, token_pos);
    }

    get_next_token();

    if (token_pos < token_count) {
        display_error(1, token_pos);
    }
}

// main driver function to start the process
int main(void) {
    FILE *tokens_file = fopen("tokens.txt", "r");
    FILE *names_file = fopen("nametable.txt", "r");

    if (tokens_file == NULL || names_file == NULL) {
        if (tokens_file != NULL) {
            fclose(tokens_file);
        }
        if (names_file != NULL) {
            fclose(names_file);
        }

        printf("Generated Code:\n\n");
        printf("Symbol Table:\n\n");
        printf("Result:\n\n");
        printf("Error 18: cannot open tokens.txt or nametable.txt\n");
        return 1;
    }

    // read the nametable file and count # of names
    size_t index;
    while (name_count < 200 && fscanf(names_file, "%zu %12s %d %d",
        &index, names[name_count].name, &names[name_count].line, &names[name_count].column) == 4
    ) {
        name_count++;
    }

    // reading the tokens.txt file
    while (token_count < 5000 && fscanf(tokens_file, "%d", &tokens[token_count].code) == 1) {
        if (tokens[token_count].code == 1) {
            fscanf(tokens_file, "%zu", &tokens[token_count].name_index);
        } else if (tokens[token_count].code == 2) {
            fscanf(tokens_file, "%6s", tokens[token_count].number);
        }
        token_count++;
    }

    fclose(tokens_file);
    fclose(names_file);

    parse_program();

    printf("\n");
    print_symbol_table();
    printf("Result:\n\nprogram accepted\n");

    return 0;
}
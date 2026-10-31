

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

static struct NameTableRow names[200];
static struct Token tokens[5000];
static struct SymbolTableEntry symbols[100];
static size_t name_count = 0;
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
void get_next_token(const char *owner) {
    if (token_pos >= token_count) {
        return;
    }

    printf("%zu\t", token_pos+1);

    if (tokens[token_pos].code == 1) {
        printf("1 %zu\t", tokens[token_pos].name_index);
    } else if (tokens[token_pos].code == 2) {
        printf("2 %s\t", tokens[token_pos].number);
    } else {
        printf("%d\t", tokens[token_pos].code);
    }

    printf("%s\t%s\n", token_text(token_pos), owner);
    token_pos++;
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
            } else {
                printf("%zu\tvariable\t%s\t-\t%d\t%d\t%d\n",
                    i, names[symbols[i].name_index].name, symbols[i].level, symbols[i].address, symbols[i].mark
                );
            }
        }
    }

    printf("\n");
}

//function  to handle errors and display them
void display_error(int error_code, size_t error_pos) {
    printf("\n");
    print_symbol_table();
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
            printf("const, var, and read must be followed by an identifier\n");
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
            printf("procedure declarations are not part of this grammar\n");
            break;
        case 13:
            printf("call statements are not part of this grammar\n");
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
    }

    exit(1);
}

// function to find an available symbol for an identifier
int find_symbol(size_t name_index) {
    for (size_t i=0; i<symbol_count; i++) {
        if (symbols[i].name_index == name_index && symbols[i].mark == 0) {
            return (int) i;
        }
    }

    return -1;
}

// this function will check if a declaration is duplicate or the symbol table is full
void check_declaration(size_t name_index) {
    if (find_symbol(name_index) != -1) {
        display_error(14, token_pos-1);
    }
    if (symbol_count >= 100) {
        display_error(17, token_pos-1);
    }
}

// function to insert a variable into the symbol table
void insert_variable(size_t name_index) {
    symbols[symbol_count].kind = 2;
    symbols[symbol_count].name_index = name_index;
    symbols[symbol_count].value = 0;
    symbols[symbol_count].level = 0;
    symbols[symbol_count].address = next_var_address;
    symbols[symbol_count].mark = 0;

    printf("\tinsert entry %zu: variable %s, level 0, address %d\n", symbol_count, names[name_index].name, next_var_address);

    symbol_count++;
    next_var_address++;
}

// function to insert a declared constant into the symbol table
void insert_constant(size_t name_index, int value) {
    symbols[symbol_count].kind = 1;
    symbols[symbol_count].name_index = name_index;
    symbols[symbol_count].value = value;
    symbols[symbol_count].level = 0;
    symbols[symbol_count].address = 0;
    symbols[symbol_count].mark = 0;

    printf("\tinsert entry %zu: constant %s, value %d, level 0\n",
        symbol_count, names[name_index].name, value);

    symbol_count++;
}

// function to look up an identifier and check if it is a variable
void check_identifier(size_t name_index, int variable) {
    int entry = find_symbol(name_index);
    if (entry == -1) {
        display_error(15, token_pos-1);
    }

    const char *kind = "variable";
    if (symbols[entry].kind == 1) {
        kind = "constant";
    }
    printf("\tlookup %s: entry %d, %s, level %d\n",
        names[name_index].name, entry, kind, symbols[entry].level
    );

    if (variable == 1 && symbols[entry].kind != 2) {
        display_error(16, token_pos-1);
    }
}

// function to mark all symbol entries when the program block ends
void mark_symbols(void) {
    for (size_t i=0; i<symbol_count; i++) {
        symbols[i].mark = 1;
        printf("\tmark entry %zu\n", i);
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

        printf("Name Table:\n\n");
        printf("Parse Trace:\n\n");
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

    printf("Name Table:\n\n");
    if (name_count > 0) {
        printf("index\tname\tline\tcolumn\n");
        
        for (size_t i=0; i<name_count; i++) {
            printf("%zu\t%s\t%d\t%d\n", i, names[i].name, names[i].line, names[i].column);
        }
    }
    printf("\n");

    // reading the tokens.txt file
    while (token_count < 5000 && fscanf(tokens_file, "%d", &tokens[token_count].code) == 1) {
        if (tokens[token_count].code == 1) {
            fscanf(tokens_file, "%zu", &tokens[token_count].name_index);
        } else if (tokens[token_count].code == 2) {
            fscanf(tokens_file, "%6s", tokens[token_count].number);
        }
        token_count++;
    }

    printf("Parse Trace:\n\n");
    printf("token\tinput\ttext\tnonterminal\n");

    fclose(tokens_file);
    fclose(names_file);
    return 0;
}


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
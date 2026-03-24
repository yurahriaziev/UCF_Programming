#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct parenthesis_node {
    char p;
    struct parenthesis_node *next;
} parenthesis_node;

typedef struct p_stack {
    parenthesis_node *top;
} p_stack;

void init_p_stack(p_stack *stack) {
    stack->top = NULL;
}

int is_empty(p_stack *stack) {
    return stack->top == NULL;
}

int push(p_stack *stack, char p) {
    parenthesis_node *temp = malloc(sizeof(parenthesis_node));
    temp->p = p;
    temp->next = stack->top;
    stack->top = temp;
    return 1;
}

char pop(p_stack *stack) {
    if (is_empty(stack)) {
        return '\0';
    }

    parenthesis_node *temp = stack->top;
    char p = temp->p;
    stack->top = temp->next;
    free(temp);

    return p;
}

void free_stack(p_stack *stack) {
    while (!is_empty(stack)) {
        pop(stack);
    }
}

int is_open(char p) {
    return (p == '(' || p == '[' || p == '{');
}

int is_close(char p) {
    return (p == ')' || p == ']' || p == '}');
}

int matches(char open, char close) {
    return (open == '(' && close == ')') ||
            (open == '[' && close == ']') ||
            (open == '{' && close == '}');
}

int check_pars(char *exp, p_stack *stack) {
    if (!exp || !stack) {
        return 0;
    }

    for (int i=0; exp[i] != '\0'; i++) {
        char p = exp[i];

        if (is_open(p)) {
            push(stack, p);
        } else if (is_close(p)) {
            char open = pop(stack);
            if (!matches(open, p)) {
                return 0;
            }
        }
    }

    int empty = is_empty(stack);
    free_stack(stack);
    return empty;
}

int main() {
    p_stack stack;
    init_p_stack(&stack);

    char input[7];
    printf("Enter expression max 6 chars: ");
    scanf("%6s", input);

    if (check_pars(input, &stack)) {
        printf("Balanced\n");
    } else {
        printf("Not balanced\n");
    }

    return 0;
}
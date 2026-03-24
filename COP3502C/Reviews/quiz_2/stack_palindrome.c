#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char c;
    struct node *next;
} node;

typedef struct stack {
    node *top;
} stack;

void init_stack(stack *stack) {
    stack->top = NULL;
}

int is_empty(stack *stack) {
    return stack->top == NULL;
}

int push(stack *stack, char c) {
    if (!stack) {
        return 0;
    }

    node *temp = malloc(sizeof(node));
    temp->c = c;
    temp->next = stack->top;
    stack->top = temp;

    return 1;
}

char pop(stack *stack) {
    if (!stack || is_empty(stack)) return '\0';

    node *temp = stack->top;
    char c = temp->c;
    stack->top = temp->next;
    free(temp);

    return c;
}

void free_stack(stack *stack) {
    while (!is_empty(stack)) {
        pop(stack);
    }
}

int is_palindrome(const char *exp, stack *stack) {
    if (!exp || !stack) {
        return 0;
    }

    for (int i=0; exp[i]!='\0'; i++) {
        push(stack, exp[i]);
    }

    for (int i=0; exp[i]!='\0'; i++) {
        char top = pop(stack);
        if (exp[i] != top) {
            free_stack(stack);
            return 0;
        }
    }

    return 1;
}

int main() {
    stack stack;
    init_stack(&stack);

    char exp[100] = "abcba";
    printf("%d\n", is_palindrome(exp, &stack));

    return 0;
}
/*              COP 3502C PA ###
This program is editted by: Yurii Hriaziev */

//Stack implementation using array skeleton code

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// The array will store the items in the stack, first in
// index 0, then 1, etc. top will represent the index
// to the top element in the stack. If the stack is
// empty top will be -1.

#define SIZE 100
#define EMPTY -1

struct stack {

    char items[SIZE];

    int top;

};

void initialize(struct stack* stackPtr);
int full(struct stack* stackPtr);
int push(struct stack* stackPtr, char value);
int empty(struct stack* stackPtr);
char pop(struct stack* stackPtr);
int peek(struct stack* stackPtr);
void display(struct stack* stackPtr);

int isOpen(char c) {
    return c == '(' || c == '{' || c == '[';
}
int isClose(char c) {
    return c == ')' || c == '}' || c == ']';
}

int match(char open, char close) {
    return (open == '(' && close == ')' || open == '{' && close == '}' || open == '[' && close == ']');
}

int isParentheses(char ch1)
{
    if (ch1 == '(' || ch1 == ')' ||
        ch1 == '{' || ch1 == '}' ||
        ch1 == '[' || ch1 == ']')
    {
        return 1;
    }

    return 0;
}

// checkBalance: function that takes in an expression and returns 1 if it has valid/balanced paranthesis return 0 if invalid.
int checkBalance(const char exp[], char *invalidPar) {
    struct stack s;
    initialize(&s);

    int i = 0;
    char ch;

    while (exp[i] != '\0') {
        ch = exp[i];

        if (isParentheses(ch)) {
            if (isOpen(ch)) {
                push(&s, ch);
            } else  if (isClose(ch)) {
                if (empty(&s)) {
                    *invalidPar = ch;
                    return 0;
                }

                char top = pop(&s);

                if (!match(top, ch)) {
                    *invalidPar = ch;
                    return 0;
                }
            } 
        }
        i++;
    }

    if (!empty(&s)) {
        *invalidPar = '\0';
        return 0;
    }
    return 1;
}

// isOperator: function that takes in a char and determines if char is an operator or not
int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// priority: function that will return what priority a given operator has
int priority(char ch)
{
    if (ch == '^') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return 0;
}

char *infixToPostfix(char infix[]) {
    struct stack s;
    initialize(&s);

    int n = (int)strlen(infix);
    char *postfix = (char*)malloc(2*n + 5);

    int k = 0;
    for (int i=0; infix[i] != '\0'; i++) {
        char ch = infix[i];
        if (isalnum((unsigned char)ch)) {
            postfix[k++] = ch;
            postfix[k++] = ' ';
        } else if (ch == '(') {
            push(&s, ch);
        } else if (ch == ')') {
            while (!empty(&s) && (char)peek(&s) != '(') {
                postfix[k++] = pop(&s);
                postfix[k++] = ' ';
            }

            if (!empty(&s) && (char)peek(&s) == '(') {
                pop(&s);
            }
        } else if (isOperator(ch)) {
            while (!empty(&s) && isOperator((char)peek(&s))) {
                char top = peek(&s);

                int pTop = priority(top);
                int pCur = priority(ch);

                if ((ch != '^' && pTop >= pCur) || (ch == '^' && pTop > pCur)) {
                    postfix[k++] = pop(&s);
                    postfix[k++] = ' ';
                } else {
                    break;
                }
            }
            push(&s, ch);
        }
    }

    while (!empty(&s)) {
        char top = pop(&s);
        if (top != '(') {
            postfix[k++] = top;
            postfix[k++] = ' ';
        }
    }

    if (k > 0 && postfix[k-1] == ' ') {
        k--;
    }

    postfix[k] = '\0';
    return postfix;
}

int main() {
    int i;
    //declare a stack
    struct stack myStack;
    // Set up the stack and push a couple items, then pop one.
    initialize(&myStack); //call this function appropriately
    
    // int ele;
    // int ch;
    // while(1)
    // {
    //     printf("\nMenu:\n 1: Stack 1 push\n 3: Stack 1 Pop\n \n 5: Stack 1 display\n 7: Exit\nEnter your choice: ");
    //     scanf("%d",&ch);
    //     if(ch==7)
    //     {
    //         printf("<<EXIT>>");
    //         break;
    //     }
    //     else if (ch==1)
    //     {
    //         printf("Enter an element to PUSH in the stack1: ");
    //         scanf("%d",&ele);
    //         push(&stack1, ele);
    //         display(&stack1);
    //     }
    //     else if (ch==2)
    //     {
    //         printf("Enter an element to PUSH in the stack2: ");
    //         scanf("%d",&ele);
    //         push(&stack2, ele);
    //         display(&stack2);
    //     }
    //     else if (ch==3)
    //     {
    //         ele = pop(&stack1);
    //         if(ele!=0 )
    //         {
    //             printf(" ITEM POPPED from Stack 1: %d ",ele);
    //             display(&stack1);
    //         }
    //     }
    //     else if (ch==4)
    //     {
    //         ele = pop(&stack2);
    //         if(ele!=0 )
    //         {
    //             printf(" ITEM POPPED from Stack 2: %d ",ele);
    //             display(&stack2);
    //         }
    //     }
    //     else if(ch==5)
    //     {
    //         display(&stack1);
    //     }
    //     else if(ch==6)
    //     {
    //         display(&stack2);
    //     }
    // }

    // LAB CODE
    char exp[100];
    char invalidPar;
    printf("Enter Expression: ");
    fgets(exp, sizeof(exp), stdin);
    exp[strcspn(exp, "\n")] = '\0';

    printf("Your input expression: %s\n\n", exp);
    printf("Checking balance...\n");
    if (checkBalance(exp, &invalidPar)) {
        printf("VALID\n");
        char *postfix = infixToPostfix(exp);
        printf("The postfix is: %s\n", postfix);
        free(postfix);
    } else {
        if (invalidPar != '\0') {
            printf("INVALID for %c!!!\n", invalidPar);
        } else {
            printf("INVALID\n");
        }
    }

    return 0;
}

void initialize(struct stack* stackPtr) {
    stackPtr->top = -1;
}

// If the push occurs, 1 is returned. If the
// stack is full and the push can't be done, 0 is
// returned.
int push(struct stack* stackPtr, char value) {
    if (full(stackPtr)) {
        return 0;
    }

    stackPtr->top++;
    stackPtr->items[stackPtr->top] = value;
    return 1;
}

// Returns true iff the stack pointed to by stackPtr is full.
int full(struct stack* stackPtr) {
    return (stackPtr->top == SIZE - 1);
}

// Returns true iff the stack pointed to by stackPtr is empty.
int empty(struct stack* stackPtr) {
    return (stackPtr->top == -1);
}

// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is popped and returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
char pop(struct stack* stackPtr) {
    if (empty(stackPtr)) {
        return EMPTY;
    }

    char value = stackPtr->items[stackPtr->top];
    stackPtr->top--;
    return value;
}

// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
int peek(struct stack* stackPtr) {

    // Take care of the empty case.
    if (empty(stackPtr))
        return EMPTY;

    // Return the desired item.
    return stackPtr->items[stackPtr->top];
}

void display(struct stack* stackPtr) {
    printf("\nPrinting the Current stack...");
    for(int i=0; i<=stackPtr->top; i++)
        printf("%d ", stackPtr->items[i]);
}

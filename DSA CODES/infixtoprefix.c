#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

void push(Stack *stack, char item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->items[++stack->top] = item;
}

char pop(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top--];
}

int is_operator(char symbol) {
    return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/');
}

int precedence(char symbol) {
    if (symbol == '+' || symbol == '-') {
        return 1;
    } else if (symbol == '*' || symbol == '/') {
        return 2;
    }
    return 0;
}

void infix_to_prefix(char *infix, char *prefix) {
    Stack stack;
    stack.top = -1;
    int length = strlen(infix);
    int j = 0;

    for (int i = length - 1; i >= 0; i--) {
        if (isalnum(infix[i])) {
            prefix[j++] = infix[i];
        } else if (infix[i] == ')') {
            push(&stack, infix[i]);
        } else if (infix[i] == '(') {
            while (stack.top != -1 && stack.items[stack.top] != ')') {
                prefix[j++] = pop(&stack);
            }
            if (stack.top == -1) {
                printf("Invalid Expression\n");
                exit(EXIT_FAILURE);
            }
            pop(&stack);
        } else if (is_operator(infix[i])) {
            while (stack.top != -1 && precedence(stack.items[stack.top]) > precedence(infix[i])) {
                prefix[j++] = pop(&stack);
            }
            push(&stack, infix[i]);
        }
    }

    while (stack.top != -1) {
        if (stack.items[stack.top] == '(' || stack.items[stack.top] == ')') {
            printf("Invalid Expression\n");
            exit(EXIT_FAILURE);
        }
        prefix[j++] = pop(&stack);
    }

    prefix[j] = '\0';

    // Reverse the prefix string to get the correct prefix expression
    int len = strlen(prefix);
    for (int i = 0; i < len / 2; i++) {
        char temp = prefix[i];
        prefix[i] = prefix[len - i - 1];
        prefix[len - i - 1] = temp;
    }
}

int evaluate_prefix(char *prefix) {
    Stack stack;
    stack.top = -1;
    int length = strlen(prefix);

    for (int i = length - 1; i >= 0; i--) {
        if (isdigit(prefix[i])) {
            push(&stack, prefix[i] - '0');
        } else if (is_operator(prefix[i])) {
            int operand1 = pop(&stack);
            int operand2 = pop(&stack);
            switch (prefix[i]) {
                case '+':
                    push(&stack, operand1 + operand2);
                    break;
                case '-':
                    push(&stack, operand1 - operand2);
                    break;
                case '*':
                    push(&stack, operand1 * operand2);
                    break;
                case '/':
                    push(&stack, operand1 / operand2);
                    break;
            }
        }
    }
    return pop(&stack);
}

int main() {
    char infix[MAX_SIZE], prefix[MAX_SIZE];

    printf("Enter an infix expression: ");
    fgets(infix, MAX_SIZE, stdin);
    infix[strcspn(infix, "\n")] = '\0'; // Remove trailing newline if present

    infix_to_prefix(infix, prefix);
    printf("Prefix expression: %s\n", prefix);

    int result = evaluate_prefix(prefix);
    printf("Result: %d\n", result);

    return 0;
}

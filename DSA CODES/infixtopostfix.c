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

void infix_to_postfix(char *infix, char *postfix) {
    Stack stack;
    stack.top = -1;
    int length = strlen(infix);
    int j = 0;

    for (int i = 0; i < length; i++) {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(&stack, infix[i]);
        } else if (infix[i] == ')') {
            while (stack.top != -1 && stack.items[stack.top] != '(') {
                postfix[j++] = pop(&stack);
            }
            if (stack.top == -1 || stack.items[stack.top] != '(') {
                printf("Invalid Expression\n");
                exit(EXIT_FAILURE);
            }
            pop(&stack); // Discard the '('
        } else if (is_operator(infix[i])) {
            while (stack.top != -1 && precedence(stack.items[stack.top]) >= precedence(infix[i])) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, infix[i]);
        }
    }

    while (stack.top != -1) {
        if (stack.items[stack.top] == '(' || stack.items[stack.top] == ')') {
            printf("Invalid Expression\n");
            exit(EXIT_FAILURE);
        }
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
}

int evaluate_postfix(char *postfix) {
    Stack stack;
    stack.top = -1;
    int length = strlen(postfix);

    for (int i = 0; i < length; i++) {
        if (isdigit(postfix[i])) {
            push(&stack, postfix[i] - '0');
        } else if (is_operator(postfix[i])) {
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            switch (postfix[i]) {
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
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    printf("Enter an infix expression: ");
    fgets(infix, MAX_SIZE, stdin);
    infix[strcspn(infix, "\n")] = '\0'; // Remove trailing newline if present

    infix_to_postfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    int result = evaluate_postfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}

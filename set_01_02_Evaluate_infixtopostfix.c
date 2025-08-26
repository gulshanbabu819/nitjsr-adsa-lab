#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>   // for isdigit()

#define MAX 100

// Stack for characters
struct Stack {
    char arr[MAX];
    int top;
};

// Initialize stack
void init(struct Stack* s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(struct Stack* s) {
    return s->top == -1;
}

// Push onto stack
void push(struct Stack* s, char c) {
    if (s->top == MAX - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    s->arr[++s->top] = c;
}

// Pop from stack
char pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return s->arr[s->top--];
}

// Peek top of stack
char peek(struct Stack* s) {
    if (isEmpty(s)) return '\0';
    return s->arr[s->top];
}

// Function to return precedence of operators
int precedence(char op) {
    switch (op) {
        case '/': return 3;
        case '*': return 3;
        case '+': return 2;
        case '-': return 2;
        default:  return 0;
    }
}

// Convert infix to postfix
void infixToPostfix(char* infix, char* postfix) {
    struct Stack s;
    init(&s);
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        char c = infix[i];

        // If operand, add to postfix
        if (isdigit(c)) {
            postfix[j++] = c;
        }
        // If '(', push to stack
        else if (c == '(') {
            push(&s, c);
        }
        // If ')', pop until '('
        else if (c == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s); // Remove '('
        }
        // If operator
        else {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(c)) {
                postfix[j++] = pop(&s);
            }
            push(&s, c);
        }
        i++;
    }

    // Pop remaining operators
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }

    postfix[j] = '\0'; // Null terminate string
}
// Evaluate postfix expression
int evaluatePostfix(char* postfix) {
    int stack[MAX];
    int top = -1;
    int i = 0;

    while (postfix[i] != '\0') {
        char c = postfix[i];

        if (isdigit(c)) {
            stack[++top] = c - '0'; // Convert char to int
        } else {
            int b = stack[top--];
            int a = stack[top--];
            int result;

            switch (c) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': 
                    if (b == 0) {
                        printf("Error: Division by zero\n");
                        exit(1);
                    }
                    result = a / b;
                    break;
                default:
                    printf("Invalid operator: %c\n", c);
                    exit(1);
            }

            stack[++top] = result;
        }

        i++;
    }

    return stack[top];
}


int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);
    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);
    return 0;
}
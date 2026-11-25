#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define BUF_SIZE 256
#define OVERFLOW_TEST_COUNT 70

// Stack 

typedef struct Node {
    char val;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

void init(Stack *s) {
    s->top = NULL;
}

bool is_empty(const Stack *s) {
    return s->top == NULL;
}

bool is_full(const Stack *s) {
    (void)s;
    return false;
}

bool push(Stack *s, char c) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Error: push failed, memory allocation error.\n");
        return false;
    }
    node->val = c;
    node->next = s->top;
    s->top = node;
    return true;
}

bool pop(Stack *s, char *out) {
    if (is_empty(s)) {
        printf("Error: pop failed, stack is empty.\n");
        return false;
    }
    Node *tmp = s->top;
    *out = tmp->val;
    s->top = tmp->next;
    free(tmp);
    return true;
}

bool peek(const Stack *s, char *out) {
    if (is_empty(s)) {
        return false;
    }
    *out = s->top->val;
    return true;
}

void clear_stack(Stack *s) {
    char dummy;
    while (!is_empty(s)) {
        pop(s, &dummy);
    }
}

// App logic 

bool is_operator(char c) {
    return c == '+' || c == '-';
}

bool infix_to_postfix(const char *infix, char *postfix, size_t out_size) {
    Stack s;
    init(&s);

    size_t i = 0;
    size_t k = 0;
    char top_ch;
    bool expect_operand = true;

    while (infix[i] != '\0') {
        if (isspace((unsigned char)infix[i])) {
            i++;
            continue;
        }

        if (isalnum((unsigned char)infix[i]) || infix[i] == '.') {
            if (!expect_operand) {
                printf("Error: expected '+' or '-' between operands.\n");
                clear_stack(&s);
                return false;
            }
            while (isalnum((unsigned char)infix[i]) || infix[i] == '.') {
                if (k + 2 >= out_size) {
                    printf("Error: output buffer overflow.\n");
                    clear_stack(&s);
                    return false;
                }
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' ';
            expect_operand = false;
        } else if (is_operator(infix[i])) {
            if (expect_operand) {
                printf("Error: expected operand before '%c'.\n", infix[i]);
                clear_stack(&s);
                return false;
            }
            char cur = infix[i];
            while (peek(&s, &top_ch)) {
                pop(&s, &top_ch);
                if (k + 2 >= out_size) {
                    printf("Error: output buffer overflow.\n");
                    clear_stack(&s);
                    return false;
                }
                postfix[k++] = top_ch;
                postfix[k++] = ' ';
            }
            if (!push(&s, cur)) {
                clear_stack(&s);
                return false;
            }
            expect_operand = true;
            i++;
        } else {
            printf("Error: invalid character '%c' (only operands, '+' and '-' are allowed).\n", infix[i]);
            clear_stack(&s);
            return false;
        }
    }

    if (k == 0) {
        printf("Error: empty expression.\n");
        clear_stack(&s);
        return false;
    }

    if (expect_operand) {
        printf("Error: expression cannot end with an operator.\n");
        clear_stack(&s);
        return false;
    }

    while (!is_empty(&s)) {
        pop(&s, &top_ch);
        if (k + 2 >= out_size) {
            printf("Error: output buffer overflow.\n");
            clear_stack(&s);
            return false;
        }
        postfix[k++] = top_ch;
        postfix[k++] = ' ';
    }

    if (k > 0 && postfix[k - 1] == ' ') {
        k--;
    }
    postfix[k] = '\0';
    return true;
}

void test_empty_stack(void) {
    Stack s;
    char dummy;
    init(&s);
    printf("Testing pop on empty stack:\n");
    pop(&s, &dummy);
}

void test_overflow_stack(void) {
    Stack s;
    init(&s);
    int pushed = 0;

    printf("Testing push (%d elements):\n", OVERFLOW_TEST_COUNT);
    for (int i = 0; i < OVERFLOW_TEST_COUNT; i++) {
        if (!push(&s, '+')) {
            break;
        }
        pushed++;
    }
    printf("Successfully pushed: %d. is_full() = %s\n",
           pushed, is_full(&s) ? "true" : "false");
    clear_stack(&s);
}

int main(void) {
    char line[BUF_SIZE];
    char postfix[BUF_SIZE * 2];

    while (true) {
        printf("\nMenu:\n");
        printf("1. Convert infix expression (+ and -, no parentheses)\n");
        printf("2. Test pop on empty stack\n");
        printf("3. Test push overflow\n");
        printf("0. Exit\n");
        printf("Choose option: ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
        line[strcspn(line, "\r\n")] = '\0';

        if (strcmp(line, "0") == 0) {
            break;
        } else if (strcmp(line, "1") == 0) {
            printf("Enter infix expression: ");
            if (fgets(line, sizeof(line), stdin) == NULL) {
                break;
            }
            line[strcspn(line, "\r\n")] = '\0';

            if (infix_to_postfix(line, postfix, sizeof(postfix))) {
                printf("Postfix expression: %s\n", postfix);
            }
        } else if (strcmp(line, "2") == 0) {
            test_empty_stack();
        } else if (strcmp(line, "3") == 0) {
            test_overflow_stack();
        } else {
            printf("Unknown option. Please enter 0, 1, 2 or 3.\n");
        }
    }

    return 0;
}
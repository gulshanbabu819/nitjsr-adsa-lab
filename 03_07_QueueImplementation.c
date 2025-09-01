#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Stack {
    int arr[MAX];
    int top;
};

void init(struct Stack *s) {
    s->top = -1;
}

int isEmpty(struct Stack *s) {
    return s->top == -1;
}

int isFull(struct Stack *s) {
    return s->top == MAX - 1;
}

void push(struct Stack *s, int x) {
    if (isFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->arr[++s->top] = x;
}

int pop(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        return -1;
    }
    return s->arr[s->top--];
}

int peek(struct Stack *s) {
    if (isEmpty(s)) return -1;
    return s->arr[s->top];
}
struct Queue1 {
    struct Stack s1, s2;
};

void initQueue1(struct Queue1 *q) {
    init(&q->s1);
    init(&q->s2);
}

void enqueue1(struct Queue1 *q, int x) {
    // Move all elements from s1 to s2
    while (!isEmpty(&q->s1)) {
        push(&q->s2, pop(&q->s1));
    }

    // Push new element into s1
    push(&q->s1, x);

    // Move everything back to s1
    while (!isEmpty(&q->s2)) {
        push(&q->s1, pop(&q->s2));
    }
    printf("Enqueued %d\n", x);
}

int dequeue1(struct Queue1 *q) {
    if (isEmpty(&q->s1)) {
        printf("Queue Underflow!\n");
        return -1;
    }
    return pop(&q->s1);
}
struct Queue2 {
    struct Stack s1, s2;
};

void initQueue2(struct Queue2 *q) {
    init(&q->s1);
    init(&q->s2);
}

void enqueue2(struct Queue2 *q, int x) {
    push(&q->s1, x);
    printf("Enqueued %d\n", x);
}

int dequeue2(struct Queue2 *q) {
    if (isEmpty(&q->s1)) {
        printf("Queue Underflow!\n");
        return -1;
    }

    // Move elements to s2
    while (!isEmpty(&q->s1)) {
        push(&q->s2, pop(&q->s1));
    }

    // Pop the element from s2
    int val = pop(&q->s2);

    // Move elements back to s1
    while (!isEmpty(&q->s2)) {
        push(&q->s1, pop(&q->s2));
    }

    return val;
}
int main() {
    struct Queue1 q1;
    initQueue1(&q1);

    enqueue1(&q1, 10);
    enqueue1(&q1, 20);
    enqueue1(&q1, 30);
    printf("Dequeued: %d\n", dequeue1(&q1));
    printf("Dequeued: %d\n", dequeue1(&q1));

    struct Queue2 q2;
    initQueue2(&q2);

    enqueue2(&q2, 100);
    enqueue2(&q2, 200);
    enqueue2(&q2, 300);
    printf("Dequeued: %d\n", dequeue2(&q2));
    printf("Dequeued: %d\n", dequeue2(&q2));

    return 0;
}

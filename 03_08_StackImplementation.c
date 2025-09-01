#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Queue {
    int arr[MAX];
    int front, rear;
};

void init(struct Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(struct Queue *q) {
    return q->front == -1;
}

int isFull(struct Queue *q) {
    return (q->rear + 1) % MAX == q->front;
}

void enqueue(struct Queue *q, int x) {
    if (isFull(q)) {
        printf("Queue Overflow!\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->rear = (q->rear + 1) % MAX;
    q->arr[q->rear] = x;
}

int dequeue(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow!\n");
        return -1;
    }
    int val = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    return val;
}

int front(struct Queue *q) {
    if (isEmpty(q)) return -1;
    return q->arr[q->front];
}
struct Stack1 {
    struct Queue q1, q2;
};

void initStack1(struct Stack1 *s) {
    init(&s->q1);
    init(&s->q2);
}

void push1(struct Stack1 *s, int x) {
    // Move all elements from q1 to q2
    while (!isEmpty(&s->q1)) {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    // Add new element to q1
    enqueue(&s->q1, x);

    // Move back elements from q2 to q1
    while (!isEmpty(&s->q2)) {
        enqueue(&s->q1, dequeue(&s->q2));
    }
    printf("Pushed %d\n", x);
}

int pop1(struct Stack1 *s) {
    if (isEmpty(&s->q1)) {
        printf("Stack Underflow!\n");
        return -1;
    }
    return dequeue(&s->q1);
}
struct Stack2 {
    struct Queue q1, q2;
};

void initStack2(struct Stack2 *s) {
    init(&s->q1);
    init(&s->q2);
}

void push2(struct Stack2 *s, int x) {
    enqueue(&s->q1, x);
    printf("Pushed %d\n", x);
}

int pop2(struct Stack2 *s) {
    if (isEmpty(&s->q1)) {
        printf("Stack Underflow!\n");
        return -1;
    }

    // Leave last element in q1, move others to q2
    while (s->q1.front != s->q1.rear) {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    // Last element in q1
    int val = dequeue(&s->q1);

    // Swap q1 and q2
    struct Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;

    return val;
}
int main() {
    struct Stack1 s1;
    initStack1(&s1);

    push1(&s1, 10);
    push1(&s1, 20);
    push1(&s1, 30);
    printf("Popped: %d\n", pop1(&s1));
    printf("Popped: %d\n", pop1(&s1));

    struct Stack2 s2;
    initStack2(&s2);

    push2(&s2, 100);
    push2(&s2, 200);
    push2(&s2, 300);
    printf("Popped: %d\n", pop2(&s2));
    printf("Popped: %d\n", pop2(&s2));

    return 0;
}

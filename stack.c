#include "stack.h"

Stack InitStack() {
    Stack s;
    s.pick = 0;
    s.size = INIT_SIZE;
    s.array = malloc(s.size * sizeof(int));
    return s;
}

void ExtendStack(Stack *s) {
    s->size *= EXTEND_COEFF;
    s->array = realloc(s->array, s->size * sizeof(int));
}

bool StackIsFull(Stack *s) {
    return s->pick == s->size;
}

void PushStack(Stack *s, int x) {
    s->array[s->pick] = x;
    s->pick++;
    if (StackIsFull(s)) {
        ExtendStack(s);
    }
}

int PopStack(Stack *s) {
    s->pick--;
    return s->array[s->pick];
}

void RemoveStack(Stack *s) {
    free(s->array);
}
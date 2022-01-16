#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define EXTEND_COEFF 2
#define INIT_SIZE 4

typedef struct Stack {
    int *array;
    size_t pick;
    size_t size;
} Stack;

Stack InitStack();

void ExtendStack(Stack *s);

bool StackIsFull(Stack *s);

void PushStack(Stack *s, int x);

int PopStack(Stack *s);

void RemoveStack(Stack *s);

#endif
#ifndef VARIABLE_H
#define VARIABLE_H

#include "stack.h"

#define BASE 10000
#define VARIABLES 26

typedef struct Variable {
    int *cart; // przechowuje 4 cyfry zmiennej
    int size;
} Variable;

void VarSetToZero(Variable *var);

void VarExtend(Variable *var, int x);

void VarDestroy(Variable *var);

void VarPrint(Variable *var, int x);

void VarZero(Variable *var, int x);

bool VarIsZero(Variable *var, int x);

void VarIncrease(Variable *var, int x);

void VarDecrease(Variable *var, int x);

void VarAdd(Variable *var, int x, int y);

#endif
#ifndef PARSE_H
#define PARSE_H

#include "variable.h"

#define ASCII_OFFSET 97

#define EMPTY -1
#define INC 1
#define ADD 2
#define CLR 3
#define JMP 4
#define DJZ 5
#define HLT 6

typedef struct Instruction {
    int type; // typ polecenia ze zbioru {INC, ADD, CLR, JMP, DJZ, HLT} lub 0 - instrukcja pusta
    int first_arg; // pierwszy argument polecenia (jeśli nie ma to -1)
    int second_arg; // drugi argument polecenia (jeśli nie ma to -1)
} Instruction;

typedef struct InstructionList {
    Instruction *arr; // w i-tej komórce przechowywana jest i-ta instrukcja oraz jej argumenty
    size_t size;
    size_t capacity;
} InstructionList;

InstructionList InitInstructionList();

void ExtendInstructionList(InstructionList *instr);

void RemoveInstructionList(InstructionList *instr);

void ParseCode(InstructionList *instr, Stack *s, int idx);

bool IsOptimisationPossible(InstructionList *instr, size_t idx);

void OptimiseCode(InstructionList *instr);

void ExecuteCode(InstructionList *instr, Variable *var);

#endif
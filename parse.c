#include "parse.h"

InstructionList InitInstructionList() {
    InstructionList instr;
    instr.arr = malloc(sizeof(Instruction));
    instr.size = 0;
    instr.capacity = 1;
    return instr;
}

void ExtendInstructionList(InstructionList *instr) {
    instr->capacity *= EXTEND_COEFF;
    instr->arr = realloc(instr->arr, instr->capacity * sizeof(Instruction));
}

void RemoveInstructionList(InstructionList *instr) {
    free(instr->arr);
}

void ParseCode(InstructionList *instr, Stack *s, int idx) {
    int c = getchar();

    switch (c) {
        case '(':
            if (instr->size == instr->capacity) {
                ExtendInstructionList(instr);
            }

            c = getchar();
            instr->arr[idx].type = DJZ;
            instr->arr[idx].first_arg = c;
            instr->size++;
            PushStack(s, idx);

            ParseCode(instr, s, idx + 1);
            break;
        case ')':
            if (instr->size == instr->capacity) {
                ExtendInstructionList(instr);
            }

            instr->arr[idx].type = JMP;
            int index = PopStack(s);
            instr->arr[idx].first_arg = index;
            instr->arr[idx].second_arg = EMPTY;
            instr->size++;
            instr->arr[index].second_arg = idx + 1;

            ParseCode(instr, s, idx + 1);
            break;
        case '\n':
            if (instr->size == instr->capacity) {
                ExtendInstructionList(instr);
            }

            instr->arr[idx].type = HLT;
            instr->arr[idx].first_arg = EMPTY;
            instr->arr[idx].second_arg = EMPTY;
            instr->size++;
            break;
        default: // przeczytany znak to zmienna
            if (instr->size == instr->capacity) {
                ExtendInstructionList(instr);
            }

            instr->arr[idx].type = INC;
            instr->arr[idx].first_arg = c;
            instr->arr[idx].second_arg = EMPTY;
            instr->size++;

            ParseCode(instr, s, idx + 1);
            break;
    }
}

bool IsOptimisationPossible(InstructionList *instr, size_t idx) {
    int var = instr->arr[idx].first_arg;

    for (size_t i = idx + 1; instr->arr[i].type != JMP; i++) {
        int curr_type = instr->arr[i].type;
        if ((curr_type == DJZ) ||
            (curr_type == INC && instr->arr[i].first_arg == var)) {
            return false;
        }
    }

    return true;
}

void OptimiseCode(InstructionList *instr) {
    for (size_t i = 0; i < instr->size; i++) {
        if (instr->arr[i].type == DJZ && IsOptimisationPossible(instr, i)) {
            size_t j;

            for (j = i + 1; instr->arr[j].type == INC; j++) {
                instr->arr[j].type = ADD;
                instr->arr[j].second_arg = instr->arr[i].first_arg;
            }

            instr->arr[j].type = CLR;
            instr->arr[j].first_arg = instr->arr[i].first_arg;
            instr->arr[i].type = EMPTY;
            instr->arr[i].first_arg = EMPTY;
            instr->arr[i].second_arg = EMPTY;

            i = j;
        }
    }
}

void ExecuteCode(InstructionList *instr, Variable *var) {
    int i = 0;
    int curr_instr;

    while ((curr_instr = instr->arr[i].type) != HLT) {
        switch(curr_instr) {
            case INC:
                VarIncrease(var, instr->arr[i].first_arg - ASCII_OFFSET);
                i++;
                break;
            case ADD:
                VarAdd(var, instr->arr[i].first_arg - ASCII_OFFSET, instr->arr[i].second_arg - ASCII_OFFSET);
                i++;
                break;
            case CLR:
                VarZero(var, instr->arr[i].first_arg - ASCII_OFFSET);
                i++;
                break;
            case JMP:
                i = instr->arr[i].first_arg;
                break;
            case DJZ:
                if (VarIsZero(var, instr->arr[i].first_arg - ASCII_OFFSET)) {
                    i = instr->arr[i].second_arg;
                }
                else {
                    VarDecrease(var, instr->arr[i].first_arg - ASCII_OFFSET);
                    i++;
                }
                break;
            default:
                i++;
                break;
        }
    }
}
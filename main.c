/** Zadanie zaliczeniowe 3: Pętlik
  * autor: Grzegorz Nowakowski
  */

#include "parse.h"

int main() {
    int c;
    Stack stack = InitStack();
    Variable *variables = malloc(VARIABLES * sizeof(Variable));
    VarSetToZero(variables);

    while ((c = getchar()) != EOF) {
        if (c == '=') {
            c = getchar();
            VarPrint(variables, c - ASCII_OFFSET);
        }
        else if (c != '\n'){
            ungetc(c, stdin);
            InstructionList instructions = InitInstructionList();
            ParseCode(&instructions, &stack, 0);
            OptimiseCode(&instructions);
            ExecuteCode(&instructions, variables);
            RemoveInstructionList(&instructions);
        }
    }
    RemoveStack(&stack);
    VarDestroy(variables);
    free(variables);
}

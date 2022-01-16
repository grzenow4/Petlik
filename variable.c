#include "variable.h"

void VarSetToZero(Variable *var) {
    for (int i = 0; i < VARIABLES; i++) {
        var[i].size = 1;
        var[i].cart = malloc(sizeof(int));
        var[i].cart[0] = 0;
    }
}

void VarExtend(Variable *var, int x) {
    var[x].size++;
    var[x].cart = realloc(var[x].cart, var[x].size * sizeof(Variable));
}

void VarDestroy(Variable *var) {
    for (int i = 0; i < VARIABLES; i++) {
        free(var[i].cart);
    }
}

void VarPrint(Variable *var, int x) {
    printf("%d", var[x].cart[var[x].size - 1]);
    for (int i = var[x].size - 2; i >= 0; i--) {
        printf("%04d", var[x].cart[i]);
    }
    putchar('\n');
}

void VarZero(Variable *var, int x) {
    var[x].size = 1;
    var[x].cart = realloc(var[x].cart, sizeof(int));
    var[x].cart[0] = 0;
}

bool VarIsZero(Variable *var, int x) {
    return (var[x].size == 1 && var[x].cart[0] == 0);
}

void VarIncrease(Variable *var, int x) {
    int rest = 1;

    for (int i = 0; i < var[x].size && rest == 1; i++) {
        var[x].cart[i]++;

        if (var[x].cart[i] < BASE) {
            rest = 0;
        }
        else {
            var[x].cart[i] = 0;
        }
    }
    // przypadek kiedy ta liczba składa się z podzielnej przez 4 liczby dziewiątek
    if (rest == 1) {
        VarExtend(var, x);
        var[x].cart[var[x].size - 1] = rest;
    }
}

void VarDecrease(Variable *var, int x) {
    int rest = 1;

    for (int i = 0; i < var[x].size && rest == 1; i++) {
        if(var[x].cart[i] == 0) {
            var[x].cart[i] = BASE - rest;
        }
        else {
            var[x].cart[i]--;
            rest = 0;
        }
    }
    // jeśli ostatni wagonik wyzerujemy - musimy zmniejszyć size, ale nie jak był tylko 1 wagonik
    if (var[x].size > 1 && var[x].cart[var[x].size - 1] == 0) {
        var[x].size--;
        var[x].cart = realloc(var[x].cart, (size_t) var[x].size * sizeof(Variable));
    }
}

void VarAdd(Variable *var, int x, int y) {
    int rest = 0;
    int result;

    for (int i = 0; i < var[y].size; i++) {
        if (var[x].size == i) {
            VarExtend(var, x);
            var[x].cart[i] = 0;
        }

        result = var[x].cart[i] + var[y].cart[i] + rest;

        if (result < BASE) {
            var[x].cart[i] = result;
            rest = 0;
        }
        else {
            var[x].cart[i] = result % BASE;
            rest = 1;
        }
    }

    for (int i = var[y].size; rest == 1; i++) {
        if (var[x].size == i) {
            VarExtend(var, x);
            var[x].cart[i] = 0;
        }

        result = var[x].cart[i] + rest;

        if (result < BASE) {
            var[x].cart[i] = result;
            rest = 0;
        }
        else {
            var[x].cart[i] = result % BASE;
        }
    }
}
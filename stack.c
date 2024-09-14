#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

 void createStack(Stack* stack) {
    stack->top = NULL;
}

 void dbcreateStack(dbStack* dbstack) {
     dbstack->top = NULL;
 }

void pushStack(Stack* stack, char chData, int inData) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->chData = chData;
    tmp->inData = inData;
    tmp->next = stack->top;
    stack->top = tmp;
}

void dbpushStack(dbStack* dbstack, char chData, double dbData) {
    dbNode* tmp = (dbNode*)malloc(sizeof(dbNode));
    tmp->chData = chData;
    tmp->dbData = dbData;
    tmp->next = dbstack->top;
    dbstack->top = tmp;
}

double dbpopStack(dbStack* dbstack) {
    if (dbisemptyStack(dbstack)) {
        return 0;
    }
    dbNode* tmp = dbstack->top;
    double topData = tmp->dbData;
    dbstack->top = dbstack->top->next;
    free(tmp);
    return topData;
}

char chpopStack(Stack* stack) {
    if (isemptyStack(stack)) {
        return 0;
    }
    Node* tmp = stack->top;
    char topData = tmp->chData;
    stack->top = stack->top->next;
    free(tmp);
    return topData;
}

char topStack(Stack* stack) {
    if (isemptyStack(stack)) {
        return 0;
    }
    return stack->top->chData;
}

int isemptyStack(Stack* stack) {
    return (stack->top == NULL);
}

int dbisemptyStack(dbStack* dbstack) {
    return (dbstack->top == NULL);
}

void destroyStack(Stack* stack) {
    Node* tmp = stack->top;
    while (tmp != NULL) {
        Node* next = tmp->next;
        free(tmp);
        tmp = next;
    }
    stack->top = NULL;
}

void dbdestroyStack(dbStack* dbstack) {
    dbNode* tmp = dbstack->top;
    while (tmp != NULL) {
        dbNode* next = tmp->next;
        free(tmp);
        tmp = next;
    }
    dbstack->top = NULL;
}


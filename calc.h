#include "queue.h"
#include <stdbool.h>

bool Operator(char inf);
bool Operand(int inf);
int matchOper(Queue* infQ);
bool matchParen(Queue* infQ);
int emptyParen(Queue* infQ);
int unaryopt(Queue* infQ);
int priority(char opt);
Queue InToPost(Queue* infQ);
void calcPostfix(Queue* postQ);

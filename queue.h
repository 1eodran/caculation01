#include "stack.h"

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

void createQ(Queue* queue);
void enQ(Queue* queue, char opt, int opd);
int indeQ(Queue* queue);
char chdeQ(Queue* queue);
char frontQ(Queue* queue);
int isemptyQ(Queue* queue);
void destroyQ(Queue* queue);

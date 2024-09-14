typedef struct Node_ {
    char chData;
    int inData;
    struct Node_* next;
}Node;

typedef struct dbNode_ {
    char chData;
    double dbData;
    struct dbNode_* next;
}dbNode;

typedef struct Stack {
    Node* top;
} Stack;

typedef struct dbStack {
   dbNode* top;
} dbStack;

void createStack(Stack* stack);
void dbcreateStack(dbStack* dbstack);
void pushStack(Stack* stack, char chData, int inData);
void dbpushStack(dbStack* dbstack, char chData, double dbData);
double dbpopStack(dbStack* dbstack);
char chpopStack(Stack* stack);
char topStack(Stack* stack);
int isemptyStack(Stack* stack);
int dbisemptyStack(dbStack* dbstack);
void destroyStack(Stack* stack);
void dbdestroyStack(dbStack* dbstack);

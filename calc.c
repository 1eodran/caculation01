#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "calc.h"

// ����������
bool Operator(char inf)
{
    return (inf == '+' || inf == '-' || inf == '*' || inf == '/' || inf == '%' || inf == '^');
}

// �ǿ�����
bool Operand(int inf)
{
    return(inf >= 0 && inf <= 9);
}

//������,�ǿ�����,��ȣ�� ������ ��������
int matchOper(Queue* infQ) {
    Node* tmp = infQ->front;
    char opt;
    int opd;
    int bo = 0;
    while (tmp != NULL)
    {
        opt = tmp->chData;
        opd = tmp->inData;
        if (opt == 0 || (Operator(opt) && opd == 0) || opt == '(' || opt == ')') //�ǿ�����, ������, ��ȣ, ��ĭ�϶� true
        {
        }
        else
        {
            bo += 1;
        }
        tmp = tmp->next;
    }
    return bo;
}

//��ȣ�ְ˻�
bool matchParen(Queue* infQ) {
    Stack stack;
    createStack(&stack);
    Node* tmp = infQ->front;
    char chData;
    while (tmp != NULL) {
        chData = tmp->chData;
        if (chData == '(') {
            pushStack(&stack, chData, 0);
        }
        else if (chData == ')') {
            if (isemptyStack(&stack)) {
                destroyStack(&stack);
                return false;
            }
            chpopStack(&stack);
        }
        tmp = tmp->next;
    }

    bool result = isemptyStack(&stack); // �������� ������ ��������� true
    destroyStack(&stack);
    return result;
}

//���ȣ�϶�
int emptyParen(Queue* infQ)
{
    Node* tmp = infQ->front;
    Node* tmp2 = tmp->next;
    char chData, chData2;
    int bo = 1;
    while (tmp2 != NULL) 
    {
        chData = tmp->chData;
        chData2 = tmp2->chData;
        if (chData == '('&& chData2 == ')')
        {
             bo = 0;
        }
        tmp = tmp->next;
        tmp2 = tmp2->next;
    }
    return bo;
}

//���׿������϶� ����
int unaryopt(Queue* infQ)
{
    Node* tmp = infQ->front;
    int opt = 0;
    int opd = 0;
    int inData;
    char chData;
    while (tmp != NULL)
    {
        inData = tmp->inData;
        chData = tmp->chData;
        if (chData == 0) //�ǿ������϶�
        {
            opd += 1;
        }
        else if (Operator(chData) && inData == 0) //�������϶�
        {
            opt += 1;
        }
        tmp = tmp->next;
    }

    if (opt >= opd)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
  
// �������� �켱����
int priority(char opt)
{
    if (opt == '+' || opt == '-')
        return 1;
    else if (opt == '*' || opt == '/' || opt == '%')
        return 2;
    else if (opt == '^')
        return 3;
    else
        return 0;
}

// infix->postfix �Լ�
Queue InToPost(Queue* infixQ) {
    Stack charStack;
    createStack(&charStack);
    Queue postQ;
    createQ(&postQ);
    Node* tmp = infixQ->front;
    char opt;
    int opd;
    char popOpt;

    while (tmp != NULL)
    {
        opt = tmp->chData;
        opd = tmp->inData;
        if (opt == 0) //postq�� �ǿ����� �ֱ�
        {
            enQ(&postQ, 0, opd);
        }
        else if (opt == '(')  //stack�� ��ȣ�� ������ �ֱ�, �켱�����ڷ� postq�� �ֱ�
        {
            pushStack(&charStack, opt, 0);
        }
        else if (opt == ')')
        {
            while (!isemptyStack(&charStack) && topStack(&charStack) != '(') {
                popOpt = chpopStack(&charStack);
                enQ(&postQ, popOpt, 0);
            }

            if (!isemptyStack(&charStack) && topStack(&charStack) == '(') {
                chpopStack(&charStack); // '(' pop
            }
        }
        else if(Operator(opt)&& opd == 0) //�������� ��
        {
            while (!isemptyStack(&charStack) && priority(opt) <= priority(topStack(&charStack)))
            {
                popOpt = chpopStack(&charStack);
                enQ(&postQ, popOpt, 0);
            }
            pushStack(&charStack, opt, 0);
        }
        tmp = tmp->next;
    }

    while (!isemptyStack(&charStack)) //���� stack�� �ִ°� ���� postQ�� enQ
    {
        popOpt = chpopStack(&charStack);
        enQ(&postQ, popOpt, 0);
    }

    destroyStack(&charStack);
    return postQ;
}

// postfix�� ���� �۵�
void calcPostfix(Queue* postQ)
{
    dbStack opdStack;
    dbcreateStack(&opdStack);
    Node* tmp = postQ->front;
    char opt;
    int opd;
    double opd2, opd1;
    char zero = 't';
    double calc;
    double result;
    int in;

    while (tmp!=NULL)
    {
        opt = tmp->chData;
        opd = tmp->inData;

        if (opt == 0) //�ǿ������϶�
        {
            dbpushStack(&opdStack, 0, (double)opd);
        }
        else if (Operator(opt) && opd == 0) //�������϶�
        {
            opd2 = dbpopStack(&opdStack);
            opd1 = dbpopStack(&opdStack);
            switch (opt) 
            {
                case '+':
                    calc = opd1 + opd2;
                    break;
                case '-':
                    calc = opd1 - opd2;
                    break;
                case '*':
                    calc = opd1 * opd2;
                    break;
                case '/':
                    if (opd2 == 0) {
                        zero = 'f';
                        printf("Error! : Invalid expression (division by zero)\n");
                        dbdestroyStack(&opdStack);
                        return;
                    }
                    calc = opd1 / opd2;
                    break;
                case '%':
                    if (opd2 == 0) {
                        zero = 'f';
                        printf("Error! : Invalid expression (modulo by zero)\n");
                        dbdestroyStack(&opdStack);
                        return;
                    }
                    calc = (int)opd1 % (int)opd2;
                    break;
                case '^':
                    calc = pow(opd1, opd2);
                    break;
            }
            dbpushStack(&opdStack, 0, calc);
        }
        tmp = tmp->next;
    }

    result = dbpopStack(&opdStack);
    in = (int)result;
    if (zero == 't'&&in!=result) //���� ������ �� result �ȳ�����
    {
        printf("result: %.1lf\n", result);
    }
    else if (zero == 't' && in == result)
    {
        printf("result: %d\n", (int)result);
    }

    dbdestroyStack(&opdStack);
}

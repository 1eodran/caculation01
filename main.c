#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

int main() {
    char infix;
    Queue infixQ;
    createQ(&infixQ);
    int tmp;
   
    while (1)
    {
        printf(">>");
        while (1) //�Է¸�
        {
            infix = getchar();
            if (Operand(infix - 48))
            {
                if (infixQ.front == NULL) //ó�� �ǿ����� �Է�
                {
                    tmp = infix - 48;
                    enQ(&infixQ, 0, tmp);
                }
                else if (infixQ.rear->chData == 0 ) //���ڸ� �̻�(���� �ǿ����� �Է�)
                {
                    tmp = (infixQ.rear->inData) * 10 + (infix - 48);
                    infixQ.rear->inData = tmp;
                }
                else if (infixQ.front != NULL)//������ �Է�
                {
                    tmp = infix - 48;
                    enQ(&infixQ, 0, tmp);
                }
            }
            else if (Operator(infix)) // ������
            {
                enQ(&infixQ, infix, 0);
            }
            else if (infix == '('|| infix == ')') //��ȣ��
            {
                enQ(&infixQ, infix, 0);
            }
            else //���� �Էµ� ���
            {
                if (infixQ.front == NULL && infix == '\n') //enter�϶�
                {
                    printf("[enter]\nClosed");
                    return 0;
                }

                if (infix == '\n') break; //���� '\n' ������ �ȵ�

                if (infix != ' ') // ' ' ������ �ȵ�
                {
                    enQ(&infixQ, infix, 0);
                }
                
            }
        }

        if (matchOper(&infixQ) > 0) //�߸��� �����϶�
        {
            printf("Error! : Invalid character input\n");
            destroyQ(&infixQ);
            continue;
        }

        if (!matchParen(&infixQ)) //��ȣ�� �ȸ����� 
        {
            printf("Error! : Mismatched parentheses input\n");
            destroyQ(&infixQ);
            continue;
        }

        if (emptyParen(&infixQ) == 0) //���ȣ�϶�
        {
            printf("Error! : IsEmpty parentheses\n");
            destroyQ(&infixQ);
            continue;
        }

        if (unaryopt(&infixQ) == 0) //���׿������϶�
        {
            printf("Error! : Is Unary Operator\n");
            destroyQ(&infixQ);
            continue;
        }
     
        //�Է�, �����˻� ��
        Queue postQ = InToPost(&infixQ);
        destroyQ(&infixQ);
        calcPostfix(&postQ);
        destroyQ(&postQ);

    }

    return 0;
}

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
        while (1) //입력만
        {
            infix = getchar();
            if (Operand(infix - 48))
            {
                if (infixQ.front == NULL) //처음 피연산자 입력
                {
                    tmp = infix - 48;
                    enQ(&infixQ, 0, tmp);
                }
                else if (infixQ.rear->chData == 0 ) //두자리 이상(연속 피연산자 입력)
                {
                    tmp = (infixQ.rear->inData) * 10 + (infix - 48);
                    infixQ.rear->inData = tmp;
                }
                else if (infixQ.front != NULL)//연산자 입력
                {
                    tmp = infix - 48;
                    enQ(&infixQ, 0, tmp);
                }
            }
            else if (Operator(infix)) // 연산자
            {
                enQ(&infixQ, infix, 0);
            }
            else if (infix == '('|| infix == ')') //괄호쌍
            {
                enQ(&infixQ, infix, 0);
            }
            else //문자 입력될 경우
            {
                if (infixQ.front == NULL && infix == '\n') //enter일때
                {
                    printf("[enter]\nClosed");
                    return 0;
                }

                if (infix == '\n') break; //끝에 '\n' 받으면 안됨

                if (infix != ' ') // ' ' 받으면 안됨
                {
                    enQ(&infixQ, infix, 0);
                }
                
            }
        }

        if (matchOper(&infixQ) > 0) //잘못된 문자일때
        {
            printf("Error! : Invalid character input\n");
            destroyQ(&infixQ);
            continue;
        }

        if (!matchParen(&infixQ)) //괄호쌍 안맞을때 
        {
            printf("Error! : Mismatched parentheses input\n");
            destroyQ(&infixQ);
            continue;
        }

        if (emptyParen(&infixQ) == 0) //빈괄호일때
        {
            printf("Error! : IsEmpty parentheses\n");
            destroyQ(&infixQ);
            continue;
        }

        if (unaryopt(&infixQ) == 0) //단항연산자일때
        {
            printf("Error! : Is Unary Operator\n");
            destroyQ(&infixQ);
            continue;
        }
     
        //입력, 오류검사 끝
        Queue postQ = InToPost(&infixQ);
        destroyQ(&infixQ);
        calcPostfix(&postQ);
        destroyQ(&postQ);

    }

    return 0;
}

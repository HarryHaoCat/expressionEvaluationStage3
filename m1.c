/*************************************************************************
	> File Name: m.c
	> Author: HarryHao
	> Mail: 954487858@qq.com 
	> Created Time: 2018年08月06日 星期一 21时00分06秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "expressionEvaluation.h"
#define ExpressionLen  30 
#define properTestNumbers 100
#define infixLength 100

int main(){
	char testChar[43] = {'+', ' ', '(', '-', ' ', '*', ')', '/',' ', '(', ')', ' ','+', ' ', '(', '-', ' ', ')', '*', '/',' ', '(', ')', ' ','0', '1',' ', '(', '2', ' ', '3', '4', ' ', '5', ')', '6', ' ', '(','7', '8', ' ', ')', '9'};
	char testExpression[ExpressionLen];
	char rightExpression[properTestNumbers][ExpressionLen] = {};
	srand(100);
	int i = 0;
	char postfixExpression[infixLength];
	while(i<properTestNumbers){

		for(int j = 0; j < ExpressionLen; j++)
        	testExpression[j] = '\0'; 

		for(int j = 0; j < ExpressionLen - 1; j++){
			testExpression[j] = testChar[rand() % 43];
		}

		for (int i = 0; i < 100; i++)   	                               
			postfixExpression[i] = '\0';

        printf("The infix expression:%s\n", testExpression);

        if (infixToPostfix(testExpression, postfixExpression) == 1){

        	int k = 0;
        	while(k<ExpressionLen)
        	{
        	
        		rightExpression[i][k] = testExpression[k];
        		k++;
        	}
        	i++;
        
        }
		printf("\n");
	}   

	i = 0;
    double value;
	printf("---------------------***   Test %d    ***------------------------\n\n", i + 1);
	for(int j = 0; j < properTestNumbers; j++)
	{
		printf("The infix expression:%s\n", rightExpression[j]);
		if (infixToPostfix(rightExpression[j], postfixExpression) == 1){
            printf("The postfix expression:%s\n", postfixExpression);
            if (computeValueFromPostfix(postfixExpression, &value) == 1)
                printf("The value of the expression:%g\n\n", value);
            else
                printf("Sorry, we can't evaluate such a postfix expression.\n");
        }
        else{
            printf("Sorry, we can't turn such an infix expression to a postfix expression.\n");
        }

	}
	printf("-----***   End of tests for IMPROPER prefix expressions.    ***-----\n\n\n");
	return 0;
}


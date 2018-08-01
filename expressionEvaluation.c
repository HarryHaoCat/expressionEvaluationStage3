/*************************************************************************
> File Name: expressionEvaluation.c
> Author: HaoJie
> Mail: 954487858@qq.com
> Created Time: 2018年07月16日  星期一 16h22m3s
************************************************************************/

#include <stdio.h>
#include "sequentialStack.h"
#include <ctype.h>

//操作符优先级计算函数
int getNumOfExpression(char* postfixExpression, double numberArray[]);
int Isproper(char *postfixExpression, double numberArray[], int lenArr);
int Priority(char c)
{
	switch (c)
	{
	case '(': return 0;
	case '+': return 1;
	case '-': return 1;
	case '*': return 2;
	case '/': return 2;
	default:  return 0;
	}
}

//Pow幂函数
double Pow(double i, int j)
{
	int k = 0;
	double result = i;
	if(j > 1)
	{
		for(k = 0; k < j - 1; k++)
		{
			result = result * i;
		}
	}
	else if(j == 1) result = i;
	else if(j == 0) result = 1;

	return result;
}
//得到第一个操作符若为'+'或者'-',并且后面跟数,则返回值1
int getFirstOperator(char* infixExpression)
{
	int index = 0;
	while (infixExpression[index] != '\0')
	{

		if (isdigit(infixExpression[index]))
			return 0;

		else if (infixExpression[index] == ' ')
		{
			index++;
			continue;
		}
		else if (infixExpression[index] == '('  || infixExpression[index] == ')')
		{
			index++;
			continue;
		}
		else if (infixExpression[index] == '+' || infixExpression[index] == '-')
		{
			int i = index + 1;
			if(infixExpression[i] == ' ')
				return 0;
			else if(infixExpression[i] == '+' || infixExpression[i] == '-')
				return 0;		
			else return 1;
		}
		else
			return 0;
	}
	//否则返回0
	return 1;
}

int illegalSpace(char* infixExpression) //判断非法的空格
{
	int index = 0;
	while (infixExpression[index] != '\0')
	{
		if(infixExpression[index] == '-' || infixExpression[index] == '+')
		{
			int temp = index;
			while(infixExpression[--temp] == ' ' && temp > 0);
			if(infixExpression[temp] == ' ' || index == 0)
			{
				if(infixExpression[index +1 ] == ' ')
				{
					return 1;
				}
			}

		}
		index++;
	}
	return 0;

}

//中缀转后缀
int infixToPostfix(char* infixExpression, char postfixExpression[])
{
	//初始化后缀表达式数组
	for (int i = 0; i < 100; i++)
		postfixExpression[i] = '\0';
	SqStack* s = (SqStack*)malloc(sizeof(SqStack));
	ElemType e;
	InitStack(s);
	int index = 0;
	int numIndex = 0;
	int proper = 0;
	while (infixExpression[index] != '\0')
	{
		//如果是操作数
		if (infixExpression[index] != '+' && infixExpression[index] != '-' && infixExpression[index] != '*' 
			&& infixExpression[index] != '/' && infixExpression[index] != '(' && infixExpression[index] != ')')
		{
			if(!(postfixExpression[numIndex - 1] == ' ' && infixExpression[index] == ' '))
				//continue;
				postfixExpression[numIndex++] = infixExpression[index];
		}
		//如果是左括号		
		else if (infixExpression[index] == '(')
		{
			if(!Push(s, infixExpression[index]))
			{
				printf("The stack is full!\n");
				DestroyStack(s);
				return 0;
			}
		}
		//如果是运算符
		else if (infixExpression[index] == '+' || infixExpression[index] == '-' || infixExpression[index] == '*' 
			|| infixExpression[index] == '/' || infixExpression[index] == ')')
		{

			//若栈为空,直接将运算符进栈
			if (StackEmpty(s))
			{
				int i = index - 1;
				while(infixExpression[i] == ' ' && i > 0)
				{
					i--;
				}
				if(infixExpression[index] == '+' && !isdigit(infixExpression[i]))
				{
					if(!Push(s, '@'))
					{
						printf("The stack is full!\n");
						DestroyStack(s);
						return 0;
					}				
				}
				else if(infixExpression[index] == '-' && !isdigit(infixExpression[i]))
				{
					if(!Push(s, '$'))
					{
						printf("The stack is full!\n");
						DestroyStack(s);
						return 0;
					}					
				}
				else
				{
					if(!Push(s, infixExpression[index]))
					{
						printf("The stack is full!\n");
						DestroyStack(s);
						return 0;
					}					
				}

				postfixExpression[numIndex++] = ' ';

			}
			//否则栈不为空
			else
			{
				//若为右括号,将栈中左括号之前的符号全部弹出
				if (infixExpression[index] == ')')
				{
					postfixExpression[numIndex++] = ' ';
					GetTop(s, &e);
       				while (e != '(')
					{
						Pop(s, &postfixExpression[numIndex++]);
						GetTop(s, &e);
					}
					Pop(s, &e);  //弹出左括号
				}
				//如果不为左括号,判断符号的优先级
				else
				{
					//优先级较大的符号直接进栈
					GetTop(s, &e);
					if (Priority(infixExpression[index]) > Priority(e))
					{
						if (infixExpression[index] == '+' || infixExpression[index] == '-')
						{

							int i = index - 1;
							if (infixExpression[i] == '(' && infixExpression[index] == '+')
								//postfixExpression[numIndex++] = '@';
							{
								postfixExpression[numIndex++] = ' ';
								if(!Push(s, '@'))
								{
									printf("The stack is full!\n");
									DestroyStack(s);
									return 0;
								}
							}
							else if(infixExpression[i] == '(' && infixExpression[index] == '-') 
							{
								postfixExpression[numIndex++] = ' ';
								if(!Push(s, '$'))
								{
									printf("The stack is full!\n");
									DestroyStack(s);
									return 0;
								}
							}
							//else if(i == 0 && !isdigit(infixExpression[i]))

							else
							{
								postfixExpression[numIndex++] = ' ';
								if(!Push(s, infixExpression[index]))
								{
									printf("The stack is full!\n");
									DestroyStack(s);
									return 0;
								}
							}
															//postfixExpression[numIndex++] = '$';
						}
						else
						{
							postfixExpression[numIndex++] = ' ';
							if(!Push(s, infixExpression[index]))
							{
								printf("The stack is full!\n");
								DestroyStack(s);
								return 0;
							}
						}
					}
					//否则将栈顶元素打出,这个元素入栈
					else if (Priority(infixExpression[index]) <= Priority(e))
					{
						Pop(s, &postfixExpression[numIndex++]);
						if(!Push(s, infixExpression[index]))
						{
							printf("The stack is full!\n");
							DestroyStack(s);
							return 0;
						}						
						index++;
						continue;   //重新开始一次循环
					}
				}
			}

		}
		index++;
	}
	while (!StackEmpty(s))
	{
		Pop(s, &postfixExpression[numIndex++]);
	}
	postfixExpression[numIndex++] = ' ';   //在后缀表达式最后加一个空格
	double numberArray[100] = { 0.0 };
	int lenArr = getNumOfExpression(postfixExpression, numberArray);
	proper = Isproper(infixExpression, numberArray, lenArr);
	return proper;

}

//计算后缀表达式
int computeValueFromPostfix(char* postfixExpression, double *value)
{
	double numberArray[100] = { 0.0 };
	int numIndex = 0;
	int number = getNumOfExpression(postfixExpression, numberArray);
	SqStack1* ds = (SqStack1*)malloc(sizeof(SqStack1));
	InitStack1(ds);
	while (numIndex <= number)
	{
		double num1, num2 = 0.0;

		if (numberArray[numIndex] == -1.0 || numberArray[numIndex] == -2.0 || numberArray[numIndex] == -3.0 
			|| numberArray[numIndex] == -4.0)
		{
			Pop1(ds,&num1);
			Pop1(ds, &num2);

			switch ((int)numberArray[numIndex])
			{
			case -1:
				Push1(ds, num2 + num1);
				break;
			case -2:
				Push1(ds, num2 - num1);
				break;
			case -3:
				Push1(ds, num2 * num1);
				break;
			case -4:
				if(num1 != 0)
					Push1(ds, (double)num2 / num1);
				else return 0;
				break;
			default: break;
			}
		}
		else if(numberArray[numIndex] == -5.0 || numberArray[numIndex] == -6.0 )
		{
			Pop1(ds, &num1);
			switch((int)numberArray[numIndex])
			{
				case -5:
					Push1(ds, num1);
					break;
				case -6:
					Push1(ds, -num1);
					break;
				default: break;

			}
		}
		else
		{
			Push1(ds, numberArray[numIndex]);
		}
		numIndex++;

	}
	//将数组清空	
	for (int i = 0; i < 100; i++)
		postfixExpression[i] = '\0';
	Pop1(ds, value);
	//printf("sizeof value: %d\n", sizeof(*value));
	return 1;
}

//得到后缀表达式的double型的操作数
int getNumOfExpression(char* postfixExpression, double numberArray[])
{
	SqStack1* ds = (SqStack1*)malloc(sizeof(SqStack1));
	InitStack1(ds);
	ElemType1 e;
	int postIndex = 0;
	int numArrayIndex = 0;
	while (postfixExpression[postIndex] != '\0')
	{
		if (postfixExpression[postIndex] == '+' || postfixExpression[postIndex] == '-' || postfixExpression[postIndex] == '*' 
			|| postfixExpression[postIndex] == '/' || postfixExpression[postIndex] == '@' || postfixExpression[postIndex] == '$'
			|| postfixExpression[postIndex] == ' ')
		{
			if (!StackEmpty1(ds))
			{
				int len = ds->top;
				for (int j = 0; j < len; j++)
				{
					Pop1(ds,&e);
					numberArray[numArrayIndex] += Pow(10.0, j) * e;
					e = 0.0;
				}
				numArrayIndex++;
			}
			switch (postfixExpression[postIndex])
			{
			case '+': numberArray[numArrayIndex++] = -1.0; break;
			case '-': numberArray[numArrayIndex++] = -2.0; break;
			case '*': numberArray[numArrayIndex++] = -3.0; break;
			case '/': numberArray[numArrayIndex++] = -4.0; break;
			case '@': numberArray[numArrayIndex++] = -5.0; break;
			case '$': numberArray[numArrayIndex++] = -6.0; break;
			default:  break;
			}
		}
		else
		{
			Push1(ds, (double)(postfixExpression[postIndex] - '0'));
		}

		postIndex++;
	}
	return numArrayIndex - 1;
}

//判断表达式的合法性
int Isproper(char *infixExpression, double numberArray[], int lenArr)
{
	int index = 0;
	int i = 0;
	SqStack* brace = (SqStack*)malloc(sizeof(SqStack));
	InitStack(brace);
	ElemType e;
	int operator = 0;
	int Digit = 0;
	int blank = 0;
	int bracenum = 0;

	//进行一次遍历
	while (infixExpression[index] != '\0')
	{
        //符号合法性的判断
		if(!(isdigit(infixExpression[index]) || infixExpression[index] == '+' || infixExpression[index] == '+' 
			|| infixExpression[index] == '-' || infixExpression[index] == '*'|| infixExpression[index] == '/'
			|| infixExpression[index] == ' ' || infixExpression[index] == '('|| infixExpression[index] == ')'
		    ))
		{
			printf("Error!!! There are illegal characters in your expression!\n");
			return 0;
		}
		//使用char型栈进行括号合法性的判断,遇到左括号就进栈,遇到右括号若不为空就出栈
		else if (infixExpression[index] == '(')
		{
			bracenum++;
			Push(brace, infixExpression[index]);
		}
		else if (infixExpression[index] == ')')
		{
			if (!StackEmpty(brace))
			{
				bracenum++;
				Pop(brace, &e);
			}
			//遇到右括号,若此时栈为空,则说明之前没有左括号		
			else {
				printf("Error!!! There are improper braces in your expression!\n");
				return 0;

			}
		}
		//统计空格的个数
		else if (infixExpression[index] == ' ')
			blank++;

		index++;

	}

	//对括号栈的合法性进行判断	
	if (!StackEmpty(brace))
	{
		printf("Error!!! There are improper braces in your expression!\n");
		return 0;
	}

	//对全空的判断	
	if (blank == index)
	{
		printf("Error!!! This is an empty expression!\n");
		blank = 0;
		return 0;
	}

	while(i <= lenArr)
	{
		if (numberArray[i] == -1.0 || numberArray[i] == -2.0 || numberArray[i] == -3.0 || numberArray[i] == -4.0 
			||numberArray[i] == -5.0 || numberArray[i] == -6.0)
		{
			operator++;
		}
		else if (numberArray[i] != ' ')
		{
			Digit++;
		}

		i++;
	}
	//对运算符和运算数进行个数进行判断,正确的表达式运算数总比运算符多一个
	if (operator != Digit - 1)
	{
		if (operator == 0)
		{
			printf("Error!!! There are illegal spaces in your expression!\n");
			return 0;
		}
		else if(Digit == 0)
		{
			printf("Error!!! There is no operand in your expression!\n");
			return 0;		}
		else if (getFirstOperator(infixExpression))
		{
			return 1;
		}
		else if(illegalSpace(infixExpression))
		{
			printf("Error!!! There are illegal spaces in your expression  2!\n");
			return 0;	
		}
		else if (StackEmpty(brace) && bracenum)
			return 1;

		else
		{
			printf("Error!!! There are insufficient operands in your expression!\n");
			return 0;
		}
		operator = Digit = 0;
	}
	//正常情况返回值1
	return 1;
}


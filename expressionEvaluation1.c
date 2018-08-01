/*************************************************************************
> File Name: expressionEvaluation1.c
> Author: HaoJie
> Mail: 954487858@qq.com
> Created Time: 2018年07月16日  星期一 16h22m3s
************************************************************************/
#include <stdio.h>
#include "sequentialStack.h"
#include <ctype.h>
int IsUnary(char* infixExpression);   //单元运算符
int Priority(char c);                 //优先级判断
char previous(char* infixExpression, int index);      //前继非空字符
char next(char* infixExpression, int index);           //后继非空字符

int infixToPostfix(char* infixExpression, char postfixExpression[])   //中缀转后缀
{
	for (int i = 0; i < 100; i++)   	                              //初始化后缀表达式数组
		postfixExpression[i] = '\0';
	SqStack* s = (SqStack*)malloc(sizeof(SqStack));
	ElemType e;
	InitStack(s);
	int numIndex = 0, index = 0;
	int operand = 0, blank = 0, leftBrace = 0, rightBrace = 0;
	while(infixExpression[index] != '\0')
	{
		if(!(isdigit(infixExpression[index]) || infixExpression[index] == '+' || infixExpression[index] == ' '  //符号合法性的判断
			|| infixExpression[index] == '-' || infixExpression[index] == '*'|| infixExpression[index] == '/'
			|| infixExpression[index] == '(' || infixExpression[index] == ')'))
		{
			printf("Illegal character \'%c\' in the expression\n", infixExpression[index]);
			return 0;
		}
		else if(infixExpression[index] == ' ')      //空格直接跳过
		{
			blank++;
		}
		else if(isdigit(infixExpression[index]))   //操作数
		{
			if(infixExpression[index + 1] == ' ' && isdigit(next(infixExpression, index)))
			{	
				printf("Too many operands\n");
				return 0;
			}
			else
			{
				postfixExpression[numIndex++] = infixExpression[index];
				if(!isdigit(infixExpression[index + 1]))
				{
					postfixExpression[numIndex++] = '#';    //每一个操作数以后加一个'#'
					operand++;
				}			
			}

		}
		else if(infixExpression[index] == '+' || infixExpression[index] == '-' || infixExpression[index] == '*'  //操作符
			|| infixExpression[index] == '/' || infixExpression[index] == '('|| infixExpression[index] == ')')	
		{
			if(infixExpression[index] == '+' || infixExpression[index] == '-')   //处理单元非法运算符
			{
				if(previous(infixExpression,index) == ' ' || index == 0)
				{
					if(infixExpression[index +1 ] == ' ')
					{
						printf("A space follows a unary \'%c\'\n", infixExpression[index]);
						return 0;
					}
				}
				char nc = next(infixExpression, index);   //得到后继非空字符
				if(nc == '\0')
				{
					printf("operator \'%c\' without operand in expression\n", infixExpression[index]);
					return 0;
				}
				if(infixExpression[index + 1 ] == '+' || infixExpression[index + 1 ] == '-' )
				{
					printf("Operator \'%c\' immediately follows another operator \'%c\' in the expression\n", infixExpression[index], infixExpression[index + 1]);
					return 0;
				}
				if(IsUnary(infixExpression))
				{
					printf("A space follows a unary \'%c\'\n", infixExpression[index]);
					return 0;
				}
			}
			if(StackEmpty(s))
			{
				char pc = previous(infixExpression, index);
				if((infixExpression[index] == '+' || infixExpression[index] == '-') && !isdigit(pc))    //前继非空为左括号或者空格则判断为单元
				{
					if(!Push(s, infixExpression[index] == '+'? '@':'$'))
					{
						printf("The stack is full!\n");
						DestroyStack(s);
						return 0;
					}				
				}
				else
				{
					if (infixExpression[index] == '(')
						leftBrace++;
					else if(infixExpression[index] == ')')
					{
						printf("No matched \'(\' before \')\'\n");
						return 0;
					}
					if(!Push(s, infixExpression[index]))
					{
						printf("The stack is full!\n");
						DestroyStack(s);
						return 0;
					}					
				}
			}
			else if (infixExpression[index] == '(')  //如果是左括号直接入站	
			{
				if(!Push(s, infixExpression[index]))
				{
					printf("The stack is full!\n");
					DestroyStack(s);
					return 0;
				}
				leftBrace++;
			}			
			else //此时栈不为空也不为左括号    ')' '+' '-' '*' '/'
			{
				if (infixExpression[index] == ')')    //若为右括号,将栈中左括号之前的符号全部弹出
				{
					rightBrace++;
					GetTop(s, &e);
       				while (e != '(')
					{
						Pop(s, &postfixExpression[numIndex++]);
						GetTop(s, &e);
					}
					Pop(s, &e);  //弹出左括号
				}
				else       //判断优先级                     
				{
					GetTop(s, &e);  			//优先级较大的符号直接进栈
					if (Priority(infixExpression[index]) > Priority(e))
					{
						if (infixExpression[index] == '+' || infixExpression[index] == '-')
						{
							if (previous(infixExpression, index) == '(' && (infixExpression[index] == '+' || infixExpression[index] == '-') 
								&&isdigit(infixExpression[index + 1]))    // 作为单目运算处理
							{
								if(!Push(s, infixExpression[index] == '+'? '@':'$'))
								{
									printf("The stack is full!\n");
									DestroyStack(s);
									return 0;
								}
							}
							else   //普通运算符处理
							{
								if(!Push(s, infixExpression[index]))
								{
									printf("The stack is full!\n");
									DestroyStack(s);
									return 0;
								}
							}
						}
						else    //'*' '/'
						{
							char nc = next(infixExpression, index);   //得到后继非空字符
							if(nc == '\0' || nc == ')')
							{
								printf("Operator \'%c\' without operand in expression\n", infixExpression[index]);
								return 0;
							}							
							if(!Push(s, infixExpression[index]))
							{
								printf("The stack is full!\n");
								DestroyStack(s);
								return 0;
							}
						}
					}
					else if (Priority(infixExpression[index]) <= Priority(e))  		//否则将栈顶元素打出,这个元素入栈
					{
						char nc = next(infixExpression, index);   //得到后继非空字符
						if(nc == '\0')
						{
							printf("Operator \'%c\' without operand in expression\n", infixExpression[index]);
							return 0;
						}	
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
	while (!StackEmpty(s))     //剩下的全部出栈
	{ 
		Pop(s, &postfixExpression[numIndex++]);
	}
	if(leftBrace != rightBrace)
	{
		if(leftBrace < rightBrace)
			printf("No matched \'(\' before \')\'\n");
		else printf("No matched \')\' after \'(\'\n");
		return 0;
	}
	if(blank == index)
	{
		printf("The input is EMPTY\n");
		return 0; 
	}
	else return 1;
}
//计算后缀表达式
int computeValueFromPostfix(char* postfixExpression, double *value)
{
	int index = 0;
	SqStack1* Is = (SqStack1*)malloc(sizeof(SqStack1));
	InitStack1(Is);
	while(postfixExpression[index] != '\0')
	{
		if(isdigit(postfixExpression[index]))   //为数字
		{
			int temp = index + 1;
			double tempValue = 0;
			while(postfixExpression[temp] != '#')
			{
				tempValue = 10.0 * (postfixExpression[temp - 1] - '0');
				temp++;
				index++;
			}
			tempValue += (double)(postfixExpression[index] - '0');
			if(!Push1(Is, tempValue))
			{
				printf("The stack is full!\n");
				DestroyStack1(Is);
				return 0;
			}
			index++;
			continue;
		}
		else if(postfixExpression[index] == '#')   //为空格
		{
			index++;
			continue;
		}
		else if(postfixExpression[index] == '+' || postfixExpression[index] == '-' || postfixExpression[index] == '*'|| postfixExpression[index] == '/')   //否则为操作符
		{
			double num1 = 0.0, num2 = 0.0;
			Pop1(Is, &num1);
			Pop1(Is, &num2);
			switch(postfixExpression[index] - '0')
			{
				case ('+' - '0'): if(!Push1(Is, num2 + num1)){printf("The stack is full!!\n"); return 0;}break;
				case ('-' - '0'): if(!Push1(Is, num2 - num1)){printf("The stack is full!!\n"); return 0;}break;
				case ('*' - '0'): if(!Push1(Is, num2 * num1)){printf("The stack is full!!\n"); return 0;}break;
				case ('/' - '0'): if(num1 != 0) if(!Push1(Is, (double)num2 / num1)){printf("The stack is full!\n"); return 0;} break;
				default:break; 
			}
		}
		else if(postfixExpression[index] == '@' || postfixExpression[index] == '$')
		{
			double num1 = 0.0;
			Pop1(Is, &num1);
			switch(postfixExpression[index] - '0')
			{
				case ('@' - '0'): if(!Push1(Is, num1)){printf("The stack is full!!!\n"); return 0;}break;
				case ('$' - '0'): if(!Push1(Is, 0-num1)){printf("The stack is full!!!\n"); return 0;}break;
				default:break;
			}
		}
		index++;
	}
	for (int i = 0; i < 100; i++)
		postfixExpression[i] = '\0';
	Pop1(Is, value);
	return 1;
}
int IsUnary(char* infixExpression)   //单元运算符
{
	int index = 0, operator = 0, operand = 0;
	while(infixExpression[index] != '\0')
	{
		if(infixExpression[index] == '+' || infixExpression[index] == '-' || infixExpression[index] == '*' || infixExpression[index] == '/')
			operator++;
		else if(isdigit(infixExpression[index]))
			operand++;
		index++;
	}
	if(operand == 0 && operator != 0)
		return 1;
	return 0;
}
int Priority(char c)                 //优先级判断
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
char previous(char* infixExpression, int index)                       //前继非空字符
{
	int i= index;
	while(infixExpression[--i] == ' ' && i > 0);
	if(i == -1)
		return infixExpression[i + 1];
	else return infixExpression[i];                  // 返回的东西要是式一个非空的字符,要么表达式开始的空格
}
char next(char* infixExpression, int index)                           //后继非空字符
{
	int i= index;
	while(infixExpression[++i] == ' ' && infixExpression[i] != '\0');
	return infixExpression[i];                 // 返回的东西要是式一个非空的字符,要么返回值'\n'
}
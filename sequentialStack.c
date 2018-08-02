/*************************************************************************
> File Name: expressionEvaluation.c
> Author: HaoJie
> Mail: 954487858@qq.com
> Created Time: 2018年07月16日  星期一 16h22m3s
************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include "sequentialStack.h"


//char型栈的实现
void InitStack(SqStack *s) //建栈,第一个位置从0开始；
{
	s->top = 0;
}

void DestroyStack(SqStack *s)    //
{
	free(s);
}

int StackEmpty(SqStack *s)
{
	if(s->top == 0)
		return 1;
	else return 0;
}

int Push(SqStack *s, ElemType e)
{
	if(s->top == MaxSize)
	{
		//printf("The stack is full!\n");
		return 0;
	}
	else 
	{
		s->data[s->top++] = e;
		return 1;
	}
}

int Pop(SqStack *s, ElemType *e)
{
	if(s->top == 0)
	{
		//printf("The stack is empty!\n");
		return 0;
	}
	else 
	{
		*e = s->data[s->top-1];
		s->top--;
		return 1;
	}
}

int GetTop(SqStack *s, ElemType *e)
{
	if(s->top == 0)
	{
		//printf("The stack is empty!\n");
		return 0;
	}
	else 
	{
		*e = s->data[s->top-1];
		return 1;
	}
}
void display(SqStack *s)
{
	for(int i = s->top - 1; i > 0; i--)
	{
		printf("%c->", s->data[i]);
	}
	printf("%d\n", s->data[0]);
}

//double型栈的实现
void InitStack1(SqStack1 *s) //建栈,第一个位置从0开始；
{
	s->top = 0;
}

void DestroyStack1(SqStack1 *s)    //
{
	free(s);
}

int StackEmpty1(SqStack1 *s)
{
	if(s->top == 0)
		return 1;
	else return 0;
}

int Push1(SqStack1 *s, ElemType1 e)
{
	if(s->top == MaxSize)
	{
		//printf("The stack is full!\n");
		return 0;
	}
	else 
	{
		s->data[s->top++] = e;
		return 1;
	}
}

int Pop1(SqStack1 *s, ElemType1 *e)
{
	if(s->top == 0)
	{
		//printf("The stack is empty!\n");
		return 0;
	}
	else 
	{
		*e = s->data[s->top-1];
		s->top--;
		return 1;
	}
}

int GetTop1(SqStack1 *s, ElemType1 *e)
{
	if(s->top == 0)
	{
		//printf("The stack is empty!\n");
		return 0;
	}
	else 
	{
		*e = s->data[s->top-1];
		return 1;
	}
}
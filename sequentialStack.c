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

/*  Initialize the sequential stack
 */
void InitStack(SqStack *s) 
{
	if(s == NULL)  //If the pointer s points to NULL.
	{
		printf("<Error! This pointer is NULL>\n");
		return;
	}
	s->top = 0;
}

/*  Release the memory of the sequential stack
 */
void DestroyStack(SqStack *s)    
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return;
	}
	free(s);   //Free the pointer that points to the stack.
}

/*  Check if the stack is empty.
    Return 1 to indicate the stack is empty.
    Return 0 to indicate the stack is NOT empty.
 */
int StackEmpty(SqStack *s)
{	
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return 0;
	}
	if(s->top == 0)
		return 1;
	else return 0;
}

/*  If the stack is NOT full, push e into it and return 1 to indicate a successful push.
    If the stack is full, merely return 0 to indicate an unsuccessful push.
 */
int Push(SqStack *s, ElemType e)
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return 0;
	}
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

/*  If the stack is NOT empty, pop the top of the stack into e and return 1 to indicate a successful pop.
    If the stack is empty, merely return 0 to indicate an unsuccessful pop.
 */
int Pop(SqStack *s, ElemType *e)
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return 0;
	}
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

/*  If the stack is NOT empty, assign the top of the stack to e and return 1 to indicate a successful gettop.
    If the stack is empty, merely return 0 to indicate an unsuccessful gettop.
 */
int GetTop(SqStack *s, ElemType *e)
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return 0;
	}
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
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return;
	}
	for(int i = s->top - 1; i > 0; i--)
	{
		printf("%c->", s->data[i]);
	}
	printf("%d\n", s->data[0]);
}

/* Interfaces for the 2nd stack for double elements*/

//  Initialize the sequential stack

void InitStack1(SqStack1 *s) 
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return;
	}
	s->top = 0;
}

/*  Release the memory of the sequential stack
 */
void DestroyStack1(SqStack1 *s)   
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return;
	}
	free(s);
}

/*  Check if the stack is empty.
 Return 1 to indicate the stack is empty.
 Return 0 to indicate the stack is NOT empty.
 */
int StackEmpty1(SqStack1 *s)
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return 0;
	}
	if(s->top == 0)
		return 1;
	else return 0;
}
/*  If the stack is NOT full, push e into it and return 1 to indicate a successful push.
    If the stack is full, merely return 0 to indicate an unsuccessful push.
 */

int Push1(SqStack1 *s, ElemType1 e)
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return 0;
	}
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
/*  If the stack is NOT empty, pop the top of the stack into e and return 1 to indicate a successful pop.
    If the stack is empty, merely return 0 to indicate an unsuccessful pop.
 */
int Pop1(SqStack1 *s, ElemType1 *e)
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return 0;
	}
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
/*  If the stack is NOT empty, assign the top of the stack to e and return 1 to indicate a successful gettop.
    If the stack is empty, merely return 0 to indicate an unsuccessful gettop.
 */
int GetTop1(SqStack1 *s, ElemType1 *e)
{
	if(s == NULL)
	{
		printf("<Error! This pointer is NULL>\n");
		return 0;
	}
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
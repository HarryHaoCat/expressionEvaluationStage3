/*************************************************************************
> File Name: expressionEvaluation1.c
> Author: HaoJie
> Mail: 954487858@qq.com
> Created Time: 2018年08月6日  星期一 17h22m3s
************************************************************************/
#include <stdio.h>
#include "sequentialStack.h"
#include <ctype.h>
int isUnary(char* infixExpression);                   //Judge if some operator is an unary operator 
int Priority(char c);                                 //Calculate the priority value of the operators
char previous(char* infixExpression, int index);      //Get the first non_space character before the current character
char next(char* infixExpression, int index);          //Get the first non_space character after the current character
void printError(char* infixExpression, int index);

//Convert infix expression into postfix expression 
int infixToPostfix(char* infixExpression, char postfixExpression[]){   
	for (int i = 0; i < 100; i++)   	                               
		postfixExpression[i] = '\0';
	int braceNum = 0;
	SqStack* s = (SqStack*)malloc(sizeof(SqStack));
	ElemType e;
	InitStack(s);
	int numIndex = 0, index = 0;
	int operand = 0, blank = 0, leftBrace = 0, rightBrace = 0;
	while(infixExpression[index] != '\0'){
		/*
		  Judge whether the current character is illegal,
		  if the current character isn't '+', '-', '*', '/', ' ', '(', ')' or number '0'-'9', 
		  then print proper error information, and return 0.  
		*/
		if(!(isdigit(infixExpression[index]) || infixExpression[index] == '+' || infixExpression[index] == ' '  
			|| infixExpression[index] == '-' || infixExpression[index] == '*' || infixExpression[index] == '/'
			|| infixExpression[index] == '(' || infixExpression[index] == ')')){
			printError(infixExpression, index);
			printf("<Error! Illegal character \'%c\' in the expression>\n", infixExpression[index]);
			return 0;
		}
		//Count the number of spaces
		else if(infixExpression[index] == ' '){    
			blank++;
		}
		/*
		  If the current character is a digit, if so, judge whether the character lacks operator,
		  if it's a legal digit, put it into the array postfixExpression   
		*/
		else if(isdigit(infixExpression[index])){   	
			if(infixExpression[index + 1] == ' ' && isdigit(next(infixExpression, index))){	
				printError(infixExpression, index);
				printf("<Error! Too many operands>\n");
				return 0;
			}
			else{
				postfixExpression[numIndex++] = infixExpression[index];
				if(!isdigit(infixExpression[index + 1])){
					postfixExpression[numIndex++] = '#';
					operand++;
				}			
			}
		}
		//If the current character is operator, space or brace
		else if(infixExpression[index] == '+' || infixExpression[index] == '-' || infixExpression[index] == '*'  
			 || infixExpression[index] == '/' || infixExpression[index] == '(' || infixExpression[index] == ')'){
			/*Handle illegal unary operator '+' and '-'.
			  (1)A space follows an unary operator '+' or '-'.
			  (2)A brace ')' or ending mark '\0' follows an unary operator '+' or '-'.
			  (3)An operaor '+' or '-' follows an unary operator '+' or '-'.
			  (4)There is only one operator '+' or '-' in the expression.
			*/
			if(infixExpression[index] == '+'  || infixExpression[index] == '-'){ 
				if((previous(infixExpression,index) == ' ' || index == 0 || previous(infixExpression,index) == '(') && infixExpression[index + 1] == ' '){
					printError(infixExpression, index);
					printf("<Error! A space follows a unary \'%c\'>\n", infixExpression[index]);
					return 0;
				}
				else if(next(infixExpression, index) == '\0' || next(infixExpression, index) == ')'){
					printError(infixExpression, index);
					printf("<Error! Operator \'%c\' without operand in expression>\n", infixExpression[index]);
					return 0;
				}
				else if(next(infixExpression, index) == '+' || next(infixExpression, index) == '-' || next(infixExpression, index) == '*' || next(infixExpression, index) == '/'){
					printError(infixExpression, index);
					printf("<Error! Operator \'%c\'  follows another operator \'%c\' in the expression>\n", next(infixExpression, index), infixExpression[index]);
					return 0;
				}
				else if(isUnary(infixExpression)){
					printError(infixExpression, index);
					printf("<Error! A space follows a unary \'%c\'>\n", infixExpression[index]);
					return 0;
				}
			}
			/*
			  Handle illegal brace.
			  (1)There is a ')' before a '('.
			  (2)There is a digit before a '('.
			  (3)There is a ')' after a '('.
			*/
			else if(infixExpression[index] == '('){  
				braceNum++;
				if(previous(infixExpression, index) == ')'){
					printError(infixExpression, index);
					printf("<Error! No operator between \')\' and \'(\'>\n");
					return 0;
				}
				else if(index != 0 && isdigit(previous(infixExpression, index))){
					printError(infixExpression, index);
					printf("<Error! No operator between operand and \'(\'>\n");
					return 0;					
				}
				else if(next(infixExpression, index) == ')'){
						printError(infixExpression, index);
						printf("<Error! Nothing in the braces>\n");
						return 0;		
				}		
			}
			/*
			  Handle illegal brace.
			  (1)Not matched braces before the current brace.
			  (2)A digit follows a close brace ')', lack of operator.   
			*/
			else if(infixExpression[index] == ')'){
				braceNum--;
				if(index == 0 || previous(infixExpression, index) == ' ' || braceNum < 0){
					printError(infixExpression, index);
					printf("<Error! No matched \'(\' before \')\'>\n");
					return 0;
				}
				else if(index != 0 && isdigit(next(infixExpression, index))){
					printError(infixExpression, index);
					printf("<Error! No operator between \')\' and operand>\n");
					return 0;					
				}
			}
			/*
			  Handle illegal '*' and '/'
			  (1)No opreands on both sizes of '*' or '/'.
			  (2)No opreands before operator '*' or '/'.
			  (3)No opreands after operator '*' or '/'.
			  (4)An operator '*','/','+' or '-' follows operator '*' or '/'.
			*/
			else if(infixExpression[index] == '*' || infixExpression[index] == '/'){
				if(previous(infixExpression, index) != ')' && !isdigit(previous(infixExpression, index)) && (next(infixExpression, index) == '\0' || next(infixExpression, index) == ')')){
					printError(infixExpression, index);
					printf("<Error! Operator \'%c\' without operand in expression>\n", infixExpression[index]);
					return 0;
				}
				else if(index == 0 || (previous(infixExpression, index) != ')' && !isdigit(previous(infixExpression, index)) && (isdigit(next(infixExpression,index)) || next(infixExpression,index) == '('))){
					printError(infixExpression, index);
					printf("<Error! No operand before operator \'%c\'>\n", infixExpression[index]);
					return 0;				
				}
				else if(infixExpression[index + 1] == '\0' || next(infixExpression, index) == '\0' || next(infixExpression, index) == ')'){
					printError(infixExpression, index);
					printf("<Error! No operand after operator \'%c\'>\n", infixExpression[index]);
					return 0;
				}
				else if(next(infixExpression, index) == '*' || next(infixExpression, index) == '/' || next(infixExpression, index) == '+' || next(infixExpression, index) == '-'){
					printError(infixExpression, index);
					printf("<Error! Operator \'%c\' follows another operator \'%c\'>\n", next(infixExpression, index), infixExpression[index]);
					return 0;
				}
			}
			//If the char stack is empty
			if(StackEmpty(s)){
				char pc = previous(infixExpression, index);
				/*
				  If the current operator '+' or '-' is an unary operator, the put character '@' and '$' into stack respectively.
				  Handle illegal braces '(' and ')'. 
 				*/
				if((infixExpression[index] == '+' || infixExpression[index] == '-') && !isdigit(pc)){    
					if(!Push(s, infixExpression[index] == '+'? '@':'$')){
						printf("<Error! The stack is full>\n");
						DestroyStack(s);
						return 0;
					}				
				}
				else{
					if (infixExpression[index] == '('){
						leftBrace++;
					}
					else if(infixExpression[index] == ')'){
						printError(infixExpression, index);
						printf("<Error! No matched \'(\' before \')\'>\n");
						return 0;
					}
					if(!Push(s, infixExpression[index])){
						printf("<Error! The stack is full>\n");
						DestroyStack(s);
						return 0;
					}					
				}
			}
			//If the char stack is not empty, if the current character is '(', then put it into the char stack.
			else if (infixExpression[index] == '('){  
				if(!Push(s, infixExpression[index])){
					printf("<Error! The stack is full>\n");
					DestroyStack(s);
					return 0;
				}
				leftBrace++;
			}	
			/*
			  If the char stack is not emptyand the current character is ')', '+', '-', '*', '/'	
			  (1)If the current character is ')', then move characters from the char stack to the postfix expression until meeting the open brace '('.
			  (2)If the current character isn't ')',
			  		(a)If the current character is prior to the top value of the char stack, then put it into the char stack,
			  		(B)else move the top value of the stack to the postfix expression, repeat (2). 
			*/
			else{ 
				if (infixExpression[index] == ')'){   
					rightBrace++;
					GetTop(s, &e);
       				while (e != '('){
						if(!Pop(s, &postfixExpression[numIndex++])){
							printf("<Error! The stack is empty>\n");
							return 0;
						}
						GetTop(s, &e);
					}
					if(!Pop(s, &e)){  
						printf("<Error! The stack is empty>\n");
						return 0;
					}
				}
				else{                          
					GetTop(s, &e);  			
					if (Priority(infixExpression[index]) > Priority(e)){
						if (infixExpression[index] == '+' || infixExpression[index] == '-'){
							if (previous(infixExpression, index) == '(' && (infixExpression[index] == '+' || infixExpression[index] == '-') 
								&&(isdigit(infixExpression[index + 1])||infixExpression[index + 1] == '(')){   
								if(!Push(s, infixExpression[index] == '+'? '@':'$')){
									printf("<Error! The stack is full>\n");
									DestroyStack(s);
									return 0;
								}
							}
							else{   
								if(!Push(s, infixExpression[index])){
									printf("<Error! The stack is full>\n");
									DestroyStack(s);
									return 0;
								}
							}
						}
						else{   
							if(!Push(s, infixExpression[index])){
								printf("<Error! The stack is full>\n");
								DestroyStack(s);
								return 0;
							}
						}
					}
					else if (Priority(infixExpression[index]) <= Priority(e)){  		
						while(Priority(infixExpression[index]) <= Priority(e)){
							if(!Pop(s, &postfixExpression[numIndex++])){
								printf("<Error! The stack is empty!!!>\n");
								return 0;
							}
							if(GetTop(s, &e) == 0)
							{
								break;
							}
						}
						if(!Push(s, infixExpression[index])){
							printf("<Error! The stack is full>\n");
							DestroyStack(s);
							return 0;
						}						
						index++;
						continue;   
					}
				}				
			}
		}
	 index++;
	}
	//Move the rest characters in the char stack to the postfix expression.
	while (!StackEmpty(s)){    
		if(!Pop(s, &postfixExpression[numIndex++])){
			printf("<Error! The stack is empty>\n");
			return 0;
		}
	}
	//DestroyStack the char stack.
	DestroyStack(s);
	if(leftBrace != rightBrace){
		if(leftBrace < rightBrace){
			printError(infixExpression, index - 1);
			printf("<Error! No matched \'(\' before \')\'>\n");
		}
		else{
			printError(infixExpression, index - 1);
			printf("<Error! No matched \')\' after \'(\'>\n");
		}
		return 0;
	}
	//Judge if the input is empty.
	if(blank == index){
		printf("<Error! The input is EMPTY>\n");
		return 0; 
	}
	else return 1;
}

//Compute the value of postfix expression.
int computeValueFromPostfix(char* postfixExpression, double *value){ 
	int index = 0;
	SqStack1* Is = (SqStack1*)malloc(sizeof(SqStack1));
	InitStack1(Is);
	while(postfixExpression[index] != '\0'){
		if(isdigit(postfixExpression[index])){ 
			
			int temp = index + 1;
			double tempValue = (double)(postfixExpression[index] - '0');;
			while(postfixExpression[temp] != '#'){
				tempValue = 10.0 *tempValue + (postfixExpression[temp] - '0');
				temp++;
				index++;
			}
			if(!Push1(Is, tempValue)){
				printf("<Error! The stack is full>\n");
				DestroyStack1(Is);
				return 0;
			}
			index++;
			continue;
		}
		else if(postfixExpression[index] == '#'){  //为空格
			index++;
			continue;
		}
		else if(postfixExpression[index] == '+' || postfixExpression[index] == '-' || postfixExpression[index] == '*'|| postfixExpression[index] == '/'){   //否则为操作符
			double num1 = 0.0, num2 = 0.0;
			if(!Pop1(Is, &num1)){
				printf("<Error! The stack is empty>\n");
				return 0;
			}
			if(!Pop1(Is, &num2)){
				printError(postfixExpression, index);
				printf("<Error! No  operand after Operator \'%c\' in the expression>\n", postfixExpression[index]);
				return 0;
			}
			switch(postfixExpression[index]){
				case ('+'): if(!Push1(Is, num2 + num1)){printf("<Error! The stack is full>\n"); return 0;}break;
				case ('-'): if(!Push1(Is, num2 - num1)){printf("<Error! The stack is full>\n"); return 0;}break;
				case ('*'): if(!Push1(Is, num2 * num1)){printf("<Error! The stack is full>\n"); return 0;}break;
				case ('/'): if(num1 != 0) {
								if(!Push1(Is, (double)num2 / num1)){
									printf("<Error! The stack is full>\n"); 
									return 0;
								} 
								break;
						    }
						    else{
						    	printError(postfixExpression, index);
						    	printf("<Error! Some operand is divided by zero>\n");
						    	return 0;
						    }
				default:break; 
			}
		}
		else if(postfixExpression[index] == '@' || postfixExpression[index] == '$'){
			double num1 = 0.0;
			if(!Pop1(Is, &num1)){
				printf("<Error! The stack is empty>\n");
				return 0;
			}
			switch(postfixExpression[index]){
				case ('@'): if(!Push1(Is, num1)){printf("<Error! The stack is full>\n"); return 0;}break;
				case ('$'): if(!Push1(Is, 0-num1)){printf("<Error! The stack is full>\n"); return 0;}break;
				default:break;
			}
		}
		index++;
	}
	for (int i = 0; i < 100; i++)
		postfixExpression[i] = '\0';
	*value = 0.0;
	if(!Pop1(Is, value)){
		printf("<Error! The stack is empty>\n");
		return 0;
	}
	DestroyStack1(Is);
	return 1;
}
int isUnary(char* infixExpression){   
	int index = 0, operator = 0, operand = 0;
	while(infixExpression[index] != '\0'){
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
int Priority(char c){               
	switch (c){
	case '(': return 0;
	case '+': return 1;
	case '-': return 1;
	case '*': return 2;
	case '/': return 2;
	case '@': return 3;
	case '$': return 3;
	default:  return 0;
	}
}
char previous(char* infixExpression, int index){                       //前继非空字符
	int i= index;
	while(i > 0 && infixExpression[--i] == ' ' );
    return infixExpression[i];                  // 返回的东西要是式一个非空的字符,要么表达式开始的空格
}
char next(char* infixExpression, int index){                           //后继非空字符
	int i= index;
	while(infixExpression[++i] == ' ' && infixExpression[i] != '\0');
	return infixExpression[i];                 // 返回的东西要是式一个非空的字符,要么返回值'\0'
}    
void printError(char* infixExpression, int index){
	printf("\"");
	for(int i = 0; i < index; i++)
        printf("%c", infixExpression[i]);
    printf("\e[47;30m%c\e[0m", infixExpression[index]);
    while(infixExpression[++index] != '\0')
        printf("%c",infixExpression[index]);
    printf("\"\n");
}

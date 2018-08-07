/*************************************************************************
	> File Name: m1.c
	> Author: HarryHao
	> Mail: 954487858@qq.com 
	> Created Time: 2018年08月07日 星期二 17时25分41秒
 ************************************************************************/

#include <stdio.h>
int main()
{
    char c[] = {'h','e','l','l','o',' ','w','o','r','l','d'};
    for(int i = 0; i < 6; i++)
        printf("%c", c[i]);
    printf("\033[47;30m%c\033[0m", c[6]);
    for(int i = 7; i<11; i++)
        printf("%c",c[i]);
    printf("\n");
    return 0;
}

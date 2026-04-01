#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(){   
    char s[20],sen[30],ch;
    scanf("%c \n%s \n%[^\n]%s",&ch,s,sen);
    //printf("%c \n%s \n%[^\n]%s",ch,s,sen);//no need of the caharcter at printing, just print the sen, 
                                          //the white space is already included in the sen at the 
                                          //reading time
    printf("%c \n%s \n%s",ch,s,sen);
    return 0;
}
#include <stdio.h>
void print(int n);
void (*fp)(int);
void test(int value);
int main(void)
{
   /*
    fp=print;
    (*fp)(10);
    fp(20);
    return 0;
   */
   printf("%d",test);  //a function pointer can be called by just using its name of function
                       //thus printing value of that name print adress of the function pointer
   fp=test;
   printf("\n%d",fp);
   (*fp)(10);
   
}
void print(int value)
{
    printf("%d",value);
}
void test(int value)
{
    printf("%d",value);
}
/*
#include <stdio.h>
int sum(float,float);
signed int diff(int,int);
int mul(float,int);
int div(int,int);
int (*fp)(int,int);
int main(void)
{
    float x;
    fp=sum;
    x=fp(10,20);
    printf("%d\n",x);
    fp=diff;
    x=fp(10,20);
    printf("%d\n",x);
    fp=mul;
    x=fp(10,20);
    printf("%d\n",x);
    fp=div;
    x=fp(10,20);
    printf("%d\n",x);

    return 0;

}
int sum(float a,float b)
{
return(a+b);
}
signed int diff(int a,int b)
{
return(a-b);
}
int mul(float a,int b)
{
return(a*b);
}
int div(int a,int b)
{
return(a/b);
}
*/

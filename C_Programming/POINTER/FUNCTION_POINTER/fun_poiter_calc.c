#include<stdio.h>
void (*fp)(int,int);
void add(int,int);
void sub(int,int);
void mul(int,int);
void div(int,int);
int s;
void main()
{
	int a,b;
	char c;
	printf("enter a:");
	scanf("%d",&a);
	printf("enter b:");
	scanf("%d",&b);
	printf("\nchoose ur operetion:");
	printf("\n1.addition\n2.subtraction\n3.multiplication\n4.division\n");
	scanf(" %c",&c);

	switch(c)
		{
			case'+':
			fp=add;
			(*fp)(a,b);
			break; 
			
			case'-':
			fp=sub;
			(*fp)(a,b);
			break;
			
			case'*':
			fp=mul;
			(*fp)(a,b);
			break;
			
			case'/':
			fp=div;
			(*fp)(a,b);
			break;
			
			default:
			break;
		}
}

void add(int a,int b)
{
	s=a+b;
	printf("sum is:%d",s);
}
void sub(int a,int b)
{
	s=a-b;
	printf("diff is:%d",s);
}
void mul(int a,int b)
{
	s=a*b;
	printf("prdct is:%d",s);
}
void div(int a,int b)
{
	s=a/b;
	printf("quet is:%d",s);
}


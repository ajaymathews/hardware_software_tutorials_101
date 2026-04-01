#include<stdio.h>
struct student
{
	int rollno;
	char name[10];
}*ptr;


void test(struct student *fn_var)
{
	printf("%d\n",(fn_var+1)->rollno);
	printf("%d\n",(fn_var+2)->rollno);
	printf("%d\n",(fn_var+3)->rollno);
}
void main()
{
	struct student str_var[5];
	str_var[1].rollno=10;
	str_var[2].rollno=20;
	str_var[3].rollno=30;
	ptr=&str_var;
	test(ptr);
}

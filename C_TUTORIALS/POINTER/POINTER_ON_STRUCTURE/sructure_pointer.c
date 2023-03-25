#include<stdio.h>
#include<string.h>
struct stud
{
	char name[5];
	int mark;
}s;
void details(struct stud *s);
void main()
{
	struct stud s;
	strcpy(s.name,"ajay");
	s.mark=45;
	details(&s);
}
void details(struct stud *s)
{
	printf("name is :%s\n",s->name);
	printf("mark is :%d",s->mark);
}

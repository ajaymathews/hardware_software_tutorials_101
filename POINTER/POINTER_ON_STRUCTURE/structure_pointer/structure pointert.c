#include <stdio.h>
#include<conio.h>
#include<string.h>
 struct student
 {
     char course[20];
     char name[20];
     int rol_num;
 }stud[20];
 
int main()
{
int i=0;
 struct student* ptr1=stud;
 for(i=0;i<3;i++)
 {
 scanf("%d",&(ptr1+i)->rol_num);
 }
 for(i=0;i<3;i++)
 {
 printf("%d",(ptr1+i)->rol_num);
 }
 
}

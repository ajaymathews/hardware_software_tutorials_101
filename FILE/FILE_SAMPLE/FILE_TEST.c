#include<stdio.h>
//#include<stdin.h>
void main()
{
FILE *fp1;
char str[20];
char x='y';
/******* writing sections in file**********/
/*
fp1=fopen("demo.txt","a");
fputc('g',fp1);//writes character by character
fputc(x,fp1);



fclose(fp1);
*/


/******* reading sections in file**********/
fp1=fopen("demo.txt","r");
x=fgetc(fp1);
//fgets(str,100,f
p1);//100 is the maximum count






printf("%c",x);
//printf("%s",str);
}

#include <stdio.h>
//#include <>
int main(void)
{
    FILE *fp,*fp1;
    char a[10],str[10];
    fp=fopen("kkpp.txt","w+");
    gets(str);
	fwrite("hello",20,20,fp);
    //fputs(str,fp);
    close(fp);
/*
    fp1=fopen("kkpp.txt","r");
    fgets(a,9,fp1);
    printf("%s",a);
    close(fp1);
*/
}


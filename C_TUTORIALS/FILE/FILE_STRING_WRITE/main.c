#include <stdio.h>
#include <string.h>
struct filedat
{
	char string[10];
	int num;
	float percnt;
}fd;
int main(void)
{
    char str[50];
    char src[]="ajay_mathews";
    
    int roll_no=20;
    float mark=20;
    int year=2012;
    FILE *fp;
    fp=fopen("sample.txt","w");
    
    
    //fd.string[]="binary"; //somehow thus is not beign possible in structure variable.
   /* 
    strcpy(fd.string,"binary");
    fd.num=100;
    fd.percnt=35;
    */
    fprintf(fp,"name:%s %s ,rollno:%d mark:%f year:%d", src, str1, roll_no,mark,year);
    
    
    /****************Different Methods to write into a file*************/
   /* 
           fp=fopen("sample.txt","w");
    
   /*1*/ //fputs(src,fp); //used to write a string into the file that points to src.but it executes line by line.
    
	
   /*2	fprintf(fp,"%s %s %s %d", src, str1, str2,year);//multiple strig is joined and written to the file.
													//using this method we could add int float values to the file.
    fclose(fp);
    */
    
    
   /* fp=fopen("sample.txt","wb");
   
    fwrite(&fd, sizeof(struct filedat),1, fp);//fwrite(addressData, sizeData, numbersData, pointerToFile);
    */
    fclose(fp);
    
    /*
    fp=fopen("sample.txt","r+");
    fgets(str,50,fp);//alwys the problem is the '50',which is the length of data that is to be read from file.
                    //this function reads from fp and put that data into the string str.
    fclose(fp);
    puts(str);
    */
}


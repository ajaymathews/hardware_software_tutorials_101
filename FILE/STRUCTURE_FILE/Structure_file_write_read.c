#include <stdio.h>
#include <stdlib.h>
typedef struct student
  {
  	char name[100];
  	int roll_no;
  	float marks;
  }stud;

int main () {

   int r[3],i;
   char n[3][30],n2[30],n3[30];
   float m[3];
   FILE * fp;
   /*
   fp = fopen ("file.txt", "w+");
   stud s[3];
    printf("Enter the Details of students:\n");
    for(i=0;i<3;i++)
    {
    	printf("Name:");
    	scanf("%s",s[i].name);
    	printf("RollNo:");
    	scanf("%d",&s[i].roll_no);
    	printf("Mark:");
    	scanf("%f",&s[i].marks);	
    	fprintf(fp,"Name:%s Roll_no:%d Mark:%f \n",s[i].name,s[i].roll_no,s[i].marks);
	}  
	fclose(fp);
   */
  /*
   fp = fopen ("file.txt", "r+");
   for(i=0;i<3;i++)
   {
   	fscanf(fp,"Name: %s Roll_no: %d Mark: %f ",n[i],&r[i],&m[i]);
   }
   
   for(i=0;i<3;i++)
   {
   	printf("Name: %s Roll_no: %d Mark: %f\n",n[i],r[i],m[i]);
   }
   fclose(fp);
   */
   return(0);
}

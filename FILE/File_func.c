#include <stdio.h> 
  
int main() 
{ 
    FILE *fp; 
    char str[4],x,need[4];
    int count=1,i;
/*    
	fp = fopen("test1.txt", "r"); 
       
   // fseek(fp, 10, SEEK_SET);
   // fgets(str,4,fp);
   
    x=fgetc(fp);
    while(x!=EOF&&count<10){
	x=fgetc(fp);
	count++;
   } 
   for(i=0;i<4;i++)
   {
	str[i]=fgetc(fp);
	printf("%c",str[i]);
   }	
	fclose(fp); 
   */
    fp = fopen("test1.txt", "r"); 
	 
    fseek(fp, 5, SEEK_SET); 
    //fputs(str,fp);
    char y=fgetc(fp);
    printf("value:%c\n",y);
    
    printf("%d", ftell(fp));
  
    return 0; 
} 

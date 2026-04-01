#include<stdio.h>
void main(){
	int i=0,j=0;

/*
char *str="hello";
char str1[]="howareyou"; 
*/
/*similar functionality*/


/*
char *str2[3]={"good","morning","ajay"}; // arry of pointer, which each pointer points to a string

int **arr={{1,2,3},{40,50,60},{700,800,900}};

char **str3={"what","evening","dae"};

*/ 
/* 2d array of strings can be represented both ways*/


/*	printf("%s\n",str);
	printf("%s\n",str1);
	printf("%s %s %s\n",*(str2),*(str2+1),*(str2+2));
*/

	char **doublepointer;
	// char **str3={"good","morning","ajay"}; // #invalid
	// int **arr={{1,2,3},{40,50,60},{700,800,900}}; //#invalid
	char *arraypointer[5]={"good","morning","ajay","hello","shyamannan"};
	
	doublepointer=arraypointer;
	
	
	
	
	// for(j=0;j<10;j++){
	// 	printf("*( doublepointer +%d)-> %s\n",j,*(doublepointer+j));
	// }
	//printf("%c\n",*(*str3)+1);
	//printf("%s\n",str3[0]);
	printf("%s\n",*(doublepointer+1));

}

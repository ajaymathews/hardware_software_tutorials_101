#include<stdio.h>
#include <stdlib.h>
void main()
{
/*   //this will work, we can assign one string to other using pointer variable
	char *a="ajay",*b="boss",*temp;
	temp=a;
	a=b;
	b=temp;
	printf("a:%s \nb:%s \ntemp:%s",a,b,temp); //string can be assigned if string pointer is used
*/
// 	char *a,*b,*temp;
// 	a=calloc(10,sizeof(char));
// 	scanf("%s",a);//for scanf,we need to allocate memory, oherwise it wont work.

// printf("a:%s",a);	
	char *a="ajay",*b="boss",*temp;
	a=b;
	//a[0]='m';
	printf("%s",a);

}

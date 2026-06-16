#include<stdio.h>
void main()
{
	
	int a;
	float b;
	char c;
	scanf("%d %f %c",&a,&b,&c);
	printf("out of scanf");
	printf("\n int:%d float:%f char:%c",a,b,c);/* dont know how the value of float is initialized to 0.0000, and the value of c is empty in all cases, even if we change the order of printing andf scaning, float must read a float value only, otherwise this happens*/
	
}

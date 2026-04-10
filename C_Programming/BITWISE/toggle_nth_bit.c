/*TOGGLE NTH BIT OF A NUMBER*/

#include<stdio.h>
void main(){
	int num,n;
	printf("enter the num:");
	scanf("%d",&num);
	printf("enter the bit:");
	scanf("%d",&n);
//	printf("%d",num^(1<<n));//TOGGLE
	printf("%d",num|(1<<n));//SET
//    printf("%d",num&~(1<<n));//RESET
}

/*
(1<<5) is actually initilize 1 , then shifts it 5 position
0)      no shift    :  0000001 (value initiliazed)	
1)      first shift :  0000010 
2)     second shift :  0000100 
3)      third shift :  0001000 
4)     fourth shift :  0010000 
5)      fifth shift :  0100000 
thus 1<<5 is 0100000 
*/ 
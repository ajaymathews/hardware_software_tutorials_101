#include<stdio.h>
#include<stdio.h>
void main()
{
	
	int i,j=0,k=0;
	for(i=0;i<=10;i++){
		j=j++;  /* This statement will nullify the effect of j++,
					which means that the value of j will always be 0,
					
					In this case upon assigning j=j++, the value should be incremnted first for that,j is taken to temp and then incremented, but it is a postincremnt operation,
					//i think it is then replaced by the asignment of previous j value , which is zero
					 */
	
		printf("j=j++:%d\n",j);
	}
	printf("%d",j);
	
}

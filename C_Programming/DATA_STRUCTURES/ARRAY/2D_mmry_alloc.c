#include<stdio.h>
void main()
{
int a[10][10],i,j;
int *p= a;

for(i=0;i<3;i++)
{
	for(j=0;j<3;j++)
	{
		scanf("%d",&a[i][j]);
	}	
}
//the memory location both acesses
for(i=0;i<10;i++)
{
	for(j=0;j<10;j++)
	{
		printf("a[%d][%d] => %d : %d\n",i,j,&a[i][j],(p)+(i*10)+j);
	}	
}
}

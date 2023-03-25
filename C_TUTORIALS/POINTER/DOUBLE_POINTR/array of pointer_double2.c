#include<stdio.h>
int n;

void read_array(int **p)
{
	int i,*p_int=*(p);
	char *p_char=*(p+1);
	float *p_flot=*(p+2);
	printf("p_int:%d\t",p_int);
	printf("p_string:%d\t",p_char);
	printf("p_float:%d\n",p_float);
	
	
	printf("Specify the limit to the arrays:");	
	scanf("%d",&n);
	
	printf("Enter the Numbers to array: \n");	
	for(i=0;i<n;i++)
	{	printf("->");
		scanf("%d",&num_array[i]);	
	}
	
	printf("numeric array is entered into %p",num_array);
	
	printf("\nEnter the Characters to array: \n");	
	for(i=0;i<n;i++)
	{	printf("->");
		scanf(" %c",&char_array[i]);	
	}
	
	printf("charcter array is entered into %p",char_array);
	printf("\nEnter the String:");
	scanf("%s",string_array);
	printf("string is entered into %p",string_array);
}
*/
void main()
{
	int num_array[100],n,i;
	char string_array[100];
	float flot_array[100];
	int *z[]={num_array,string_array,flot_array};
	int **ptr=z;
	printf("Num_array:%d ,string_array:%d ,float_array:%d\n",num_array,string_array,flot_array);
	printf("ptr=%d,z=%d\n",ptr,z);
	read_array(ptr);
	
	

//	printf("numArray-%p\n,charArray-%p\n,stringArray-%p\n",z[0],z[1],z[2]);
}

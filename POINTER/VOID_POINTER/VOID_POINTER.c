#include<stdio.h>
void main()
{
	int a = 10; 
	char b = 'x'; 
	int c[]={1,7,2,9,3};
    void *p;
    
	p= &a;         // void pointer holds address of int 'a' 
	
	//printf("%d",*p); //void pointer cannot be dereferenced normally
	printf("a=%d\n",*(int*)p); //defereferenced only by applying the type of the pointer to it
		
	
	p = &b;       // void pointer holds address of char 'b' 
	
	//printf("%c",*p); //void pointer cannot be dereferenced normally
	printf("b=%c\n",*(char*)p);
	
	p = c;
	printf("c[0]=%d\t",*(int*)p);
//	printf("c[1]=%d\t",*(int*)(p+1));//pointer arrithemetic is not applicable in void pointer
	printf("c[1]=%d\t",*(int*)(p+sizeof(int))); //nd elemnt is found by adding 4bytes to current adress.
}

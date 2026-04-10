/*void read_array(int *x,int n)  //#this method recieves adress and stores to pointer
{   int i;
    printf("\n Array is entered into the adress %p\n",x);
    printf("now, enter the array elements:");
    for(i=0;i<n;i++)
    {   scanf("%d",&(*(x+i)));  }
    printf("\nArray:\t");
    for(i=0;i<n;i++)
    {   printf("%d \t",*(x+i)); }
}*/


#include <stdio.h>
void read_array(int x[],int n) //#array is passed as adress but recieved as an array,
                               //#thus after read array values, x[0],..x[n] can be obtained
{   int i;
    printf("\nnow, enter the array elements\n");
    for(i=0;i<n;i++)
    {   printf("- ")
    scanf("%d",&x[i]);  }
    printf("Array stored in: %p\n",x);
    printf("Stored Array:\t");
    for(i=0;i<n;i++)
    {   printf("%d \t",x[i]); }
    printf("\n");
}
int* sum_array(int a[],int b[],int n)
{   int c[100],i;
    for(i=0;i<n;i++)
    {   c[i]=a[i]+b[i]; }
    printf("\nFinal Array location: %p\n",c);
    printf("Output Array:\t");
    for(i=0;i<n;i++)
    {   printf("%d \t",c[i]);}
    return c;
}

int main(void)
{ int a[100],b[100],n,*s,i;
  printf("Specify the limit:");
  scanf("%d",&n);
  printf("Location alloted for 1st Array : %p\n",a);
  printf("Location alloted for 2nd Array : %p\n",b);
  read_array(a,n);
  read_array(b,n);
  s=sum_array(a,b,n);
  printf("\npassed location to main: %p\n",s);
  printf("\nValue in passed location %d\n",*s);
  printf("\nArray Passed to the main:");
  for(i=0;i<n;i++)
  {   printf("%d \t",*(s+i)); }
}


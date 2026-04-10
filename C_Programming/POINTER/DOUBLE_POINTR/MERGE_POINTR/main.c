#include <stdio.h>

void merge_doublepointer(int **a)    ///using pointers
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
       {
        printf("%d\n",*(*(a+i)+j));
    }

}}

int main(void)
{
    int j,i;
    int arr1[]={9,8,7};
    int arr2[]={6,5,4};
    int arr3[]={3,2,1};
     int *ptr[3]={arr1,arr2,arr3};
     int **p=&ptr;


        merge_doublepointer(p);
}










//int main(void)
//{
//    int i,j,arr[5][5],(*ptr)[3];
//    printf("enter the 2d array");
//    for(i=0;i<3;i++)
//    {
//        for(j=0;j<3;j++)
//        {
//            scanf("%d",&arr[i][j]);
//        }
//    }
//    for(i=0;i<3;i++)
//    {
//        for(j=0;j<3;j++)
//        {
//            printf("%d",(*(arr+i))[j]);
//        }
//        printf("\n");
//    }

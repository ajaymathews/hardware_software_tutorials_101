#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{
    int n,i,j;
    scanf("%d", &n); 
    for(i=n;i>0;i--){
        
        for(j=n;j>=i;j--){ // prints a triangle 
            printf("%d ",j);
        }
        for(j=1;j<=i-1;j++){
            printf("b ",i);
        }
        for(j=1;j<=i-2;j++){
            printf("c ",i);}
        for(j=i;j<=n;j++){
            if(j==1)
            continue;
            printf("d ",j);
        }    
        printf("\n");
    }
    for(i=2;i<=n;i++){
        for(j=n;j>=i;j--){
            printf("e ",j);
        }
        for(j=i;j>1;j--){
            printf("f ",i);
        }
        for(j=i;j>1;j--){
            printf("g ",i);}
        for(j=i+1;j<=n;j++){
            printf("h ",j);
        }
        printf("\n");
    }
    return 0;
}

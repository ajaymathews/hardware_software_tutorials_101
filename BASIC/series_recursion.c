#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//Complete the following function.

int find_nth_term(int n, int a, int b, int c) {
static int s=0;
    if(s!=0){
        a=b;
        b=c;
        c=s;}
        if(n==3)
            return c;
        else if(n==2)
            return b;
        else if(n==1)
            return a;            
    n--;
    if(n-2>0){
        s=a+b+c;
        find_nth_term(n,s,b,c);
    }
    return s;
}


int main() {
    int n, a, b, c;
  
    scanf("%d %d %d %d", &n, &a, &b, &c);
    int ans = find_nth_term(n, a, b, c);
 
    printf("%d", ans); 
    return 0;
}
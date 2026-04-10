/* THIS PROGRAM IS USED TO CALL THE NAME OF THE FUNCTION WE ENTER THROUGH 
SCANF(), THE FUNCTION DEFENITION ARE DEFINED AND DECALRED IN MULTIPLE FILES 
SINCE WE CANNOT ASSIGN THE STRING DIRECTLY TO THE FUNCTION POINTER, WE CREATED 
A 'LOOKUPTABLE' WHICH IS SIMPLY A STRUCTURE LIST THAT CONTAINS  THE FUNNAME 
ALONG WITH THE STRING, AND WHENEVER WE ENTER THE STRING, A FUNCTION IS USED TO 
ITERATE THROUGH THE STRING LISTS IN THE TABLE AND WHENEVER A MATCH HITS, IT
RETURN THE FUNNAME ASSIGNED WITH THE STRING*/


#include <stdio.h> 
#include <string.h>
#include "arithmetic.h"
#include "bitwise.h"
#include "relational.h"

typedef struct{
    char *name;
    int (*fn)();
}lookuptype;   /*this name lookuptype is created that contains two elements the 
                string we are going to enter and the function related to it, both this will be used to create a table thatwill be used to match the fun() name with string*/


lookuptype lookuptable[]={
    {"sum",sum},{"sub",sub},{"div",div},{"mul",mul}    };              
/*this table will be used to get the function name from thestring enetered,as 
we cannot directly assign string to the function pointer*/


int (*getfn(char* name))(){
    for(int i=0;i<sizeof(lookuptable)/ sizeof(lookuptype);i++){ 
        
        /*(sizeof(lookuptable)/ sizeof(lookuptype)) will give out the no elements present in the array, similar to total_size/size of 1 elmnt*/

        if(strcmp(lookuptable[i].name,name)==0){
            return lookuptable[i].fn;
        }
    }
    return NULL;
}
/*this function is used to get the funname when we enter the string, it iterates through all the values in the lookuptable array(structuaral array) 
and compares the funname with the string enterd using strcmp*/


int main(){
    int a;
    int b;
    char s[4];
    int(*fn)(int, int); /* This is the function pointer we used to call the 
                            function */
    printf("this is the main file:%d\n",sizeof(a));
    printf("A:");
    scanf("%d",&a);
    printf("B:");
    scanf("%d",&b);
    printf("enter the operation:");
    scanf("%s",s);
    fn=getfn(s);/*in here the value of fn pointer fn will be assigned with 
                funname if it matches the string name*/
 
    printf("%d",fn(a,b));
}
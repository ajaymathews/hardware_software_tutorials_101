/***** template in array passsing*******/

#include<iostream>
using namespace std;
template <class T>
//this T will be changed to the data type as per the parameter passed,
//thus we can use same function with 2 type of parameter

T fun(T x[],T y[]){
    if((typeid(x[0])==typeid(char))||(typeid(x[0])==typeid(string))){
        //if the type passed is char or string, just print x , y prints string
        cout<<"T fun(T,T) "<<x<<y<<endl;
    }
    else{//if the type passed is int, implement loop to print int array 
        for(int i=0;i<6;i++){
             cout<<x[i]<<" "<<y[i]<<" ";
        } cout<<endl;
    }
}
 
int main()
{ int i_arr1[]={0,1,2,3,4,5};
int i_arr2[]={6,7,8,9,10,11};
char s_arr1[]="hello";
char s_arr2[]=" world";
 
 fun(s_arr1,s_arr2); 
 fun(i_arr1,i_arr2);
}

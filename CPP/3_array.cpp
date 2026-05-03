/* 
 * Tutorial: 3_array.cpp
 * Description: Part of the C++ Programming Tutorial Series
 * 
 * How to Compile: g++ "3_array.cpp" -o "3_array"
 * How to Run:     ./"3_array.exe"
 */
#include<iostream>
using namespace std;
int main()
{
/*********Character array************/

char c_arr[]={'h','e','l','l','o',' ','w','o','r','l','d'};//11 size
//in memory, c_arr="hello world" only not null terminated

char a_arr[]="hello world" ;//size 12
//in memory, a_array="hello world\0"
//a_array has null terminated

string s_arr="hello world";//size 32
//s_arr,ie, string is a class contains 
//- a pointer: which holds adress of the array which is a heap(dynamic memory), 
//- an int with size of the charcter in string, and 
//- an int shows how much memory allocated curently, to calculate resizing


//BElow 3 method prints the string hello world just fine
cout<<"c_array : "<<c_arr<<endl;
//unlike in c, just array name print the whole array in char 
cout<<"a_array : "<<a_arr<<endl;
cout<<"s_arr: "<<s_arr<<endl;


//all 3 method will print the first charcter 'h'
cout<<"first charctr ion c_array: "<<c_arr[0]<<endl;
cout<<"first charctr in a_array "<<a_arr[0]<<endl;
cout<<"first charctr in s_array: "<<s_arr[0]<<endl;
//s_arr[0] return 'h' because the [] operator is overloaded in the 
//class to mimic the functionality of [] in normal arrays. 




/***********Integer array**************/

int i_arr[]={1,5,3,8,2};

cout<<"integer_array: "<<i_arr<<endl;//prints the address of the first element
//this address is a label of the array allocation, which cannt be incremented using pointer arithmetic


cout<<"integer_array using for loop: ";
for (int i=0;i<=4;i++){
cout<<i_arr[i];       }
cout<<endl;


/*****pointer arithmetic*****/

//++arr_i and arr++ will not work as it tries to increment the fixed label / fixed address of array adress(arr_i). it is not modifiable	 
// soln: instead of incrementing array address, assign a pointer to array address and increment it

/***** causes error: modifying fixed address of array *****/
// cout<<*(++arr); 
// cout<<*(arr++); 


int *ptr = i_arr;//asign an pointer, which can be varied usin ponit arithemtic

/** This will work because ptr is a pointer to an arry address */
cout<<"integer_array using poinetr arithmetic ptr++: "; 
for (int i=0;i<=4;i++){
cout<<*(ptr++)<<" "; }cout<<endl; //array usng pointer arithmetic ++arr



//but arr_i+i works becuse it is same as arr[i], pointing to the next location
cout<<"integer_array using poinetr arithmetic arr+i: "; 
for (int i=0;i<=4;i++){
cout<<*(i_arr+i)<<" "; }cout<<endl; //array usng pointer arithmetic arr+i




/*****Dynamic memory allocation for array********/

int size=10;

int *dy_arr = new int[5]; 
//this will allocate a 5 integer spaces in the heap memory
int *dy_arr_new = new int[size]; 
//this allocation using size as a variable also work fine
int i=0;	

for(i=0;i<5;i++){
	dy_arr[i]=i*10;     }

for(i=0;i<size;i++){
	dy_arr_new[i]=i;     }

//please note we cannot asign dy_arr_new={1,2,3,4,5,6,7,8,9,10} in both dynamic and normal array, after its initilization


cout<<"dy_arr[]=";
for(i=0;i<5;i++){
	cout<<dy_arr[i]<<" ";   }  cout<<endl;

cout<<"dy_arr_new[]=";
for(i=0;i<size;i++){
	cout<<dy_arr_new[i]<<" ";   }  cout<<endl;


delete[]dy_arr; //freeying the dynamic memmory alocated
delete[]dy_arr_new;

dy_arr=NULL; // initilaizing it to a null value to avoid a wild pointer scenerio
dy_arr_new=NULL;

}


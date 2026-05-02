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
//in memory, a_array="hello world\n"
//a_array has null terminated

string s_arr="hello world";//size 32
//s_arr,ie, string is a class contains 
//- a pointer: which holds adress of the array which is a heap(dynamic memory), 
//- an int with size of the charcter in string, and 
//- an int shows how much memory allocated curently, to calculate resizing


//BElow 3 method prints the string hello world just fine
cout<<"c_array : "<<c_arr<<endl;
//unlike in c, just array name print the whole array both in char and int
cout<<"a_array : "<<a_arr<<endl;
cout<<"s_arr: "<<s_arr<<endl;


//all 3 method will print the first charcter 'h'
cout<<"first charctr ion c_array: "<<c_arr[0]<<endl;
cout<<"first charctr in a_array "<<a_arr[0]<<endl;
cout<<"first charctr in s_array: "<<s_arr[0]<<endl;
//s_arr[0] return 'h' because the [] operator is overloaded in the 
//class to mimic the functionality of [] in normal arrays. 




/***********Integer array**************/
/*
int i_arr[]={1,5,3,8,2};
/* 
cout<<"i_array: "; 
for (int i=0;i<=4;i++)
{
cout<<i_arr[i]; 
}
cout<<endl;
*/

/*****pointer arithmetic*****/
/*
cout<<"i_array: "; 
for (int i=0;i<=4;i++)
{
cout<<*(i_arr+i); //array usng pointer arithmetic
//i_arr++;       //dosnt go to the next array elemnt if it is initialised as array, will work if it is initialised using pointer as dynamic array
}
cout<<endl;



/*****Dynamic memory allocation for array********/
/*
int i=10;
//int *dy_arr = new int[10]; //this will allocate a 10 integer spaces in the heap memory under the name dy_arr,
int *dy_arr = new int[i]; //this also will work fine
for(i=0;i<10;i++){
	cout<<"dy_arr["<<i<<"]: ";
	cin>>dy_arr[i];
}

cout<<"dy_arr[]=";
for(i=0;i<10;i++){
cout<<dy_arr[i]<<" ";
}
cout<<endl;

delete[]dy_arr; //freeying the dynamic memmory alocated
dy_arr=NULL; // initilaizing it to a null value to avoid a wild pointer scenerio

*/

}


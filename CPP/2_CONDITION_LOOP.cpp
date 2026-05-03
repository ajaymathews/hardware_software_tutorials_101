/* 
 * Tutorial: 2_CONDITION_LOOP.cpp
 * Description: Part of the C++ Programming Tutorial Series
 * 
 * How to Compile: g++ "2_CONDITION_LOOP.cpp" -o "2_CONDITION_LOOP.exe"
 * How to Run:     ./"2_CONDITION_LOOP.exe"
 */
#include<iostream>
using namespace std;
int main()
{ int num1,num2;
cout<<"num1:"; 
cin>>num1; 
cout<<"num2:"; 
cin>>num2;
if ( (num1 > num2) or (num1 > 10 ) )
	cout<<"num1 is greater"<<endl;
else
	cout<<"num2 is greater"<<endl;

//the condition for 'or', 'and' (&&)  ,
if(num1 > num2 || num1 > 10){ 
	cout<<"num1 is greater"<<endl;
}

/********** LOOPS  ************/

for(int i=0;i<5;i++)
{  cout<<i<<" ";   }
cout<<endl;

/* similar functionality or or loop*/
int i=0;
bool cond=true;
for( ; cond ; ){
	cout<<i<<" ";
	i++;
	if(!(i<5))
		cond=false;
	}
cout<<endl;





/* while Loop*/
cout<<"start_limit:"; 
cin>>num1; 
cout<<"end_limit:"; 
cin>>num2;

while(num1<=num2){
	cout<<num1<<" ";
	num1++;
}
}

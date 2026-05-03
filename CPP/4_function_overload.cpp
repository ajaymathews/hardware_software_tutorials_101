/* 
 * Tutorial: 4_function.cpp
 * Description: Part of the C++ Programming Tutorial Series
 * 
 * How to Compile: g++ "4_function.cpp" -o "4_function.exe"
 * How to Run:     ./"4_function.exe"
 */



/******* function overloading********/
/* Same add() to add different parameter type*/						
/*it is done by using the same function with different numbers of parameter or different type parameter with same function name
*/

#include<iostream>
using namespace std;

/****** Function defenitions of overloaded functions ******/

int add(int x,int y)
{cout<<"add-fun(int,int): "<<x<<" + "<<y<<endl;
 cout<<"sum: "<<x+y<<endl;
return 0;}

int add(float x,int y)
{cout<<"add_fun(float,int): "<<x<<" + "<<y<<endl;
 cout<<"sum: "<<x+y<<endl;
return 0;}
 
int add(float x,float y)
{cout<<"add_fun(float,float): "<<x<<" + "<<y<<endl;
 cout<<"sum: "<<x+y<<endl;
return 0;}

int add(int x,float y)
{cout<<"add_fun(int,float): "<<x<<" + "<<y<<endl;
 cout<<"sum: "<<x+y<<endl;
return 0;}

int add(int x,int y,int z)
{cout<<"add_fun(int,int,int): "<<x<<" + "<<y<<" + "<<z<<endl;
 cout<<"sum: "<<x+y+z<<endl;
return 0;}
 


int main(){

/******* Function calls *******/ 	
add( 10 , 20 );
add( 10.5f , 20 ); 
add( 10 , 20.2f );
add( 10.5f , 20.2f );
//to pass a float value to fun it need to be with 'f', 
//bcz, normally it taken as double
add( 10 , 20 , 30 );

} 






/******* Default arguments******/
/*
#include<iostream>
using namespace std;
//when the number of parametrs differ,in 2 parmeter case,3rd is taken as zero default,
//and in 3 parametrs case, the z is assigned the passed value, z=0 is ignored,but make sure
int fun(int x,int y,int z=0;)        //that the default parmetr comes at right
{cout<<"int fun(int,int,int) "<<x<<":"<<y<<":"<<z<<endl;}					
int main()
{ 
 fun(1,2); 
 fun(1,2,3);
}

/*
void add(T x,T y,T z=0)
{cout<<x+y+z<<endl;}
int main()
{   add(10.6f,20.8f,0.9f);
    add(10.6f,20.8f);	} 
*/



/************ call by refernce ***************/
/*actually using call by value method, it can access the variable loaction like call by adresss*/
/*
#include<iostream>
using namespace std;
int fun(int &a,int &b)//jut include a '&' next to the parameter
{a=a+10;
b=b+10;  }
 
int main()
{int x=1,y=2;
 fun(x,y);//passed parameter value
 cout<<"int fun(int,int) "<<x<<":"<<y<<endl; 
}*/




/********Function pointer*************/
//same as C
/* 
int sum(int x,int y){
	return x+y;     }
int diff(int x,int y){
	return x-y;     }
int main()
{
	int (*fp)(int,int);
	fp=sum; cout<<"sum:"<<fp(10,9)<<endl;//or (*fp)(10,9);
	fp=diff; cout<<"diff:"<<fp(10,9)<<endl;
}  */


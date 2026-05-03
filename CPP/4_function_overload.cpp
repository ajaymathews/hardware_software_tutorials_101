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

int dif(int x,int y)
{cout<<"diff-fun(int,int): "<<x<<" - "<<y<<endl;
 cout<<"diff: "<<x-y<<endl;
return 0;}

/******* Default arguments******/

int fun(int x,int y,int z=0){        
//that the default parmetr comes at right
cout<<"int fun(int,int,int) "<<x<<":"<<y<<":"<<z<<endl;}				

/*instead of writing every possible combination, we can use template ,which is discussed in next tutorial*/



/********Function pointer*************/
int (*fp)(int,int); //can be defclared globaly or locally inside main()

//Cleaner method
/*
typedef int (*int_fun_ptr)(int,int);
int_fun_ptr fp1;//creating new functio pointer that can point to
//add() and diff()
fp1=add;
fp1=diff

int_fun_ptr fp2;//creating new functio pointer that can point to
//add() and diff()
fp2=add;
fp2=diff
*/

/*
Because C++ supports function overloading, the compiler changes function names (e.g., void fun(int) becomes _Z3funi). ie, in the assembly code or something function is given an unique identifier type name

extern "C" {
    void EXTI0_IRQHandler(void) {
        // Interrupt code
    }
}
this extern "C" let knows the compiler that keep the anme of the function at it is, don't change it.
*/


/********Function pointer*************/

int main(){

/******* Function calls *******/ 	
add( 10 , 20 );
add( 10.5f , 20 ); 
add( 10 , 20.2f );
add( 10.5f , 20.2f );
//to pass a float value to fun it need to be with 'f', 
//bcz, normally it taken as double
add( 10 , 20 , 30 );

fun(1,2);//output x=1,y=2,z=0
fun(1,2,3);//output x=1,y=2,z=3

/********Function pointer*************/
//int (*fp)(int,int); 
fp=add;
cout<<"function pointer to add()"<<endl;
fp(1,2);

fp=dif;
cout<<"function pointer to dif()"<<endl;
fp(1,2);

} 



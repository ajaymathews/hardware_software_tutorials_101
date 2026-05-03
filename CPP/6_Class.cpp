/* 
 * Tutorial: 5_Class.cpp
 * Description: Part of the C++ Programming Tutorial Series
 * 
 * How to Compile: g++ "5_Class.cpp" -o "5_Class.exe"
 * How to Run:     ./"5_Class.exe"
 */
// /*
#include<iostream>
using namespace std;

class rectangle{	
	private:
		int pri_length, pri_breadth;

	public:
		//by default variables and function inside a class  become private,so we cant access this from main(), therefore to access it in main(), use public:	

		int length,breadth; 

		int area()
		{ return (length*breadth); }
		
		int peri()
		{ return (2*(length+breadth)); }	

		
	~rectangle() //this will b called a the end of the program automatically
		{cout<<"destructor called "<<endl;}
	
	};

int fun_ptr_class(rectangle* r_ptr){
	r_ptr->length = 4;
	r_ptr->breadth = 4;
	return 0;
}

int fun_ref_class(rectangle& ref){
	ref.length=6;
	ref.breadth=6;
	return 0;
}

int main()
{ 

	/************  Creating a class and its objects ************/
	rectangle r1,r2;//this r1 and r2 are the objects.
	r1.length=1;
	r1.breadth=2;
	//r1.pri_length=10;//cannot access as this is a private variable
	
	cout<<"area() using object : "<<r1.area()<<endl;





	/************ Using Pointer *************/
	
	rectangle *r_ptr = nullptr;
	//class pointer to hold the adress of the class pointing to null value initially

	r_ptr = &r1; 
	//pointer knows the address of r1 now
	//this is the important step,only this will point the object to the pointer

	cout<<"checking poniter hold previous r1 area() value :"<<r_ptr->area()<<endl;
	//calling object function of r1 using pointer r_ptr

	//modifying the r1 object values
	r_ptr->length=2;
	r_ptr->breadth=2;
	//r_ptr->pri_length=10;//cannot access as this private variable from main()
	cout<<"area() using pointer : "<<r_ptr->area()<<endl;	



	/********* passsing value to the function using pointer *************/

	fun_ptr_class(r_ptr);
	cout<<"classs value modified in pointer function:"<<r1.area()<<endl;



	/************ Using refernces *************/
	rectangle & ref = r2; //points to the r2 , it is same as r2
	ref.length	= 5;
	ref.breadth = 5;
	cout<<"area value modifie using refernce: "<<ref.area()<<endl;



	/********* passsing value to the function using refrence *************/

	fun_ref_class(r2);
	cout<<"classs value modified in ref function:"<<r2.area()<<endl;

	


	/************ Dynamic memory allocation (in heap) for class object */

	rectangle *dyn_r_ptr = new rectangle(); 
	//creates a new memory in heap and assigns it to dyn_r_ptr 
	//this rectangle() is constructor

	dyn_r_ptr->length=10;
	dyn_r_ptr->breadth=10;
	//dyn_r_ptr->pri_length=10;//cannot access as this is a private variable
	cout<<"area() using dynamic pointer : "<<dyn_r_ptr->area()<<endl;

	delete dyn_r_ptr; //free the dynamic memory of rectangle


} 

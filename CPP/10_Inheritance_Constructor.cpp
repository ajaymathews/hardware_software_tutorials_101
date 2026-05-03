/* 
 * Tutorial: 9_Inheritance_Constructor.cpp
 * Description: Part of the C++ Programming Tutorial Series
 * 
 * How to Compile: g++ "9_Inheritance_Constructor.cpp" -o "9_Inheritance_Constructor.exe"
 * How to Run:     ./"9_Inheritance_Constructor.exe"
 */
#include<iostream>
using namespace std;
class date
{
	private:
		int day,mon,yr;
	public:
		date(int d, int m, int y){	//constructor
			day=d;mon=m;yr=y;
			cout<<"executed base constructor"<<endl;}
			
		 ~date(){//this virtual destructor will destroy both derived and base class
			cout<<"base class destructor is called"<<endl;}
};

class time : public date
{
	private:
		int hr,min,sec;
	public:
		time(int h, int m, int s):date(23,4,20){ //constructor of derived class calling base classs, but note that when 2 constructors
		hr=h;min=m;sec=s;						//have written for the class, the priority goes on to non-parametirized
		cout<<"executed derived class constructor"<<endl;}
		
		~time() {
			cout<<"derived class destructor is called"<<endl;}
		
};
int main()
{
	time(5,56,12);
}


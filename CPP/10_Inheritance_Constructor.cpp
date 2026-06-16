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
		int pri_day,pri_mon,pri_yr;
	public:
		date(int d=0, int m=0, int y=0){	//constructor
			pri_day=d;pri_mon=m;pri_yr=y;
			cout<<"executed base constructor"<<endl;}
			
		~date(){
		//this virtual destructor will destroy both derived and base class
			cout<<"base class destructor is called"<<endl;}
};	

class time : public date
{
	private:
		int pri_hr,pri_min,pri_sec;
	public:
		time(int h, int m, int s):date(04,05,2026){ 
			pri_hr=h;pri_min=m;pri_sec=s;						
			cout<<"executed derived class constructor"<<endl;}
		
		~time() {
			cout<<"derived class destructor is called"<<endl;}
		
};
int main()
{
	time(02,44,55);
	
}


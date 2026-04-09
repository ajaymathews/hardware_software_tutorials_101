/* 
 * Tutorial: 7_Inheritance.cpp
 * Description: Part of the C++ Programming Tutorial Series
 * 
 * How to Compile: g++ "7_Inheritance.cpp" -o "7_Inheritance.exe"
 * How to Run:     ./"7_Inheritance.exe"
 */
/* It is actually that if we create a derived class from the base class using ':' operator, then the new derived class object
can access the variable, function defined in base class, but wht i faced is, when the variables are set as private,
when using the derived class object to get value from the base class only when we set tht values from the derived class
we recive he corect value, otherwise we are getting a zero.
Also note that when we create an object of derived class by constructor, it automatically executes the base class condtructor also, if it exits*/

#include<iostream>
using namespace std;

class date
{
	private:
		int day,mon,yr;
	public:
		int get_day();
		int get_mon();
		int get_yr();
		int set_day(int);
		int set_mon(int);
		int set_yr(int);
/*		date(int d=0, int m=0, int y=0)//when we try to set the value from the base class,the derived class recieves 
		{                              //a zero value, when trying to get() using the derriveed object.
		set_day(d); //it is used because i cant able to access the base class private variables from the derived class
		set_mon(m);
		set_yr(y);	
		} */
};
class time : public date
{
	private:
		int hr,min,sec;	
	public:
		int get_hr();
		int get_min();
		int get_sec();
		
/*	time(int h=0,int mi=0,int s=0) //used whenn set_day,mon .. are in base class.
	{
		hr=h;
		min=mi;
		sec=s;	
	}*/
	
	time(int d=0, int m=0, int y=0,int h=0,int mi=0,int s=0)//THIS IS THE CONSTRUCTOR OF DERR CLASS
	{
		set_day(d); //it is used because i cant able to access the base class private variables from the derived class
		set_mon(m);
		set_yr(y);
		hr=h;
		min=mi;
		sec=s;	
	}	
};

	int date::get_day(){
	return day;}
	int date::get_mon(){
	return mon;	}
	int date::get_yr(){
	return yr;	}
	int date::set_day(int d){
	day=d;	}
	int date::set_mon(int m){
	mon=m;	}
	int date:: set_yr(int y){
	yr=y;	}
	
	int time::get_hr(){
	return hr;	}
	int time::get_min(){
	return min;	}
	int time::get_sec(){
	return sec;	}
	
	
int main()
{
	date d;
	time t(22,4,20,8,29,50);
	d.set_day(30);
	cout<<d.get_day()<<"   ";
	cout<<t.get_day()<<endl;
	
	cout<<t.get_hr()<<":"<<t.get_min()<<":"<<t.get_sec()<<endl;
	cout<<t.get_day()<<"/"<<t.get_mon()<<"/"<<t.get_yr()<<endl;
}

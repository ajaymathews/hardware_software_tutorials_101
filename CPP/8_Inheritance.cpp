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

Note: when we create an object of derived class by constructor, it automatically executes the base class condtructor also, if it exits*/

#include<iostream>
using namespace std;

class date
{
	private:              
	//if i change private: into protected: , then derrived class time() can access the private variables of the base class date() directly, but main can't
		int pri_day,pri_mon,pri_yr;
	public:
		int get_day();
		int get_mon();
		int get_yr();
		int set_day(int);
		int set_mon(int);
		int set_yr(int);



		date(int d=0, int m=0, int y=0)
		{
		//when we try to set the value from the base class,the derived class recieves a zero value, when trying to get() using the derriveed object.

		cout<<"date constructor called"<<endl;
		set_day(d); //it is used because i cant able to access the base class private variables from the derived class
		set_mon(m);
		set_yr(y);	
		}

		~date(){
			cout<<"date destructor called"<<endl;}
 
};

class time : public date
{
	//the public keyword before date means, the funtions and members of date is available as public to son. so son can use this to modify the values of base class from main. eg: t.set_day(10);
	//if i change private: into protected: , then derived class time() can access the private variables of the base class date() directly, but main can't
	
	//time class now contains variables from date classs such as pri_day,pri_mon,pri_yr, but in a differnt memory location ,only the type are inherited not value

	private:
		int pri_hr,pri_min,pri_sec;	
	public:
		int get_hr();
		int get_min();
		int get_sec();
		
	time(int h=0,int mi=0,int s=0) 
	{
		cout<<"time constructor called"<<endl;
		pri_hr=h;
		pri_min=mi;
		pri_sec=s;	
	}
	
/*	time(int d=0, int m=0, int y=0,int h=0,int mi=0,int s=0)
	{
		set_day(d); 
		set_mon(m);
		set_yr(y);
		pri_hr=h;
		pri_min=mi;
		pri_sec=s;	
	}	*/
	~ time(){
		cout<<"time destructor called"<<endl;}


};

	int date::get_day(){
	return pri_day;}

	int date::get_mon(){
	return pri_mon;	}

	int date::get_yr(){
	return pri_yr;	}

	int date::set_day(int d){
	pri_day=d;	}

	int date::set_mon(int m){
	pri_mon=m;	}

	int date:: set_yr(int y){
	pri_yr=y;	}
	
	int time::get_hr(){
	return pri_hr;	}

	int time::get_min(){
	return pri_min;	}

	int time::get_sec(){
	return pri_sec;	}
	
	
int main()
{
	date d(03,05,2026);//calls the constructor & sets date using set_day(), ..
	time t(23,45,50);//calls the date constructor & time constructor , both

	d.set_day(30);
	t.set_day(10);

	//eventhough it is derrived from base, base and derrived objects have different memory location
	cout<<"base class : derrived class"<<endl;
	cout<<d.get_day()<<" : "<<t.get_day()<<endl; //prints 30 : 10 , not 10 : 10
	
}
/* order of execution of constructor and destructor
date constructor called
time constructor called

time destructor called
date destructor called
*/
/* 
 * Tutorial: 8_friend.cpp
 * Description: Part of the C++ Programming Tutorial Series
 * 
 * How to Compile: g++ "8_friend.cpp" -o "8_friend.exe"
 * How to Run:     ./"8_friend.exe"
 */


/* using keyword frind we can make any class a frind of base class, so that it can look into the private values of base class, that is the value itself,,

where as in inhereitance , the derrived class creates a copy of the base class variables, and the values are not shared.




#include<iostream>
using namespace std;
class time; 
/*this is to notify the compiler that there is a class named time,othervise when executing friend time, shows error*/

class date
{
	private:
		int pri_day=01,pri_month=01,pri_year=1990;

	public:
		int get_day();
		int get_month();
		int get_year();

		
		void set_date(int,int,int);

		friend void display_date();
		/*using friend for function in date class, allows you to acess the date members without representing it using :: when writing outside class, dont need to write as
		' void date :: display_date(){ ..access date variables..  }
		instead,write as
		 void display_date(){. ..access date variables..  .}
		*/


		friend time; 
		/*here the time class can look into the data class values, 
		dont need to write as 
		class time : public date {  }
		instead,
		class time {  } 
		but acess the values using t.d.value not t.value*/

};

class time
{
	private:
		int pri_hour=10,pri_minute=10,pri_second=50;
	public:
		date d;
		void set_time(int,int,int);

		void display_date_time(){
			cout<<endl;
			cout<<"derrived fun : date:>  "<<d.pri_day<<"/"<<d.pri_month<<"/"<<d.pri_year<<endl;
			cout<<"time:>  "<<pri_hour<<":"<<pri_minute<<":"<<pri_second<<endl;
		}
		
};

void date::set_date(int day,int month,int year){
	pri_day=day;
	pri_month=month;
	pri_year=year;
}

void time::set_time(int hour,int minute,int second){
	pri_hour=hour;
	pri_minute=minute;
	pri_second=second;
}

void display_date(){
	cout<<"friend fun: date:>  "<<pri_day<<"/"<<pri_month<<"/"<<pri_year<<endl;
}

/* //this function s for when friend sum() is used
void sum()
{
	base obj; //defining an object of class base on function, and using function as friend accessing the variables.
	int c=obj.a+obj.b;
	cout<<"sum="<<c;
}

// please note: class derr() can access the private variables of the base class, but base can't access the private variables of the class derr() unless class derr() is declared as friend of base() class.
*/

int main()
{
	time t;
	t.set_time(5,30,55);
	t.d.set_date(10,11,2026);//acessing base variables using friend function
	display_date();

	t.display_date_time();
}


/* 
 * Tutorial: 1_COUT_CIN.cpp
 * Description: Part of the C++ Programming Tutorial Series
 * 
 * How to Compile: g++ "1_COUT_CIN.cpp" -o "1_COUT_CIN.exe"
 * How to Run:     ./"1_COUT_CIN.exe"
 */
#include<iostream>
using namespace std;
// std::cout, std::cin is the operation in normally
//we can remove this std:: by using 'namespace std' on top*/
//unlike printf(), scanf() in c, cout and cin are objects ;
//#include <climits> // Required for INT_MAX

int main()
{
	int i_val=10, val_max=INT_MAX; //max value is 2 billion
	//val(22) :
	
	double l_val=100.548585L; //l stands for long double
	float f_val=100.548585f; 


	char c_letter='a';
	char i_letter=65;
	char c_name[20];
	string s_name;
	//instead of char[], string is better because getline() operates only on string type.

	cout<<"Enter the full name:"<<endl;
	cin>>c_name;
	//cin reads only the first name only, doesnt read spaces. cin puts the /n after its read till space(here it is first name)

   //getline() reads last name after the space(which is replaced by /n by cin) automatically, so it skips getline(), it is called phantom read


   //avoided by putting a cin.ignore() before getline()
	cin.ignore(20,'\n');  
	//Clear the buffer(buffer:temp storage when entering values to variables)
	cout<<"Enter the full name:"<<endl;
	getline(cin,s_name);
	//getline is used to read the input with spaces

	cout<<"integer value :"<<i_val<<endl;
	cout<<"Maximum Integer:"<<val_max<<endl;

	cout<<"char value in char:"<<c_letter<<endl<<"num value in char:"<<i_letter<<endl;//even if we write numbers, since the datatype is char , while printing it prints as char only
	//the cpp is type safe, >> , << detects data type automatically 

	cout<<"float value with L:"<<l_val<<endl;	
	//prints 100.549 which is that it prints only 6 digits,and the last digit will be 1 added or 1 reduced(rounding)
	cout<<"float value with f:"<<f_val<<endl;

	cout<<"char array Name:"<<c_name<<endl;
	cout<<"string Name:"<<s_name<<endl;

	cout<<"press Enter key to exit";
	cin.get();//used to hold the output screen until the user presses enter key

	return 0;
}

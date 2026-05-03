/* 
 * Tutorial: 6_Constructors.cpp
 * Description: Part of the C++ Programming Tutorial Series
 * 
 * How to Compile: g++ "6_Constructors.cpp" -o "6_Constructors.exe"
 * How to Run:     ./"6_Constructors.exe"
 */
#include<iostream>
using namespace std;

class rectangle
{
	private:
		int length, breadth;
		
	public:
		int setlength(int l);		
		int setbreadth(int b);
		int getlength();	
	inline int getbreadth();
	//inline keyword pastes the function defenition defined outside into exact point where it is called, rather than calling function //usually used for short functions improving speed






/*************CONSTRUCTOR****************/
/*constructor is just like a function with the same name as that 
of the class, usually constrructor and destructors are defined inside class, but can also define outside with the ' class :: constructor '
use of constructor:

 1) we can pass value to the constructor to assign it to the private variables at the creation of the object itself, 
 therefore we dont need r1.length=10; r1.breadth=20; 
 instead r1(10,20); rest is don inside constructor



 2) we can call any function defined with the class inside the constructor



/* 1) ********** Default constructor *************/
		//this constructor is automatically created by compiler when an object is created in main, like in any normal class program, but we doesnt see it, but if we define constructor then it is parameterised constructor

/*		rectangle()
		{                            
			cout<<"default constructor is called "<<endl;
		}
*/		//commented to avoid rectangle() ambiguity error

/* 2) ********* parameterised constructor ***********/	
     //this is the constructor created if we want to pass any value to the function defined inside class, without calling ' class.par = x ' in main.

/*		rectangle(int l=0)
		{
		//in here l is initialized, so that when we are not passing l it take it as zero, no garbage value.                            
			cout<<"parameterised constructor with l initilaized is called "<<endl;
		}
*/
		//commented to avoid rectangle() ambiguity error
		


/* 3) ************ Constructor overloading ******************/		
      //constructor can be overloded just like a function to accommodate different type of parameter using same class name as rectangle, but only one constructor can be defined, there for use onewith maximum parameter
		

	/*	rectangle(int l=0, int b=0)
		{ 
	// in here l&b is initialized, so that when we are not passing l& b it take it as zero, no garbage. 
			cout<<"parameterised constructor with l&b initilaized is called "<<endl;                           
			setlength(l);
			setbreadth(b);
		} 
*/
//equivalent for all 3 constructr above
		rectangle(int l=0, int b=0, int h=0)
		{                            
			cout<<"parameterised constructor with l&b&h initilaized is called "<<endl;
			setlength(l);
			setbreadth(b);
		}
		//this constructor will be called when create an object with one or two or three parameterised values




		
/* 4) ************ Copy Constructor ******************/	
		//IMPORTANT: 
		//the aim of copy constructor is to copy the exact values of one object to another object, so we are creating similar another object with same values and types
		
		rectangle(const rectangle &cpy_rec)
		{ 
			//rectangle r2(r1) is called from main()
			//thus values of r1 is obtained using the refrence operator and it is copied into r2 
			//const is used to avoid modifying the r1 object

			cout<<"copy constructor is called "<<endl;
			setlength(cpy_rec.length);
			setbreadth(cpy_rec.breadth);
		}

		/* rectangle(rectangle cpy_rec)
		{
			} 
		*/
		//if we try to create a copy of object without refrence operator, r1 tries to make copy, but needed copy constructor for copying, thus calling copy constructor again and again thus causing infinite loop.


/******************* Destructor **************/
//destructor called automatically  at the end of the scope of class in main
		~rectangle() 
		{
			cout<<"rectangle destructor is called "<<endl;
			//everything the constructor allocated should be destroyed here			
		}
};




/********class functions defined outside class************/ 
//we can also define function inside the class in place of declaration,
//but then it will become inline function at compiling[placing the function code to the class object created in main() ] , but it is not a good method

//:: scope resolution operator

int rectangle::setlength(int l) {	
	if(l<=0)
		this->length=0; 
	else
		this->length=l;	}
	//we can also write length =l; instead, that will also work, 
	//but in case of parameter passed from main() is also named 'length', then 'this->length' is class variable and 'length' is parameter passed, 
	//eg:this->length=length; //this improves readability
				
int rectangle::setbreadth(int b){
	if(b<=0)
		this->breadth=0;
	else
		this->breadth=b;	}
		
int rectangle::getlength(){	
	return this->length;	}	
			
int rectangle::getbreadth(){	
	return this->breadth;	}

/****** Below uses another class, comeback after checking the ectangle calls in main(), as numbers is used for other funcionality ******/	

class numbers{	
	private:
		int limit, *ptr; 
		//these are the private members that can be accessed only in this class.
	public:
		numbers(int num) { 
		//creating a constructor, to pass the value to the private variables.
			limit=num;
			ptr=new int[limit];
			//creating an array of size 'limit' in heap memory.
		}

		numbers(const numbers &ref){
		//copy constructor, use const to avoid modifying the original object
			limit=ref.limit;
			//if we use ptr=ref.ptr;
			//its actually not creating but accessing the already created array of the abaove consructor,
			//thus changing any value fom this will actually change the above also. soif we delete n1, n2 will be deleted.
			//this is called shallow copy

			ptr=new int[limit];
			//to avoid that this need its own array space location with same size of above. //called deep copy
			
			for(int i = 0; i < limit; i++) {
        	ptr[i] = ref.ptr[i]; // Copy the actual values fro the original object to copy object
    		}
			//afer doing all the above cpy constructor is completed
		}
		read_arr()
		{
			cout<<"Enter the values:"<<endl;
			for(int i=0;i<limit;i++)
			{
				cout<<":";
				cin>>*(ptr+i);
			}
		}
		print_arr()
		{
			for(int i=0;i<limit;i++)
			{
				cout<<" "<<*(ptr+i);
			}
			cout<<endl;
		}
		delete_arr()
		{
			delete[]ptr;
			ptr=NULL;
		}


	~ numbers() 
	{
					//this will be called automatically, even if we forgot to call delete_arr to free the memory
		cout<<"number destructor is called"<<endl;
		delete_arr();
	}
};
		
int main()
{
	/******************* rectangle class functions ********************/
	//here it is calling the constructor, not class.
	rectangle r1; //default constructor
	rectangle r2(10,20);//parameterised
	rectangle r3(r2);//copy constructor

	cout<<"R2 length:"<<r2.getlength()<<" breadth:"<<r2.getbreadth()<<endl;
	cout<<"R3 length:"<<r3.getlength()<<" breadth:"<<r3.getbreadth()<<endl;




	/******************* numbers class functions ********************/
	numbers n1(10);//created a dynamc arry of 10 elemnts
	n1.read_arr();
	numbers n2(n1);//copy constructor
	n1.print_arr();
	n2.print_arr();

}

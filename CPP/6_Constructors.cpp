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
		int length,breadth;
	public:
		int setlength(int l);		
		int setbreadth(int b);
		int getlength();	
	inline int getbreadth();//we can make any function defined outside also   							   inline using this method

/*************CONSTRUCTOR****************/
/*constructor is just like a function with the same name as that 
of the class, usually constrructor and destructors are defined inside class, but can also define outside with the ' class :: constructor '
use of constructor:
 1) we can pass value to the constructor to assign it to the private variables
 2) we can call any function defined with the class inside the constructor

/* 1) ********** Default constructor *************/
		//this constructor is automatically created by compiler when an object is created in main, like in any normal class program, but we doesnt see it, but if we define constructor then it is parameterised constructor


/* 2) ********* parameterised constructor ***********/	
     //this is the constructor created if we want to pass any value to the function defined inside class, without calling ' class.par = x ' in main.

		rectangle(int l=0, int b=0)/*in here l&b is initialized, so that when we are not passing l& b it take it as zero, no garbage. */
		{                            
			setlength(l);
			setbreadth(b);
		}
		

/* 3) ************ Constructor overloading ******************/		
      //  we can use the same constructor name with different parameter, similar to a function , which is called overloading
		rectangle()
		{                            
			// .....................
		}

		rectangle(int l=0)
		{                            
			// .....................
		}

		rectangle(int l=0, int b=0)
		{                            
			// .....................
		}


/* 4) ************ Copy Constructor ******************/	

		rectangle(rectangle(&cpy_rec)) //it points to same object rather than ceating a copy, thats why & , if not used prgrm tries to create a copy,but need to pass a copy of object to copy constructor, thus infinite loop.
		{
			setlength(cpy_rec.length);
			setbreadth(cpy_rec.breadth);
		}


/******************* Destructor **************/
//the destructor is automatically called at the end of the program,
		~rectangle() 
		{
			cout<<"include codes to deallocate everything the constructor allocted"<<endl;		
			//such as if file is created, this is where it should be destroyed	
		}
};

/********functions for the class************/ //we can also define function inside the class in place of declaration,
//but then it will become inline function at compiling[executing fun with main] , but it is not a good method
		int rectangle::setlength(int l)  //:: scope resolution operator
		{	if(l<=0)
				this->length=0; //we can also write length & breadth instead, also work, but this is efficient.
			else
				this->length=l;	}
				
		int rectangle::setbreadth(int b)
		{	if(b<=0)
				this->breadth=0;
			else
				this->breadth=b;	}
		
		int rectangle::getlength()
		{	return this->length;	}	
			
		int rectangle::getbreadth()
		{	return this->breadth;	}

		//'this' will be used as r1 or r2 as the object name defined in main()
		
		
int main()
{
	//here calling the constructor, not class.
	rectangle r2(10,20);//parameterised
	rectangle r3(r2);//copy constructor


	cout<<"R2 length:"<<r2.getlength()<<"    breadth:"<<r2.getbreadth()<<endl;
	cout<<"R3 length:"<<r3.getlength()<<"    breadth:"<<r3.getbreadth()<<endl;
}

/*
class numbers
{	private:
		int a, *p; //these are the private members that can be accessed only in this class.
	public:
		numbers(int num) //creating a constructor, to pass the value to the private variables.
		{	a=num;
			p=new int[a];//creating an array to the p th location. 
		}
		numbers(const numbers(&n))
		{							//copy constructor, use const to avoid 
									//modifying the original object
			a=n.a;
		//	p=n.p; 
				//its actually not creating but accessing the already created array of the abaove consructor,
				//thus changing any value fom this will actually change the above also. so it fails the functionality of a opy constructor, so always use below method 

			p=new int[a];
			//to avoid that this need its own array space location with same size of above. 
			
			for(int i = 0; i < a; i++) {
        	p[i] = n.p[i]; // Copy the actual values fro the original object to copy object
    }
		}
		read_arr()
		{
			for(int i=0;i<a;i++)
			{
				cout<<":";
				cin>>*(p+i);
			}
		}
		print_arr()
		{
			for(int i=0;i<a;i++)
			{
				cout<<" "<<*(p+i);
			}
			cout<<endl;
		}
		delete_arr()
		{
			delete[]p;
			p=NULL;
		}


	~ numbers() 
	{
					//this will be called automatically, even if we forgot to call delete_arr to free the memory
		cout<<"destructor called"<<endl;
		delete[]p;
		p=NULL;
	}
};

int main()
{
	numbers n1(10);
	//n1.read_arr();
	numbers n2(n1);
	n2.read_arr();	
	n2.print_arr();
	
n1.delete_arr();
n2.delete_arr();
}
*/





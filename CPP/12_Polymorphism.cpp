/* 
 * Tutorial: 11_Polymorphism.cpp
 * Description: Part of the C++ Programming Tutorial Series
 * 
 * How to Compile: g++ "11_Polymorphism.cpp" -o "11_Polymorphism.exe"
 * How to Run:     ./"11_Polymorphism.exe"
 */

/* Inhertence: when we create a derived class from the base class using ':' operator,child have acces to parent class functions and variables.
in this case if you create a pointer of parent class and assign child class object to it, the cmpiler will check the which class isused to make pointer, then call the function of that class.

/*POLYMORPHISM : using virtual keyword, we can access the functions and vaiables of base class like inheritanc but also it works in opposite way, the ponier created using parent class can call the function of child class.

virtual keyword creates the vtble , when a function is called, it checks the v tble to find which child class object is assigned to the base class pointer, then calls the function of that class.
*/

#include<iostream>
using namespace std;
class parent{
	private:
		int pri_a,pri_b;
	public:
		//void display(){
		virtual void display(){
			cout<<"Display in parent"<<endl;}
};

class child: public parent{
	public:
		void display(){
			cout<<"Display in child"<<endl;}
};



/****check the main, below is another class explaining polymorphism ******/

class communication{
	public:
		virtual void init()=0;
		virtual void send(int data)=0;
		virtual void receive()=0;
};

class uart: public communication{
	private:
		int uart_data_buffer=0;
	public:
		void init(){
			uart_data_buffer=11;
			cout<<"uart initialized"<<endl;}

		void send(int data){
			uart_data_buffer=data;
			cout<<"uart sending data : "<<uart_data_buffer<<endl;}

		void receive(){
			cout<<"received data on uart buffer: "<<uart_data_buffer<<endl;}
};

class spi: public communication{
	private:
		int spi_data_buffer=0;
		public:
		void init(){
			spi_data_buffer=22;
			cout<<"spi initialized"<<endl;}

		void send(int data){
			spi_data_buffer=data;
			cout<<"spi sending data : "<<spi_data_buffer<<endl;}

		void receive(){
			cout<<"received data on spi buffer: "<<spi_data_buffer<<endl;}
};


int main()
{
	parent p;
	child c;
	p.display();//parent class function
	c.display();//child class function

	parent *p_ptr = new child();
	//assigning child class object to parent class pointer
	//parent *p_ptr = &c;

	//both parent and child have same display() function, but child class have higher priority
	p_ptr->display();
	//if virtual keyword is not used, then it will call the parent class display() function, you can check by commenting the virtual keyword in parent class display() function

	delete p_ptr;

/********************Polymorphism- more****************************************/

communication *hal_comm;

hal_comm = new uart();
hal_comm->init();
hal_comm->receive();
hal_comm->send(100);
hal_comm->receive();

hal_comm = new spi();
hal_comm->init();
hal_comm->receive();
hal_comm->send(200);
hal_comm->receive();

delete hal_comm;
}


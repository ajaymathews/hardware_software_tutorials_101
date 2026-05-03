

/********** Function Template **************/

#include<iostream>
using namespace std;

//" template <class T> " is needed to be added for each use of T, otherwise error of undeclared T	
template <class T> 	

T T_fun(T x,T y)
{cout<<"same type T_fun(x,y)- "<<x<<"  : "<<y<<endl;
return x+y;}
//this template t can bxe of any value , but T c be only one value, 
//either (int,int) or (float,float) or (char,char) depends upon the value at passing, but not mixed datatype as (int,float) or (char,int) 


//soln: mixed template
template <typename T1, typename T2>
	
void T_mix_fun(T1 x, T2 y)
	{cout<<"T overloaded fun(x,y)- "<<x<<" : "<<y<<endl;}
  
 
int main()
{
    //passing same type parameter to function
	T_fun(10,20);
	T_fun(10.5f,20.2f); 
	T_fun('a','k');
 
	//T_fun(10.5f,'k'); 
    //This will fail as no two mixed types can be used for a single T in a single function call


    //Soln: use mixed temlate, this will work
    cout<<endl;
	T_mix_fun(10,10.5f);
	T_mix_fun(15.5,1);
    T_mix_fun(25,'k');



 return 0;
}


/* 
 * Tutorial: Linear_Search.cpp
 * Description: Part of the C++ Programming Tutorial Series
 * 
 * How to Compile: g++ "Linear_Search.cpp" -o "Linear_Search.exe"
 * How to Run:     ./"Linear_Search.exe"
 */
#include<iostream>
using namespace std;

int* search(int num, int arr[],int *pos)
{
	int p=0;
	for(int i=0;arr[i-1]!=255;i++)
	{
		if(arr[i]==num)
		{
		    pos = new int;
			*(pos)=i;
			cout<<"pos[]="<<i<<endl;
			pos++;
		}
	}
	return pos;
}

int main()
{
	int num,*arr=NULL,*pos;
	cout<<"enter the array:";
	while((*arr)!='.')
	{
		cout<<":";
		arr=new int;
		cin>> (*arr);
		arr++;
	}
	
	cout<<"Enter the number to search";
	cin>>num;
	search(num,arr,pos);
	for(int i=0;i<=4;i++)
	{	cout<<*(pos+i)<<" ";}
	delete[]arr;
	delete[]pos;
	return 0;
}


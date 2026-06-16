

/******Static members and functions*/


#include<iostream>
using namespace std;

class time
{
	private:
		int pri_hr=0,pri_min=0;
	public:
		static int sec,count=0;

		void update_second(){
			sec+=10;
			cout<<"second :"<<sec<<endl;}
};
int time::sec=0; 
//to use a static variable, it also should be writtten outside the class or main, like global.  



int main()
{
	time t1,t2,t3;
	t1.update_second();
	t2.update_second();
	t3.update_second();
    cout<<"no of object created :"<<t1.count<<endl;
    //the varaible count is shared amoung all the object,thus value one object uses the same as the other objects. 
}

/* a class inside another class can be created*/ 

#include<iostream>
using namespace std;

class node {
    public: // Must be public for the list to access it
        int data;
        node *next = NULL; // 'addr' is usually called 'next' in linked lists
};

class linkedlist {
    private:
        node* head; // The start of the list
    public:
        linkedlist() {
            head = NULL; // Initialize the list as empty
        }

        void add_node(int val) {
            node* newNode = new node; // Create a node on the HEAP
            newNode->data = val;
            newNode->next = head;     // Point new node to the old head
            head = newNode;           // Update head to be the new node
            cout << "Added node with data: " << val << endl;
        }

        void display() {
            node* temp = head;
            while(temp != NULL) {
                cout << temp->data << " -> ";
                temp = temp->next;
            }
            cout << "NULL" << endl;
        }
};

int main() {
    linkedlist l1;
    
    l1.add_node(10);
    l1.add_node(20);
    l1.add_node(30);

    cout << "The list looks like: ";
    l1.display();

    return 0;
}
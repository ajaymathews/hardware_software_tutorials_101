#include<iostream>
#define log(x) std::cout<<x<<std::endl;
int add10(int& );

int main(){
    int var_a=10;


    /***************** pointer ******************/
    int* ptr=nullptr;
    //null ptr is similar to the null value , except cpp has a null value defined for the pointer, but both hold value 0 in its memory location.

    ptr=&var_a;
    //ptr now holds the adress of the variable var_a

    std::cout<<"memory adress: "; log(ptr); 
    std::cout<<"value :"; log(*ptr);

    *ptr=20;
    std::cout<<"modifed value :"; log(*ptr);

    int *new_ptr=ptr;
    std::cout<<"new ptr memory adress: "; log(new_ptr); 
    std::cout<<"new ptr value :"; log(*new_ptr);


    //pointer to pointer
    int **ptr_to_ptr=&ptr;
    std::cout<<"double pointer memory adress: "; log(ptr_to_ptr); 
    std::cout<<"double pointer value :"; log(*ptr_to_ptr);
    std::cout<<"accesing value using double pointer :"; log(**ptr_to_ptr);



    //dynamic memory allocation
    ptr = new int;
    int *arr_ptr = new int[10];//ponts to 10 int array values in heap

    *ptr=100;std::cout<<"new value :"; log(*ptr);


    //freeing the memory
    delete ptr;
    delete[] arr_ptr;
    //avoiding dangling pointer by assigning null value
    ptr=nullptr;
    arr_ptr=nullptr;








    /***************** refrence variable ******************/
    /****  IMPTNT ****/ 

    int& ref_var=var_a; 
    //& operator is overloaded here to refer to the address of the variable
    //doest have the same meaning as adress operator in pointer,

    //refrence variable is just another name for the variable, both var_a and ref_var point to the same variable and its value


    //int b_var=100;
    //ref_var = b_var

    //if ref_var = b_var, then ref_var doesnt point to b_var, since it first points to a_var , it changes the value of a_var to the value of b_var


    std::cout<<"refrence variable: "; log(ref_var);
    ref_var=30; 



    std::cout<<"modifed value using refrence variable: "; log(var_a);

    add10(var_a);
    //eventhough var_a is supposed to be passed as a copy, but using reference operator at defenition it will act as a reference variable, and thus update the variable itself (pointer functionality but doesnt need * operator to acess the value)

    std::cout<<"modifed value using refrence variable: "; log(var_a);

    return 0;
}

int add10(int& a){
    a=a+10;
    return 0;
}
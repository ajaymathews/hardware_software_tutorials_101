#include<stdio.h>
#include<stdlib.h>

int no_of_one(int num);
int rotate_n_bits(int num,int rot);
int check_grey(int num1, int num2);
char* dec_bin(int num);
int bit_sum(int num1, int num2);

char buffer[33];

int main(){
    int num,count=0;
    printf("give the input:");scanf("%d",&num);
    printf("\n number of bits in this num  is %d", 8 * sizeof(num));// sizeof() returns the memory in bytes 
    

    // #count num of 1 in binary code
    // count = no_of_one(num);
    // printf("\n no of ones in the number is %d ",count);

    // #counter clockwise rotation in binary code
    // int rot,rot_num = 0;
    // printf("\n no of clockwise rotation to be done:");scanf("%d",&rot);
    // rot_num = rotate_n_bits(num , rot);
    // printf("\n rotated value %d",rot_num);

    //#checking if the number is grey or not
    // int num2;
    // printf("\nEnter the second number to check");scanf("%d",&num2);
    // int ret = check_grey(num, num2);

    // swap two num
    // int num2,num1=num;
    // printf("\nEnter the second number to check");scanf("%d",&num2);
    // // normal method:
    // // num1=num1+num2;
    // // num2=num1-num2;
    // // num1=num1-num2;

    // // BItwise method
    // num1 = num1 ^ num2;
    // num2 = num1 ^ num2;
    // num1 = num1 ^ num2;
    
    // printf("swapped nos:%d %d",num1,num2);


    // SUM OF TWO NUMBERS USING BIT OPERATIONS
    // int num1=num,num2,ret;
    // scanf("%d",&num2);
    // ret = bit_sum(num1 ,num2);
    // printf("\n the sum= %d",ret);
    

    return 1;
}

int bit_sum(int num1, int num2){
    int sum=0,carry=0; 
    while(num2!=0){
        sum = num1 ^ num2 ; //xor operation //1+0 = 1        1011
                                            //0+1 = 1      + 0110
                                            //0+0 = 0      --------
                                            //1+1 = 0         1101 
        carry = (num1 & num2 )<<1; // and operation gives the carry value 
                //only 1*1 has a carry value and it is added to its left num 

        //to carry out the process without any delay
        num1 = sum;
        num2 = carry;
    }

    return sum;
}

char* dec_bin(int num){// #print num in binary code
    itoa(num, buffer, 2);
    return buffer;
}
int check_grey(int num1, int num2){   //num1 = 1101  num2 = 1010
    int count=0;
    while((num1 || num2) > 0){
        count += ((num1 & 1) ^ (num2 & 1));
        printf("\n %d = %s + %s",count, dec_bin((num1 & 1)),dec_bin((num1 & 1)));
        num1 >>= 1;
        num2 >>= 1;
        printf("\n decreased bin value num1= %s  num2=%s",dec_bin(num1),dec_bin(num2));
    }
    if(count == 1)
        printf("\n the numbers are grey");
    else
        printf("the numbers are not grey");
    return count;
}

int rotate_n_bits(int num,int rot){ //clockwise rotation of num 

    printf("\n %d = %d | %d",num >> rot,num << (32 -rot));
  return ((num >> rot) | (num << (32-rot)));
//         00001101 >> 2 |  00001101 << (8-2)
//         00000011      |  01000000
//      =        01000011
}

int no_of_one(int num){
    int ret=0;
    while(num>0){//let num be 13 = 1101,

//  NORMAL METHOD
//        ret += num%2 ; // 13%2 = 1(remainder)
//        num >>= 1 ;   //shift each bit in the number to right,(compute in 
//                      binary) 

//  BITWISE METHOD
        ret += num & 1 ; //compare the lsb is 1, by bitwise & operation
//                          1101  &
//                          0001  
//                         -------
//                          0001
//  this '1' is added to 'ret' and remove the last bit then do again
        num >>= 1 ;     // current vaue : 1101 -> 0110
    }
    return ret;
}
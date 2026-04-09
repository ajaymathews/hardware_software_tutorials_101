/* now you know where im standing with my knowledge, so structure memory space is created when structure objects/members are declared, so no neeed to malloc and allocate space, only the array pointer declared inside the structure require dynamic allocation, if the array inside the structure was 
typedef struct {
    int data[10];
    size_t size;
} array_t;
like this then it would also allocate the memory for the array also, no need to dynamically allocate the array right?
i corrected the code please recheck
*/
/* PROBLEM 1*/

#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int *data;
    size_t size;
} array_t;

int array_append(array_t *arr, int value){
    int *temp_arr;// dont need this, it is already allocated at structure member, we need to dynamically allocate array only
    int extra_size=arr->size+1;

    if(!arr){
        return -1;
    }
    else{
        temp_arr=realloc(arr->data,sizeof(int)*extra_size);
        if(!temp_arr)
            return -1;
    }
    
    arr->data=temp_arr;
    arr->data[arr->size]=value;
    arr->size++;
}

int array_sum(const array_t *arr){
    int sum=0;
    for(int i=0; i<arr->size ;i++){
        sum=sum+arr->data[i];
    }
    return sum;
}

/* PROBLEM 2*/
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
// typedef struct{
//     uint8_t version;
//     uint16_t length;
//     uint16_t checksum;
// }reg_t;

void parse_register(uint32_t reg, uint8_t *version, uint16_t *length, uint16_t *checksum){
    if(!version||!length||!checksum){
        return;
    }
*version=(uint8_t)reg>>28&0x0F;
*length=(uint16_t)reg>>16&0x0FFF;
*checksum=(uint16_t)reg&0xFFFF;

}


/* PROBLEM 3*/
#include<stdio.h>
#include<stdlib.h>

int my_strcpy(char *dst, size_t size, const char *src){
    if(!dst||!src||(size==0))
        return -1;

    int src_len=0,i=0;
    while(src[src_len]!='\0'){
        src_len++;
    }
    if(src_len>size-1)//size-1 bcz reserve space for '\0'
        return -1;

    for(i=0;i<src_len;i++){
        dst[i]=src[i];
    }
    dst[i]='\0';
    return src_len;
}


/* PROBLEM 4*/

#include<stdio.h>

typedef struct {
    int id;
    int data[3];
    void (*process)(int *);
} device_t;

void process_data(int *d){
    for(int i=0;i<3;i++){
        d[i]=d[i]*2;
    }
}
 
int main(){
    device_t dev;
    dev.id=1;
    for(int i=0;i<3;i++){
        dev.data[i]=i;
    }
    dev.process=process_data;
    dev.process(dev.data);
}

/* PROBLEM 5*/

#include <stdio.h>
#include <stdlib.h>

int print_buffer(const uint8_t *buf, size_t len){
    if(!buf||(len==0)){
        return -1;
    }
    for(int i=0;i<len;i++){
        printf("%02X",buf[i]);
    }
 return 0;   
}

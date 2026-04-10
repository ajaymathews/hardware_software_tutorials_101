#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct{
    char *str;
    int *num;
}datatype;

typedef struct{
    bool sof;
    int *id;
    int *ctrl;
    int *crc;
    datatype data;
}header;

int add_msg(){
    printf("\nAdditional.h is included\n");
    return 1;
}


void init(){
    header can_header;
    char* str2;
    add_msg();
    printf("\nEnter the ID:");
    scanf("%d", &can_header.id);
    printf("\nEnter the messege:");
    scanf("%s", str2);    
    can_header.data.str=str2;
    printf("\nmessege recieved : %s",can_header.data.str);
}
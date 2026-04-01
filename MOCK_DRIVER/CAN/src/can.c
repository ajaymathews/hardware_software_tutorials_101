#include<stdio.h>
#include <string.h>
#include "can.h"


/**********   MOCKBUFFER *********/
static CAN_Header_Typedef can_header_rx_buff_temp;

/*can_tx_header : we enter the can data into this varaible
 *can_header_rx_buff_temp : used to copy the data from the tx_header, so
      that we can asssign it to the rcv buffer as mock data recived
 * can_header_rx_buff : the buffer wher the mock data is stored and printed as  
      recieved    */ 


void can_init(){
    printf("CAN driver initialization done .\n");
}

bool can_transmit(CAN_Header_Typedef* can_tx_header){
    printf("Sending can message with header :\n");
    printf(" Id : %X \n msg: %s \n a[0] : %d\n a[0] : %d \n a[0] :%d \n dlc: %d",can_tx_header->id,can_tx_header->msg.str, can_tx_header->msg.arry[0], can_tx_header->msg.arry[1], can_tx_header->msg.arry[2], can_tx_header->dlc);
    
    /*********** NOTE ******************/
    printf("\npass the structure as pointer to save memory ie, pointer takes %I64d bytes and this structure takes %lu bytes\n", sizeof(can_tx_header),(unsigned long)sizeof(CAN_Header_Typedef));


    //copying the same data into rx_buffer for mocking as recived msg
    //memcpy() is defined in the string.h
    //first parmeter is a pointer contains address always
    memcpy(&can_header_rx_buff_temp,can_tx_header,sizeof(CAN_Header_Typedef));

    return true;
}

bool can_recive(CAN_Header_Typedef* can_header_rx_buff){
    memcpy(can_header_rx_buff,&can_header_rx_buff_temp, sizeof(CAN_Header_Typedef));
    printf("Message recived with Id : %X \n msg: %s \n %d\n %d\n %d \n dlc: %d",can_header_rx_buff->id,can_header_rx_buff->msg.str, can_header_rx_buff->msg.arry[0], can_header_rx_buff->msg.arry[1], can_header_rx_buff->msg.arry[2], can_header_rx_buff->dlc);
    return true;
}
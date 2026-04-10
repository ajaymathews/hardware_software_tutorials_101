#include<stdio.h>  //Each c file is compiled independently , standard libraries used will be needed in every c, if you using printf() etc. eg:in can.c

#include "can.h"

int main(){
    can_init();

/* configuring message for sending */
/*
    CAN_HEADER tx_msg={
        .id = 0x123,
        .dlc = 4,
        .msg.arry[0]=10 // this kind of two '.' operations for nested doesnt work during this kind of initialization
    };
    instead
    CAN_HEADER header = {
    .id = 0x01,
    .msg = {
        .str = "Hello",
        .arry = {1, 2, 3, 4}
    },
    .dlc = 4
};  but this method will work fine
    CAN_HEADER tx_msg={ 0x123, 4,10 }
*/
CAN_Header_Typedef can_header_tx_buff;
    can_header_tx_buff.id = 0x123;
    can_header_tx_buff.dlc = 4;
    can_header_tx_buff.msg.arry[0]=10;
    can_header_tx_buff.msg.arry[0]=115;
    can_header_tx_buff.msg.arry[0]=254;

    //snprintf() is safer, since it prevents buffer overflows by checking bountary, in sprintf() only copies the data without checking the boundary has reached or not.
    //snprint(str,sizeof(str),"the value is %d",val); // this kind of asssign is also possible

    snprintf(can_header_tx_buff.msg.str,sizeof(can_header_tx_buff.msg.str),"hello world \n");

can_transmit(&can_header_tx_buff);


CAN_Header_Typedef can_header_rx_buff;
can_recive(&can_header_rx_buff);

return 0;
}
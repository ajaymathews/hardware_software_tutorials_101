/* This is a mock driver developed to test the make file configuration
using gcc compiler */

#ifndef CAN_H
#define CAN_H

#include <stdbool.h>
#include <stdint.h>

/* Struct declarations */

typedef struct{
    char str[10];
    uint8_t arry[10];
}msg_Typedef;

typedef struct {
    uint16_t id;
    msg_Typedef msg;
    uint8_t dlc; 
}CAN_Header_Typedef;


/* function declarations */

void can_init(void);
bool can_transmit(CAN_Header_Typedef* can_header_tx_buff);//always note, when passing a structure, its better to define it as a pointer

bool can_recive(CAN_Header_Typedef* can_header_rx_buff);

#endif
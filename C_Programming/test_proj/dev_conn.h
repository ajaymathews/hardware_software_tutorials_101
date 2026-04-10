#ifndef DEV_CONN_H


    #define DEV_CONN_H

    #include<stdio.h>
    #include<stdint.h>
    #include<stdlib.h>

    /* defining varaibales and global varaiables*/
    #define MAX_VAL_SIZE 256
    

    extern int ex_data;

    /* Structure and enum Definition */
    typedef enum{
        ERR_OK=0,
        ERR_CONN=-1,
        ERR_INIT=-2,
        ERR_WRITE=-3,
        ERR_BUFF_OVF=-4,
        ERR_STR_PTR=-5
    }err_t;

    struct device_t;//forward declaration, used if structure used inside structure

    typedef struct device_t{
        uint8_t device_id;
        char* device_name;
        uint32_t device_data[MAX_VAL_SIZE];
        uint32_t data_index;
        err_t (*device_function)(struct device_t*);
    }device_t;

    /* Function Declaration */
    err_t start_device(device_t*);
    err_t connect_device(device_t*);
    err_t init_device(device_t*);
    err_t write_data_device(device_t *);

#endif

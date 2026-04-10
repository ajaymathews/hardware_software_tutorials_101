#include"dev_conn.h"


/* Function Definition */
int ex_data=111;

err_t start_device(device_t* dev){
    

    if(!dev){
        printf("structure pointer failure\n");
        return ERR_STR_PTR;
    }
    int i;
    printf("attempting to start..\n");
    for(i=0;i<=dev->data_index;i++){
        if(dev->device_data[i]> MAX_VAL_SIZE){
            printf("Buffer overflows\n");
            return ERR_BUFF_OVF;
        }
    }
    for(i=0;i<=dev->data_index;i++){
        printf("%d ",dev->device_data[i]);
    }
    return ERR_OK;
}


err_t write_data_device(device_t *dev){
    if(!dev){
        printf("structure pointer failure\n");
        return ERR_STR_PTR;
    }
    for(dev->data_index=0;dev->data_index<=5;dev->data_index++){
        dev->device_data[dev->data_index]=rand() % MAX_VAL_SIZE;
    }
    return ERR_OK;
}

err_t init_device(device_t* dev){
    if(!dev){
        printf("structure pointer failure\n");
        return ERR_STR_PTR;
    }
    err_t err_ret;
    dev->device_id=11;
    dev->device_name="device1";
    err_ret=write_data_device(dev);
    if(err_ret!=ERR_OK){
        printf("Device writing failed \n");
        return ERR_WRITE;
    }
    dev->device_function=start_device;
    dev->device_function(dev);
    return ERR_OK;
}


err_t connect_device(device_t* dev){
    if(!dev){
        printf("structure pointer failure\n");
        return ERR_STR_PTR;
    }
    err_t err_ret;
    printf("Connecting device...\n");
    err_ret=init_device(dev);
    if(err_ret!=ERR_OK){
        printf("Device Initilization failed \n");
        return ERR_INIT;
    }
    return ERR_OK;
}



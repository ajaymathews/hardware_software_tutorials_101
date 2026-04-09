
#include "dev_conn.h"
#include <stdio.h>
#include <time.h>


int main(){
    err_t err_ret;
    srand(time(NULL));

    device_t device_1;
    err_ret = connect_device(&device_1);
    if(err_ret!=ERR_OK){
        printf("Device Connection failed \n");
        return ERR_CONN;
    }
    printf("extern var %d",ex_data);
return ERR_OK;
}
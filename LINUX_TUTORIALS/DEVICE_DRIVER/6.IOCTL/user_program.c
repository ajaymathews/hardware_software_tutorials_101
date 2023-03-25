#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define WR_VAL _IOW('a','a',int32_t*)
#define RD_VAL _IOW('a','b',int32_t*)

 
int main()
{
	int32_t sent_val, rec_val;
        int fd;
        char option;
        printf("*********************************\n");
        printf("*********** USER-APP ************\n");
 
        fd = open("/dev/sample_device", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }
 
        while(1) {
                printf("****Please Enter the Option******\n");
                printf("        1. Write               \n");
                printf("        2. Read                 \n");
                printf("        3. Exit                 \n");
                printf("*********************************\n");
                scanf(" %c", &option);
                printf("Your Option = %c\n", option);
                
                switch(option) {
                        case '1':
                                printf("Enter the value to write into driver :");
                                scanf("%d",&sent_val);
                                printf("Data Writing ...");
                                ioctl(fd,WR_VAL, (int32_t*) &sent_val);
                                printf("Done!\n");
                                break;
                        case '2':
                                printf("Data Reading ...");
                                ioctl(fd,RD_VAL, (int32_t*) &rec_val);
                                printf("Done!\n\n");
                                printf("Data = %d\n\n", rec_val);
                                break;
                        case '3':
                                close(fd);
                                exit(1);
                                break;
                        default:
                                printf("Enter Valid option = %c\n",option);
                                break;
                }
        }
        close(fd);
}

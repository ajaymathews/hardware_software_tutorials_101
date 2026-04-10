/* safe string append */
#include<stdio.h>
#include<stdlib.h>


int safe_str_append(char *dst, size_t dst_size, const char *src){
    if(!dst||!src||dst_size==0)
        return -1;
        int len=0,i;
        while (dst[len]!='\0')
        {
            if(len>dst_size){
                return -1;
                printf("dst is not null terminated");
            }
            len++;
        }
        
        for(i=0;(src[i]!='\0'&&i+len<dst_size);i++){
            dst[i+len]=src[i];
        }
        dst[i+len]='\0';
    return i;
    }




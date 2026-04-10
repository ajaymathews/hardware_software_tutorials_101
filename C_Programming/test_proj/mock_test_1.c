#include<stdio.h>
#include<stdint.h>

#define ERR_OK 0
#define ERR -1

typedef struct {
    uint8_t  version;
    uint16_t length;
    uint8_t  flags;
    uint8_t  type;
    uint16_t payload_len;
} packet_t;

int parse_packet(const uint8_t *buf, size_t buf_len, packet_t *out);

int parse_packet(const uint8_t *buf, size_t buf_len, packet_t *out){
    uint32_t reg;
    uint16_t load_len;

    if(!buf||!out||(buf_len < 8))
        return ERR;

    reg = buf[0]<<24|buf[1]<<16|buf[2]<<8|buf[3];

    out->version=(reg>>28)&0x0F;
    out->length=(reg>>24)&0x0F|(reg>>16)&0xFF;
    out->flags=(reg>>8)&0xFF;
    out->type=reg&0xFF;

    load_len=buf[4]<<8|buf[5];
    out->payload_len=load_len;

    if(out->length==out->payload_len){
        return ERR;
    }

    return ERR_OK;
}


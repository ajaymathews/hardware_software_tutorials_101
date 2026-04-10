#include <stdio.h>
#include "bitwise.h"

int AND(int x, int y){
    printf("Bitwise AND operation is performed\n");
    return x&y;
}

int OR(int x, int y){
    printf("Bitwise OR operation is performed\n");
    return x|y;
}

int NOT(int x){
    printf("Bitwise NOT operation is performed\n");
    TOGGLE(x,31);
    return ~x;
}

int XOR(int x, int y){
    printf("Bitwise XOR operation is performed\n");
    return x^y;
}

int LSH(int x, int n){
    printf("Bitwise Left Shift operation is performed\n");
    return x<<n;
}

int RSH(int x, int n){
    printf("Bitwise Right shift operation is performed\n");
    return x>>n;
}

int TOGGLE(int x, int pos){
    printf("Bit-Toggle operation is performed\n");
    return (x^(1<<pos));
}
int SET(int x, int pos){
    printf("Bit-Set operation is performed\n");
    return (x|(1<<pos));
}
int RESET(int x, int pos){
    printf("Bit-Reset operation is performed\n");
    return (x&~(1<<pos));
}

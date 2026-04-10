

## Setting Tool Chains
CC = gcc
CFLAGS = -Wall -Wextra -Iinc #Iinc tells 
# the compiler to include the inc foler for headers 
SRC = src/main.c src/can.c
OBJ = $(SRC:.c=.o) #setting main.o and can.o as OBJ
TARGET = build/can_driver

## Setting to include make all
all: $(TARGET)

$(TARGET):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src*.o build/*


#when giving cmnd make, the code actually runs is
# gcc -Wall -Wextra -Iinc  src/main.o src/can.o  -o build/can_driver
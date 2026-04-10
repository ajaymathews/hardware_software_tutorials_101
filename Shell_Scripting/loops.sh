#!/bin/bash

# Title: Loops in Shell Scripting
# Description: Demonstrating while, until, and for loops with break conditions.

# <-----while loop-----> 
# i=0
# while [ "$i" -lt 10 ]    # space after while and inside [] is required, -lt means 'less than'
# do 
#     echo "$i"
#     i=$((i+1))
#     sleep 1
#     if [ "$i" == 7 ]     # break from the loop using break statement
#     then
#         echo "exiting via break"
#         break
#     fi
# done

# while [ 1 ] or while : is an infinite loop
# operations can be done on the shell itself without a script:
# while :; do echo hello; sleep 1; done

# <--------until loop--------->
# i=10
# until [ "$i" -le 0 ]      # until runs as long as the condition is FALSE, -le means 'less than or equal to'
# do
#     echo "hello"
#     i=$((i-1))
#     sleep 1
# done

# <------for loop------->
# for var in 1 2 3 a b c "hello"   # loop through a list of values
# for var in {1..25}               # loop through a range 1 to 25
# for var in {0..25..5}            # loop from 0 to 25, incrementing by 5

for ((var=0; var<=10; var++))
do 
    echo "$var"
    sleep 1
    if [ "$var" == 7 ]
    then
        echo "exiting via break"
        break
    fi
done

printf "the last value after loop is $var\n"

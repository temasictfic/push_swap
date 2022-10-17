#!/bin/sh

RAND=$(/usr/bin/python3 randrange.py $1 $2 $3)
./push_swap $RAND | ./checker_Mac $RAND
./push_swap $RAND | ./checker $RAND
./push_swap $RAND | wc -l
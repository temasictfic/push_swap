#!/bin/sh

RAND=$(/usr/bin/python3 randrange.py $1 $2 $3)
./push_swap $RAND > ps.txt
./vis $RAND
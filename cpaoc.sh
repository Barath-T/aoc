#!/bin/bash

args=("$@")
noargs=("$#")

if [ $noargs == 2 ]
then
  #echo "completed/${args[0]}/day${args[1]}_${args[2]}.cpp"
  cp working/main.cpp ${args[0]}/${args[1]}.cpp
else
  echo "wrong no of args"
fi

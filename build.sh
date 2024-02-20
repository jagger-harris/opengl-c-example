#!/bin/bash
if [ "$1" = "build" ] && [ "$2" = "" ]
then
  if ! [ -d "./build" ]
  then
    mkdir build
    cd build
    cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_EXPORT_COMPILE_COMMANDS=1
    make
  fi
elif [ "$1" = "run" ]
then
  if ! [ -d "./build" ]
  then
    echo "Build folder not located: ./build.sh build"
  else
    cd build
    ./executable
  fi
elif [ "$1" = "build" ] && [ "$2" = "run" ]
then
  if ! [ -d "./build" ]
  then
    mkdir build
  fi
  cd build
  cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_EXPORT_COMPILE_COMMANDS=1
  make
  ./executable
else
  echo "Command usage: ./build.sh command [command: build, run, build run]"
fi

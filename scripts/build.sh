#!/bin/bash

mkdir -p bin
cd bin 
mkdir -p debug


target_debug() {
    cd debug 
    cmake -DCMAKE_BUILD_TYPE=Debug ../..
    make
    echo "Built target in bin/debug/"
}

target_debug 

#if [ "$1" = "release" ]
#then
 #   target_release
#elif [ "$1" = "both" ]
#then
 #   target_release
  #  target_debug
#else
 #   target_debug
#fi

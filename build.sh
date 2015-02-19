#!/bin/sh

g++ jsoncpp-src-0.5.0/src/lib_json/*.cpp main.cpp -std=c++14 -I external/include/ -l luajit-5.1 -o play


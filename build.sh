#!/bin/bash

g++ -std=c++11 -static -static-libstdc++ -static-libgcc \
-Wall -Werror -Wextra -Weffc++ \
main.cpp -o padder

strip padder


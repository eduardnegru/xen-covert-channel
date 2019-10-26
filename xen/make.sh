#!/bin/bash

g++ -std=c++11  receiver.cpp -o receiver
g++ -std=c++11   sender.cpp -o sender
g++ -std=c++11   test.cpp -o test
g++ -std=c++11   load.cpp -o load

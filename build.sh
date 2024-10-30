#!/usr/bin/env bash

rm -rf build
mkdir build
cd build
cp -r ../res .
cmake ..
make

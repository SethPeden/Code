#!/bin/bash
./compile $1 temp
./run temp
rm temp

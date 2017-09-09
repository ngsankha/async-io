#!/bin/sh

rm -r lib
mkdir lib
cd src
gcc -Wall -c asyncio.c -pthread
ar -cvq ../lib/libasyncio.a *.o


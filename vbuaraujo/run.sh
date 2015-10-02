#!/bin/bash
gcc -o test *.c && gdb -ex run -ex bt ./test

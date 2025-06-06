#!/usr/bin/env bash

echo "COMPILING"
g++ -Iinclude -Wall -Wextra ./src/* -o ./build/bfc

if [[ $? != 0 ]]; then
	echo "FAILED"
else
	echo "COMPILED SUCCESSFULLY"
fi

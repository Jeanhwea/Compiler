#!/bin/bash
for (( i = 1; i < 13; i++ )); do
	echo "compiling t$i.pas ~>"
	./compiler c t${i}.pas
done

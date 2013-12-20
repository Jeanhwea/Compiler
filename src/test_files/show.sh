#!/bin/bash
for (( i = 1; i < 13; i++ )); do
	cat t$i.pas
	./run$i
done

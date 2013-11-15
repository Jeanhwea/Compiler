#!/bin/bash
for (( i = 1; i < 6; i++ )); do
	./compiler example/${i}.pas > tree/${i}.xml
done

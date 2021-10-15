#!/bin/bash
rm *.asm *.stb *.xml *.qaud *.lst *.o
for (( i = 1; i < 13; i++ )); do
	rm t$i
done